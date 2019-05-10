//BusinessCard.h
#ifndef _BUSINESSCARD_H
#define _BUSINESSCARD_H
#include "Personal.h"
#include "Company.h"
#include <string>
using namespace std;

class BusinessCard {
public:
	BusinessCard();
	BusinessCard(string name, string telephoneNumber, string emailAddress, string position, string companyName, string address, string companyTelephoneNumber, string faxNumber, string url);
	BusinessCard(const BusinessCard& source);
	~BusinessCard();
	bool IsEqual(const BusinessCard& other);
	bool IsNotEqual(const BusinessCard& other);
	BusinessCard& operator=(const BusinessCard& source);
	bool operator==(const BusinessCard& other);
	bool operator!=(const BusinessCard& other);
	string& GetName() const;
	string& GetTelephoneNumber() const;
	string& GetEmailAddress() const;
	string& GetPosition() const;
	string& GetCompanyName() const;
	string& GetAddress() const;
	string& GetCompanyTelephoneNumber() const;
	string& GetFaxNumber() const;
	string& GetUrl() const;

private:
	Personal personal;
	Company company;
};

inline string& BusinessCard::GetName() const {
	return const_cast<string&>(this->personal.GetName());
}

inline string & BusinessCard::GetTelephoneNumber() const {
	return const_cast<string&>(this->personal.GetTelephoneNumber());
}

inline string & BusinessCard::GetEmailAddress() const {
	return const_cast<string&>(this->personal.GetEmailAddress());
}

inline string & BusinessCard::GetPosition() const {
	return const_cast<string&>(this->personal.GetPosition());
}

inline string & BusinessCard::GetCompanyName() const {
	return const_cast<string&>(this->company.GetName());
}

inline string & BusinessCard::GetAddress() const {
	return const_cast<string&>(this->company.GetAddress());
}

inline string & BusinessCard::GetCompanyTelephoneNumber() const {
	return const_cast<string&>(this->company.GetTelephoneNumber());
}

inline string & BusinessCard::GetFaxNumber() const {
	return const_cast<string&>(this->company.GetFaxNumber());
}

inline string & BusinessCard::GetUrl() const {
	return const_cast<string&>(this->company.GetUrl());
}

#endif // !_BUSINESSCARD_H
