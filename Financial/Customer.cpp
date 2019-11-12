#include "Customer.hpp"
#include <string>

// Incrementing this variable in the Customer constructor ensures that each customer has a unique customer ID.
int Customer::incrementCustomerID = 0;

Customer::Customer(const std::string &name) {
	customerName = name;
	customerID = incrementCustomerID++;
}

std::string Customer::getName() const {
	return customerName;
}

int Customer::getID() const {
	return customerID;
}

Customer::~Customer() {
}

