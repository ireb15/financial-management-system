#ifndef ACCOUNT_HPP_
#define ACCOUNT_HPP_
#include "Money.hpp"

// The following type is used in the implementation of performTransaction() in the Transaction class.
enum account {
	SAVINGS,
	CHEQUE,
	CREDIT
};

class Account{
protected:
	int customerID;
	int accountID;
	static int incrementAccountID;
	Money accountBalance;
private:
	Account& operator=(const Account &other);
	Account(const Account &other);
public:
	// accountType (of type account) is a variable that represents the type of account.
	//	It is used in the implementation of performTransaction() from the Transaction
	//	class.
	account accountType;
	Account(const int customerID);
	virtual bool withdrawMoney(Money amount) = 0;
	virtual bool depositMoney(Money amount) = 0;
	int getCustomerID() const;
	int getAccountID() const;
	Money getBalance() const;
	// revertWithdrawal is a helper method that is called in performTransaction() from 
	//	the Transaction class.
	virtual void revertWithdrawal(Money amount) = 0;
	virtual ~Account();
};

#endif /* ACCOUNT_HPP_ */
