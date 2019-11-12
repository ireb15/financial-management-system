#include "ChequeAccount.hpp"

ChequeAccount::ChequeAccount(const int customerID) : Account(1) {
	this->customerID = customerID;
	chequeID = Account::getAccountID();
	Money transactionFee(1,0);
	transactionFeeCHA.add(transactionFee);
	// The following variable is used in the implementation of performTransaction() in the Tranasction class.
	accountType = CHEQUE;
}

bool ChequeAccount::withdrawMoney(Money amount) {
	Money incrementTransactionFee(1,0);
	// Withdraw amount from Cheque Account, unless amount to withdraw is greater than the balance of the 
	//	Cheque Account or is negative.
	if (((amount.asCents() + transactionFeeCHA.asCents()) <= balanceCHA.asCents()) && (amount.asCents() >= 0)) {
		balanceCHA.subtract(amount);
		balanceCHA.subtract(transactionFeeCHA);
		// Pass the Savings Account balance to the Account class;
		accountBalance = balanceCHA;
		transactionFeeCHA.add(incrementTransactionFee);
		return true;
	} else {
		return false;
	}
}

bool ChequeAccount::depositMoney(Money amount) {
	// Deposit amount into Cheque Account, unless the amount to deposit is greater than $3000 or is negative.
	if ((amount.asCents() <= 300000) && (amount.asCents() >= 0)) {
		balanceCHA.add(amount);
		// Pass the Savings Account balance to the Account class;
		accountBalance = balanceCHA;
		return true;
	} else {
		return false;
	}
}

Money* ChequeAccount::getTransactionFee() const {
	Money tempPointer = this->transactionFeeCHA;
	Money* transactionFeePointer = &tempPointer;
	return transactionFeePointer;
}

// revertWithdrawal is a helper method that is called in performTransaction() from the Transaction class.
// It reverts the Cheque Account balance and its transaction fee to their original values after a successful 
//	withdrawal but an unsuccessful deposit in performTransaction().
void ChequeAccount::revertWithdrawal(Money amount) {
	balanceCHA.add(amount);
	accountBalance = balanceCHA;
	Money incrementTransactionFee(1,0);
	transactionFeeCHA.subtract(incrementTransactionFee);
	accountBalance.add(transactionFeeCHA);
}

ChequeAccount::~ChequeAccount() {
}

