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

int main2test() {
	ST_cardData_t *newcardPtr;
	newcardPtr = (ST_cardData_t*) malloc(sizeof(ST_cardData_t));
	//*newcardPtr=(const ST_cardData_t){0};
	memset(newcardPtr, 0, sizeof(ST_cardData_t));
	/*
	 //Testing card expiry date
	 EN_cardError_t card_state= getCardExpiryDate(newcardPtr);


	 if(card_state==CARD_OK)
	 printf("date is valid and expiry date is %s  \n",newcardPtr->cardExpirationDate);

	 else
	 printf("invalid expiry date  \n");
	 */

	/*
	 //Testing card holder name
	 EN_cardError_t card_state= getCardHolderName(newcardPtr);
	 if(card_state==CARD_OK)
	 printf("name valid and name is %s  \n",newcardPtr->cardHolderName);

	 else
	 printf("invalid name  \n");
	 */

	/*
	 //Testing card PAN number
	 EN_cardError_t card_state= getCardPAN(newcardPtr);
	 if(card_state==CARD_OK)
	 printf("PAN valid and PAn is is %s  \n",newcardPtr->primaryAccountNumber);

	 else
	 printf("invalid PAN  \n");
	 */

	/*
	 //testing terminal transaction date
	 ST_terminalData_t* ter = (ST_terminalData_t*)malloc(sizeof(ST_terminalData_t));
	 EN_terminalError_t err;
	 err =getTransactionDate(ter);
	 if(err==TERMINAL_OK){
	 printf("valid date");
	 }
	 else{
	 printf("not valid date");
	 }
	 */

	/*
	 //testing is card expired function
	 EN_cardError_t card_state = getCardExpiryDate(newcardPtr);
	 if (card_state == CARD_OK)
	 printf("date is valid and expiry date is %s  \n",
	 newcardPtr->cardExpirationDate);

	 else
	 printf("invalid expiry date  \n");

	 ST_terminalData_t *ter = (ST_terminalData_t*) malloc(sizeof(ST_terminalData_t));
	 EN_terminalError_t err;
	 err = getTransactionDate(ter);
	 if (err == TERMINAL_OK) {
	 printf("valid transaction date date \n");
	 err = isCardExpired(*newcardPtr, *ter);
	 if (err == TERMINAL_OK) {
	 printf("valid card \n");
	 } else if(err==EXPIRED_CARD){
	 printf("not valid card date \n");
	 } else {
	 printf("not valid date\n");
	 }


	 }*/

	/*
	 //testing transaction amount
	 ST_terminalData_t *ter = (ST_terminalData_t*) malloc(sizeof(ST_terminalData_t));
	 EN_terminalError_t err;
	 err=getTransactionAmount(ter);
	 if(err==TERMINAL_OK){
	 printf("valid transaction amount\n");
	 }
	 else{
	 printf("not valid amount\n ");
	 }
	 */

	//printf("data of transaction %s",transactions_arr[0].cardHolderData.cardHolderName);
	//printf("data of database %s ",accounts[100].primaryAccountNumber);
	//-----------------------------------------------------------------------------------------------------
	/*
	 //testing SERVER.C file
	 ST_transaction* transData =(ST_transaction*)malloc(sizeof(ST_transaction));
	 EN_cardError_t card_state= getCardExpiryDate(newcardPtr);
	 card_state=getCardHolderName(newcardPtr);
	 card_state=getCardPAN(newcardPtr);

	 if(card_state==CARD_OK)
	 printf("valid and expiry date is %s ,name is:%s \n Pan number is: %s\n"
	 "",newcardPtr->cardExpirationDate,newcardPtr->cardHolderName,newcardPtr->primaryAccountNumber);

	 else
	 printf("invalid expiry date in main function  \n");


	 ST_terminalData_t* ter = (ST_terminalData_t*)malloc(sizeof(ST_terminalData_t));
	 EN_terminalError_t err;

	 err =getTransactionDate(ter);
	 err=setMaxAmount(ter);
	 err=getTransactionAmount(ter);

	 if(err==TERMINAL_OK){
	 printf("valid date \n");
	 }
	 else{
	 printf("not valid terminal case:%d \n",err);
	 }

	 transData->cardHolderData=*newcardPtr;
	 transData->terminalData=*ter;




	 EN_transStat_t receve_tr_error= recieveTransactionData( transData);

	 printf("date inside transaction is   is %s  \n",transData->cardHolderData.cardExpirationDate);


	 printf("data is valid and state  is %d  \n",receve_tr_error);

	 getchar();

	 */

	return EXIT_SUCCESS;
}

