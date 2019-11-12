#ifndef TRANSACTION_HPP_
#define TRANSACTION_HPP_

#include <string>
#include "Account.hpp"
#include "Money.hpp"

enum TransactionState {
	COMPLETED,
	PENDING,
	FAILED
};

class Transaction {
private:
	Money amount;
	int transactionID;
	static int incrementTransactionID;
	Transaction& operator=(const Transaction &other);
    Transaction(const Transaction &other);

public:
	TransactionState state;
	Account* toAccount;
	Account* fromAccount;
	Transaction(Account* fromAccount, Account* toAccount, Money amount);
	bool performTransaction();
	TransactionState getState() const;
	Money getAmount() const;
	Account* getFromAccount() const;
	Account* getToAccount() const;
	int getID() const;
	virtual ~Transaction();
};

#endif /* TRANSACTION_HPP_ */
