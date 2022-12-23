#include "./app.h"
#include <stdio.h>
#include <stdlib.h>

//ST_cardData_t *newcardPtr;
extern ST_transaction transactions_arr[255];
extern ST_accountsDB_t accounts[255];
//ST_transaction transactions[255]={{{{0}}}};

int main() {
	ST_cardData_t *newcardPtr;
	newcardPtr = (ST_cardData_t*) malloc(sizeof(ST_cardData_t));
	//*newcardPtr=(const ST_cardData_t){0};
	memset(newcardPtr,0,sizeof(ST_cardData_t));
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



	return EXIT_SUCCESS;
}



