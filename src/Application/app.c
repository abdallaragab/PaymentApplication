#include "./app.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
	ST_cardData_t *newcardPtr;
	newcardPtr = (ST_cardData_t*) malloc(sizeof(ST_cardData_t));
	ST_transaction *transData = (ST_transaction*) malloc(sizeof(ST_transaction));
	ST_terminalData_t *terminal_data_ptr = (ST_terminalData_t*) malloc(sizeof(ST_terminalData_t));
	memset(transData, 0, sizeof(ST_transaction));
	memset(newcardPtr, 0, sizeof(ST_cardData_t));
	memset(terminal_data_ptr, 0, sizeof(ST_terminalData_t));
	EN_terminalError_t terminal_err = INVALID_CARD;
	//---------------------------------------
	terminal_err = setMaxAmount(terminal_data_ptr);
	if (terminal_err == INVALID_AMOUNT) {
		printf("invalid maximum amount\n");
		free(newcardPtr);
		free(terminal_data_ptr);
		return EXIT_SUCCESS;
	}
	//get card holder name

	EN_cardError_t card_state = getCardHolderName(newcardPtr);
	if (card_state != CARD_OK) {
			printf("invalid name entered \n");
			free(newcardPtr);
			return EXIT_SUCCESS;
		}
	card_state = getCardExpiryDate(newcardPtr);
	if (card_state != CARD_OK) {
			printf("invalid date entered \n");
			free(newcardPtr);
			return EXIT_SUCCESS;
		}
	card_state = getCardPAN(newcardPtr);
	if (card_state != CARD_OK) {
		printf("invalid data entered \n");
		free(newcardPtr);
		return EXIT_SUCCESS;
	}
	//receive terminal data

	terminal_err = getTransactionDate(terminal_data_ptr);
	if (terminal_err != TERMINAL_OK) {
		printf("invalid data entered \n");
		free(newcardPtr);
		free(terminal_data_ptr);
		return EXIT_SUCCESS;
	}
	//in case of expired card end program,else continue
	terminal_err = isCardExpired(*newcardPtr, *terminal_data_ptr);
	if (terminal_err == EXPIRED_CARD) {
		printf("this card is expired\n");
		free(newcardPtr);
		free(terminal_data_ptr);
		return EXIT_SUCCESS;
	}
	//get the required transaction amount
	terminal_err = getTransactionAmount(terminal_data_ptr);
	if (terminal_err == INVALID_AMOUNT) {
		printf("invalid amount\n");
		free(newcardPtr);
		free(terminal_data_ptr);
		return EXIT_SUCCESS;
	}
	if (isBelowMaxAmount(terminal_data_ptr) == EXCEED_MAX_AMOUNT) {
		printf("the amount exceeded maximum amount \n");
		free(newcardPtr);
		free(terminal_data_ptr);
		return EXIT_SUCCESS;
	}

	transData->cardHolderData=*newcardPtr;
	transData->terminalData=*terminal_data_ptr;
	EN_transStat_t receve_tr_error= recieveTransactionData( transData);
	switch (receve_tr_error) {
		case APPROVED:
			printf("the transaction is successful\n");
			break;
		case DECLINED_STOLEN_CARD:
			printf("this card is stolen ,please refere to bank\n");
			break;
		case FRAUD_CARD:
			printf("this card is invalid \n");
			break;
		case DECLINED_INSUFFECIENT_FUND:
			printf("the balance is insufficient \n");
			break;
		default:
			printf("error happened please refer to bank\n");
			break;
	}
	printf("press enter to end\n");
	fflush(stdout);

	getchar();
	fflush(stdin);



	return EXIT_SUCCESS;
}


