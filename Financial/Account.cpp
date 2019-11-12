#include "Account.hpp"

// Incrementing this variable in the Account constructor ensures that each account has a unique account ID.
int Account::incrementAccountID = 0;

Account::Account(const int customerID) {
	this->customerID = customerID;
	accountID = incrementAccountID++;
}

int Account::getAccountID() const {
	return accountID;
}

int Account::getCustomerID() const {
	return customerID;
}

Money Account::getBalance() const {
	return accountBalance;
}

Account::~Account() {
}

