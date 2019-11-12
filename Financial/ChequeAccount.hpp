#include "Account.hpp"

#ifndef CHEQUEACCOUNT_HPP_
#define CHEQUEACCOUNT_HPP_

class ChequeAccount : public Account {
private:
	Money balanceCHA, transactionFeeCHA;
	int chequeID;
	ChequeAccount& operator=(const ChequeAccount &other);
    ChequeAccount(const ChequeAccount &other);
public:
	ChequeAccount(const int customerID);
	bool withdrawMoney(Money amount);
	bool depositMoney(Money amount);
	Money* getTransactionFee() const;
	// revertWithdrawal is a helper method that is called in performTransaction() from 
	//	the Transaction class.
	void revertWithdrawal(Money amount);
	virtual ~ChequeAccount();
};

#endif /* CHEQUEACCOUNT_HPP_ */
