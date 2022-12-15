#include "card.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include  <ctype.h>

EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	uint8_t temp_name[30];
	//temp_name[]= (char*) malloc(sizeof(char)*30);

	//flush the input buffer to avoid any unexpected behavior


	printf("Enter the card Holder Name \n");
	fflush(stdout);

	//scanf("%26[^\n]%*c",temp_name);
	//	scanf("%[^\n]",temp_name);
	fgets(temp_name,29,stdin);
	fflush(stdin);


	uint8_t name_length = strlen((const char*)temp_name);

	if ((name_length > 24) || (name_length < 20)) {

		return WRONG_NAME;
	}
	else {

		memcpy((cardData->cardHolderName),temp_name,24);




		return	CARD_OK;
	}
}



	EN_cardError_t getCardExpiryDate(ST_cardData_t * cardData){
		char temp_Expiry[7];

		fflush(stdout);
		printf("Enter the card Expiry Date in format MM/YY \n");
		fflush(stdout);

		fflush(stdin);
		scanf("%6s", temp_Expiry);
		fflush(stdin);
		//fgets(temp_Expiry,7,stdin);
		//if expiry date is not valid set flag=0
		int flag = 1;
		//expiry date length is not valid if it doesn't consist of  digits
		if (strlen(temp_Expiry) != 5){
			flag = 0;
		}
		int var = 0;
		for (var = 0; var < 4; var++) {
			//check if expiry date contain "/"
			if (var == 2) {
				if (temp_Expiry[var]!='/') {
					flag = 0;
				}
			}
			else {
				if (!(isdigit(temp_Expiry[var])))
					flag = 0;
			}
		}
		if (flag == 0) {
			return WRONG_EXP_DATE;
		}
		else {
			memcpy((cardData->cardExpirationDate) ,temp_Expiry , 6);
			return	CARD_OK;
		}
}

	

EN_cardError_t getCardPAN(ST_cardData_t* cardData){
	uint8_t temp_PAN [22];


	printf("Enter the card PAN Number \n");
	fflush(stdout);
	scanf("%21s",temp_PAN);
	fflush(stdin);
	uint8_t PAN_len=strlen((const char*)temp_PAN);
	if(PAN_len>DEF_PAN_MAX_LEN||PAN_len<DEF_PAN_MIN_LEN){
		return  WRONG_PAN ;
	}
	int var;
	for (var = 0; var < PAN_len; ++var) {
		if (!(isdigit(temp_PAN[var]))){
			return WRONG_PAN;
		}
	}
	memcpy(cardData->primaryAccountNumber ,temp_PAN , 21);
	return CARD_OK;



}
