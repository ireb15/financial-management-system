#include "CreditAccount.hpp"

CreditAccount::CreditAccount(const int customerID) : Account(1) {
	this->customerID = customerID;
	creditID = Account::getAccountID();
	// The following variable is used in the implementation of performTransaction() in the Tranasction class.
	accountType = CREDIT;
}

bool CreditAccount::withdrawMoney(Money amount) {
	// Withdraw amount from Credit Account, unless the amount to be withdrawn is negative.
	originalBalanceCRA = balanceCRA.asCents();
	balanceCRA.subtract(amount);
	// Pass the Savings Account balance to the Account class;
	accountBalance = balanceCRA;
	if (balanceCRA.asCents() == (originalBalanceCRA - amount.asCents())) {
		return true;
	} else {
		return false;
	}
}

bool CreditAccount::depositMoney(Money amount) {
	// Deposit amount into Credit Account, unless depositing amount into the Credit Account raises the balance 
	//	of Credit Account past $5000 or the amount is negative. 
	if (((balanceCRA.asCents() + amount.asCents()) <= 500000) && (amount.asCents() >= 0)) {
		balanceCRA.add(amount);
		// Pass the Savings Account balance to the Account class;
		accountBalance = balanceCRA;
		return true;
	} else {
		return false;
	}
}

// revertWithdrawal is a helper method that is called in performTransaction() from the Transaction class.
// It reverts the Credit Account balance to its original value after a successful withdrawal but an unsuccessful 
//	deposit in performTransaction().
void CreditAccount::revertWithdrawal(Money amount) {
		balanceCRA.add(amount);
		accountBalance = balanceCRA;
}

CreditAccount::~CreditAccount() {
}
