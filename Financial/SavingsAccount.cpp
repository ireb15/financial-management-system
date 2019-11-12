#include "SavingsAccount.hpp"

SavingsAccount::SavingsAccount(const int customerID) : Account(1) {
	this->customerID = customerID;
	savingsID = Account::getAccountID();
	deposit = 0;
	bonusValue = 10;
	// The following variable is used in the implementation of performTransaction() in the Tranasction class.
	accountType = SAVINGS;
}

bool SavingsAccount::withdrawMoney(Money amount) {
	// Withdraw amount from Savings Account, unless the amount being subtracted is greater than the balance of the 
	//	Savings Account or the amount is negative.
	if ((amount.asCents() >= 0) && (amount.asCents() <= balanceSA.asCents())) {
		balanceSA.subtract(amount);
		// Decrease the bonus value by $2 for each successful withdrawal, ensuring it doesn't fall below 0.
		if ((bonusValue - 2) >= 0) {
			bonusValue -= 2;
		} else {
			bonusValue = 0;
		}
		// Pass the Savings Account balance to the Account class;
		accountBalance = balanceSA;
		return true;
	} else {
		return false;
	}
}

bool SavingsAccount::depositMoney(Money amount) {
	// Deposit amount into Savings Account, unless the amount to be deposited is negative.
	if (amount.asCents() >= 0) {
		balanceSA.add(amount);
		deposit++;
		// Add bonus value to the Savings Account balance on every second successful deposit.
		if (deposit % 2 == 0) {
			balanceSA.addDollars(bonusValue);
		}
		// Pass the Savings Account balance to the Account class;
		accountBalance = balanceSA;
		return true;
	} else {
		return false;
	}
}

Money SavingsAccount::getBonusValue() const {
	Money bonusValueSA(bonusValue, 0);
	return bonusValueSA;
}

// revertWithdrawal is a helper method that is called in performTransaction() from the Transaction class.
// It reverts the Savings Account balance and its bonus value to their original values after a successful 
//	withdrawal but an unsuccessful deposit in performTransaction().
void SavingsAccount::revertWithdrawal(Money amount) {
	balanceSA.add(amount);
	accountBalance = balanceSA;
	bonusValue += 2;
	Money bonusValueSA(bonusValue, 0);
}

SavingsAccount::~SavingsAccount() {
}


