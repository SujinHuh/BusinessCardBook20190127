//BusinessCard.cpp
#include "BusinessCard.h"

BusinessCard::BusinessCard() {
}

BusinessCard::BusinessCard(string name, string telephoneNumber, string emailAddress, string position, string companyName, string address, string companyTelephoneNumber, string faxNumber, string url)
	:personal(name,telephoneNumber,emailAddress,position),company(companyName,address,companyTelephoneNumber,faxNumber,url) {
}

BusinessCard::BusinessCard(const BusinessCard & source)
	:personal(source.personal),company(source.company) {
}

BusinessCard::~BusinessCard() {
}

bool BusinessCard::IsEqual(const BusinessCard & other) {
	bool ret = false;

	if (this->personal.IsEqual(other.personal) == true && this->company.IsEqual(other.company) == true) {
		ret = true;
	}
	
	return ret;
}

bool BusinessCard::IsNotEqual(const BusinessCard & other) {
	bool ret = false;

	if (this->personal.IsNotEqual(other.personal) == true && this->company.IsNotEqual(other.company) == true) {
		ret = true;
	}

	return ret;
}

BusinessCard & BusinessCard::operator=(const BusinessCard & source) {
	
	this->personal = source.personal;
	this->company = source.company;

	return *this;
}

bool BusinessCard::operator==(const BusinessCard & other) {
	bool ret = false;

	if (this->personal == other.personal&&this->company == other.company) {
		ret = true;
	}
	
	return ret;
}

bool BusinessCard::operator!=(const BusinessCard & other) {
	bool ret = false;

	if (this->personal != other.personal || this->company != other.company) {
		ret = true;
	}

	return ret;
}
