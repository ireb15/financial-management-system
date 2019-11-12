#include "Account.hpp"

#ifndef CREDITACCOUNT_HPP_
#define CREDITACCOUNT_HPP_

class CreditAccount : public Account {
private:
	Money balanceCRA;
	int creditID, originalBalanceCRA;
	CreditAccount& operator=(const CreditAccount &other);
    CreditAccount(const CreditAccount &other);
public:
	CreditAccount(const int customerID);
	bool withdrawMoney(Money amount);
	bool depositMoney(Money amount);
	// revertWithdrawal is a helper method that is called in performTransaction() from 
	//	the Transaction class.
	void revertWithdrawal(Money amount);
	virtual ~CreditAccount();
};

#endif /* CREDITACCOUNT_HPP_ */
