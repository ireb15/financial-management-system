#include "FinancialServicesSystem.hpp"
#include <iostream>
#include <vector>

FinancialServicesSystem::FinancialServicesSystem() {
}

std::string FinancialServicesSystem::author(){
	return "ireb692";
}

bool FinancialServicesSystem::addCustomer(Customer* customer) {
	unsigned int i;
	int present = 0;
	// Check if the customer's customer ID is already stored in the financial management system.
	// If it isn't already stored, store it.
	for (i = 0; i < listOfCustomers.size(); i++) {
		if (listOfCustomers[i]->getID() == customer->getID()) {
			present = 1;
		}
	}
	if (present == 0) {
		listOfCustomers.push_back(customer);
		return true;
	} else {
		return false;
	}
}

bool FinancialServicesSystem::addAccount(Account* account) { 
	unsigned int i, j; 
	int customerPresent = 0, accountPresent = 0;
	// Check if the customer who owns the account to be added is stored in the financial management system.
	// If the customer is not in the system, their account can't be added.
	for (i = 0; i < listOfCustomers.size(); i++) {
		if (listOfCustomers[i]->getID() == account->getCustomerID()) {
			customerPresent = 1;
		}
	}
	if (customerPresent == 0) {
		return false;
	}
	// Check if the account to be added is already stored in the financial management system.
	// If it isn't already stored, store it.
	for (j = 0; j < listOfAccounts.size(); j++) {
		if (listOfAccounts[j]->getAccountID() == account->getAccountID()) {
			accountPresent = 1;
		}
	}
	if (accountPresent == 0) {
		listOfAccounts.push_back(account);
		return true;
	} else {
		return false;
	}
}

bool FinancialServicesSystem::addTransaction(Transaction* transaction) {
	unsigned int i, j;
	int transactionPresent = 0, accountsPresent = 0;
	// Check if the transaction being passed is a pending transaction.
	if (transaction->getState() == PENDING) {
		// Check if the transaction being passed is already present in the financial management system.
		// If it is already stored, it can't be stored again.
		for (i = 0; i < listOfTransactions.size(); i++) {
			if (listOfTransactions[i]->getID() == transaction->getID()) {
				transactionPresent = 1;
			}
		}
		// Check if the fromAccount and toAccount of the transaction being passed are stored in the 
		//	financial management system.
		// If they're not already stored, the transaction can't be stored.
		for (j = 0; j < listOfAccounts.size(); j++) {
			if ((listOfAccounts[j]->getAccountID() == transaction->getFromAccount()->getAccountID()) || (listOfAccounts[j]->getAccountID() == transaction->getToAccount()->getAccountID())) {
				accountsPresent++;
			}
		}
		// If all of the above conditions are met, the transaction is added to the financial management system.
		if ((transactionPresent == 0 && (accountsPresent == 2))) {
			listOfTransactions.push_back(transaction);
			return true;
		}
	}
	return false;
} 

std::vector<Transaction*> FinancialServicesSystem::performPendingTransactions() {
	std::vector<Transaction*> pendingTransactions;
	std::vector<Transaction*> successfulTransactions;
	unsigned int i, j, k;
	Transaction* tempTransaction;
	// Check if the listOfTransactions vector has any transactions stored.
	if (listOfTransactions.size() == 0) {
		return successfulTransactions;
	}
	// Create a vector of pending transactions from the main vector of transactions.
	for (i = 0; i < listOfTransactions.size(); i++) {
		if (listOfTransactions[i]->getState() == PENDING) {
			pendingTransactions.push_back(listOfTransactions[i]);
		}
	}
	//Sort the vector of pending transactions into ascending order of their transaction IDs.
	for (j = 0; j < pendingTransactions.size(); j++) {
		for (k = j + 1; k < pendingTransactions.size(); k++) {
			if (pendingTransactions[j]->getID() > pendingTransactions[k]->getID()) {
				tempTransaction = pendingTransactions[j];
				pendingTransactions[j] = pendingTransactions[k];
				pendingTransactions[k] = tempTransaction;
			}
		}
	}
	// Perform the pending transactions and store the completed transactions in a vector to be returned.
	for (j = 0; j < pendingTransactions.size(); j++) {
		pendingTransactions[j]->performTransaction();
		if (pendingTransactions[j]->getState() == COMPLETED) {
			successfulTransactions.push_back(pendingTransactions[j]);
		}
	}
	return successfulTransactions;
}

Money FinancialServicesSystem::getCustomerBalance(int customerID) const {
	std::vector<Account*> tempListOfCustomerAccounts;
	Money tempBalance, customerBalance;
	// Create a vector that stores all of the customer's accounts that are stored in the financial management
	// system.
	unsigned int i, j;
	for (i = 0; i < listOfAccounts.size(); i++) {
		if (listOfAccounts[i]->getCustomerID() == customerID) {
			tempListOfCustomerAccounts.push_back(listOfAccounts[i]);
		}
	}
	// Add the balances of the customer's accounts together and return the total balance.
	for (j = 0; j < tempListOfCustomerAccounts.size(); j++) {
		if (tempListOfCustomerAccounts[j]->getBalance().asCents() < 0) {
			customerBalance.subtractCents(tempListOfCustomerAccounts[j]->getBalance().asCents() * -1);
		} else {
			tempBalance = tempListOfCustomerAccounts[j]->getBalance();
			customerBalance.add(tempBalance);
		}
	}
	return customerBalance;
}

bool FinancialServicesSystem::verifyCustomer(int customerID) const {
	unsigned int i;
	// Check if customer's customer ID is already stored in the financial management system.
	for (i = 0; i < listOfCustomers.size(); i++) {
		if (listOfCustomers[i]->getID() == customerID) {
			return true;
		}
	}
	return false;
}

bool FinancialServicesSystem::verifyAccount(int accountID) const {
	unsigned int i;
	// Check if the account's account ID is already stored in the financial management system.
	for (i = 0; i < listOfAccounts.size(); i++) {
		if (listOfAccounts[i]->getAccountID() == accountID) {
			return true;
		}
	}
	return false;
}

bool FinancialServicesSystem::verifyTransaction(int transactionID) const {
	unsigned int i;
	// Check if the transaction's transaction ID is already stored in the financial management system.
	for (i = 0; i < listOfTransactions.size(); i++) {
		if (listOfTransactions[i]->getID() == transactionID) {
			return true;
		}
	}
	return false;
}

std::vector<Account*> FinancialServicesSystem::getAccounts() const {
	return listOfAccounts;
}

std::vector<Customer*> FinancialServicesSystem::getCustomers() const {
	return listOfCustomers;
}

std::vector<Transaction*> FinancialServicesSystem::getTransactions() const {
	return listOfTransactions;
}

std::vector<Transaction*> FinancialServicesSystem::getTransactions(TransactionState state) const {
	std::vector<Transaction*> tempListOfTransactions;
	unsigned int i;
	// Create a vector that only stores transactions of the specified type and return that vector. 
	for (i = 0; i < listOfTransactions.size(); i++) {
		if (listOfTransactions[i]->getState() == state) {
			tempListOfTransactions.push_back(listOfTransactions[i]);
		}
	}
	return tempListOfTransactions;
}

FinancialServicesSystem::~FinancialServicesSystem() {
}

