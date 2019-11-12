#include "Transaction.hpp"
#include <string>

// Incrementing this variable in the Transaction constructor ensures that each transaction has a unique transaction ID.
int Transaction::incrementTransactionID = 0;

Transaction::Transaction(Account* fromAccount, Account* toAccount, Money amount) {
	transactionID = incrementTransactionID++;
	this->fromAccount = fromAccount;
	this->toAccount = toAccount;
	if (amount.asCents() > 0) {
		this->amount = amount;
	}
	// The following variable is used in the implementation of performTransaction() in the Tranasction class.
	state = PENDING;
}

bool Transaction::performTransaction(){
	Account* FromAccount = this->fromAccount;
	Account* ToAccount = this->toAccount;
	// Withdraw amount from the fromAccount and deposit it into the toAccount.
	// If withdrawMoney fails, depositMoney is not called and performTransaction() fails.
	// If withdrawMoney passes but depositMoney fails, determine which type of account FromAccount is and call 
	//	revertWithdrawal on it.
	// revertWithdrawal is a helper method from the Account class and has a different implementation for each 
	//	type of account. For more information on how revertWithdrawal works, refer to each type of account to
	//	see it's implementation.
	// If withdrawMoney passes but depositMoney fails, performTransaction() fails.
	if (FromAccount->withdrawMoney(amount) == true) {
		if (ToAccount->depositMoney(amount) == true) {
			state = COMPLETED;
			return true;
		} else if (FromAccount->accountType == SAVINGS) {
			FromAccount->revertWithdrawal(amount);
			state = FAILED;
			return false;
		} else if (FromAccount->accountType == CHEQUE){
			FromAccount->revertWithdrawal(amount);
			state = FAILED;
			return false;
		}else {
			FromAccount->revertWithdrawal(amount);
			state = FAILED;
			return false;
		}
	} else {
		state = FAILED;
		return false;
	}
}

TransactionState Transaction::getState() const {
	return state;
}

Money Transaction::getAmount() const {
	return this->amount;
}

Account* Transaction::getToAccount() const {
	return this->toAccount;
}

Account* Transaction::getFromAccount() const {
	return this->fromAccount;
}


int Transaction::getID() const {
	return transactionID;
}

Transaction::~Transaction() {
}

