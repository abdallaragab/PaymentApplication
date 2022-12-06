#include "terminal.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include  <ctype.h>
#include <string.h>

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData) {
	uint8_t temp_date[11];
	printf("Enter the Transaction Date in format DD/MM/YYYY \n");
	//scanf("%11[^\n]%*c",temp_date);
	scanf("%10s", temp_date);

	printf(" Date entered is:%s \n", temp_date);

	uint8_t date_length = strlen((const char*) temp_date);
	if (date_length != 10) {

		return WRONG_DATE;
	}
	uint8_t flag = 1;

	int var = 0;
	for (var = 0; var < TRN_DATE_LEN; var++) {
		switch (var) {
		case 0:
		case 1:
		case 3:
		case 4:
		case 6:
		case 7:
		case 8:
		case 9:
			if (!(isdigit(temp_date[var]))) {
				flag = 0;
				return WRONG_DATE;
			}
			break;
		case 2:
		case 5:
			if (temp_date[var] != '/') {
				flag = 0;
				return WRONG_DATE;
			}
			break;
		}
	}
	if (flag == 0) {
		return WRONG_DATE;
	} else {
		memcpy(termData->transactionDate, temp_date, 11);
		return TERMINAL_OK;

	}
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData,
		ST_terminalData_t termData) {
	//compare date digits in card data and terminal date
	if (cardData.cardExpirationDate[3] < termData.transactionDate[8]) {
		return EXPIRED_CARD;
	} else if (cardData.cardExpirationDate[4] < termData.transactionDate[9]) {
		return EXPIRED_CARD;
	} else if (cardData.cardExpirationDate[0] < termData.transactionDate[3]) {
		return EXPIRED_CARD;
	} else if (cardData.cardExpirationDate[1] < termData.transactionDate[4]) {
		return EXPIRED_CARD;
	} else {
		return TERMINAL_OK;
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData) {
	//in case if the input contained any character it will be stored in tempchar variable
	//if tempchar variable value is not newline '\n' the input is rejected
	char tempchar;
	float temp_amount = 0;
	printf("Enter the Transaction amount \n");
	scanf("%f%c", &temp_amount, &tempchar);
	if (temp_amount <= 0 || tempchar != '\n') {
		return INVALID_AMOUNT;
	} else {
		termData->transAmount = temp_amount;
		return TERMINAL_OK;
	}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData) {
	if (termData->transAmount > termData->maxTransAmount) {
		return EXCEED_MAX_AMOUNT;
	} else {
		return TERMINAL_OK;
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData) {
	//in case if the input contained any character it will be stored in tempchar variable
	//if tempchar variable value is not newline '\n' the input is rejected
	char tempchar;
	float temp_mxamount = 0;
	printf("enter the Max Transaction amount \n");
	scanf("%f%c", &temp_mxamount, &tempchar);
	if (temp_mxamount <= 0 || tempchar != '\n') {
			return INVALID_AMOUNT;
		} else {
			termData->maxTransAmount = temp_mxamount;
			return TERMINAL_OK;
		}

}

