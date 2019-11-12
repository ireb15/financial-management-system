#include "Account.hpp"

#ifndef SAVINGSACCOUNT_HPP_
#define SAVINGSACCOUNT_HPP_

class SavingsAccount : public Account {
private:
	Money balanceSA, bonusValueSA;
	int deposit, bonusValue, savingsID;
	SavingsAccount& operator=(const SavingsAccount &other);
    SavingsAccount(const SavingsAccount &other);
public:
	SavingsAccount(const int customerID);
	bool withdrawMoney(Money amount);
	bool depositMoney(Money amount);
	Money getBonusValue() const;
	// revertWithdrawal is a helper method that is called in performTransaction() from 
	//	the Transaction class.
	void revertWithdrawal(Money amount);
	virtual ~SavingsAccount();
};

#endif /* SAVINGSACCOUNT_HPP_ */
