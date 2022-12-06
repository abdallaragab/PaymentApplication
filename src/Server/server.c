
#include "server.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include  <ctype.h>
#include <string.h>


uint8_t LAST_SEQ_NUMBER =0;
ST_transaction transactions_arr[255]={{{{0}}}};

ST_accountsDB_t accounts[255]={{661661,RUNNING,"94785236978945612320"},{65119811,RUNNING,"14781236978945612320"},{98464654,RUNNING,"14785216978945612320"},{77989499,RUNNING,"12785236978945612320"},{8615165,RUNNING,"84785236978945612320"},{1189113,RUNNING,"14782236978945612320"},{13189132,RUNNING,"14785226978945612320"},{9849,RUNNING,"13785236978945612320"},{1681616,RUNNING,"74785236978945612320"},{616123,BLOCKED,"14783236978945612320"},{13216861,BLOCKED,"14785246978945612320"},{49849,RUNNING,"15785236978945612320"},{618161,RUNNING,"64785236978945612320"}};
/*
ST_accountsDB_t accounts[255]={{661661,"94785236978945612320"},{65119811,"14781236978945612320"},{98464654,"14785216978945612320"},{77989499,"12785236978945612320"},{8615165,"84785236978945612320"},{1189113,"14782236978945612320"},{13189132,"14785226978945612320"},{9849,"13785236978945612320"},{1681616,"74785236978945612320"},{616123,"14783236978945612320"},{13216861,"14785246978945612320"},{49849,"15785236978945612320"},{618161,"64785236978945612320"},{159813,"14784236978945612320"},{21651613,"14785256978945612320"},{98496161,"16785236978945612320"},{66161,"54785236978945612320"},{8162118,"14785536978945612320"},{3216513,"14785266978945612320"},{65448646,"18785236978945612320"},{6841616316,"44785236978945612320"},{1981613,"14786236978945612320"},{2166321,"14785286978945612320"},{11316516,"19785236978945612320"},{64984116,"34785236978945612320"},{1989984,"14787236978945612320"},{26515161,"14785296978945612320"},{4654894,"14185236978945612320"},{648949161,"24785236978945612320"},{651661986,"14788236978945612320"},{161616,"14785231978945612320"},{449484,"14285236978945612320"},{4984616,"14785236978945612320"},{3551611,"14789236978945612320"},{161616,"14785232978945612320"},{4948441,"14385236978945612320"},{6498461,"04785236978945612320"},{46462,"14785136978945612320"},{161616,"14785233978945612320"},{494118,"14485236978945612320"},{861848,"99785236978945612320"},{9811651,"14785336978945612320"},{161616,"14785234978945612320"}};*/





EN_transStat_t recieveTransactionData(ST_transaction* transData){
	//since the array is not sorted the algorthim must check all its elements for the required account id
	//and this algorithm is not optimal
	ST_accountsDB_t *loc_account_ref=NULL;
	EN_serverError_t server_state =isValidAccount(&(transData->cardHolderData), loc_account_ref);
	if(server_state==SERVER_OK){
		if(isBlockedAccount(loc_account_ref)==BLOCKED_ACCOUNT){
			transData->transState=DECLINED_STOLEN_CARD;
			server_state=BLOCKED_ACCOUNT;

		}

	}
		else {
			transData->transState=FRAUD_CARD;
		}
	//next step is to withdraw from balance if the card and account is valid
	if(server_state==SERVER_OK){
		if(isAmountAvailable(&(transData->terminalData),loc_account_ref)==SERVER_OK){
			loc_account_ref->balance-=transData->terminalData.transAmount;
			transData->transState=APPROVED;
		}
		else{
					transData->transState=DECLINED_INSUFFECIENT_FUND;
		}
	}
	//next step is to save transaction
	saveTransaction(transData);
	return transData->transState;



/*
	 if(found==1){
		if(accounts[var].balance>=transData->terminalData.transAmount){
			accounts[var].balance=accounts[var].balance-transData->terminalData.transAmount;
			transData->transState=APPROVED;
			return APPROVED;;
		}
		else{
			transData->transState=DECLINED_INSUFFECIENT_FUND;
			return DECLINED_INSUFFECIENT_FUND;
		}
	}
	else{
			transData->transState=DECLINED_STOLEN_CARD;
			return DECLINED_STOLEN_CARD;
		}*/

}

EN_serverError_t isValidAccount(ST_cardData_t* cardData,ST_accountsDB_t* accountRefrence)
{
	//since the array is not sorted the algorthim must check all its elements for the required account id
		//and this algorithm is not optimal
		uint8_t found=0;
		uint8_t var=0;
		while (var!=254){
			//if the next account id=0 then the rest of array is empty thus break the loop
			if(accounts[var].primaryAccountNumber==0){
				break;
			}
			//compare accounts id
		    else if(strcmp((char*)cardData->primaryAccountNumber,(char*)accounts[var].primaryAccountNumber)==0 ){
				found =1;
		    	break;
			}
			var++;
		}
		if(found==1){
			accountRefrence=&accounts[var];
			return SERVER_OK;
		}
		else{
			return ACCOUNT_NOT_FOUND;
		}
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence){
	 if (accountRefrence->state==RUNNING){
		return SERVER_OK;
	}
	 else {
		return BLOCKED_ACCOUNT;
	}
}


EN_serverError_t isAmountAvailable(ST_terminalData_t* termData,ST_accountsDB_t* accountRefrence){
	if(accountRefrence->balance>=termData->transAmount){
		return SERVER_OK;
	}
	else{
		return LOW_BALANCE;
	}
}

EN_serverError_t saveTransaction(ST_transaction* transData){
	//find the last sequence number in transactions array
	if( LAST_SEQ_NUMBER<=TRANS_ARR_SIZE){
	transactions_arr[LAST_SEQ_NUMBER+1]=*transData;
	LAST_SEQ_NUMBER++;
	return SERVER_OK;
	}
	else{
		return SAVING_FAILED;
	}
}


