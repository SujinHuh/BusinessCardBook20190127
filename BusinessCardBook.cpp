//BusinessCardBook.cpp
#include "BusinessCardBook.h"

BusinessCardBook::BusinessCardBook() {
	this->length = 0;
	this->current = 0;
}

BusinessCardBook::BusinessCardBook(const BusinessCardBook & source) :businessCards(source.businessCards) {
	this->length = source.length;
	this->current = &(this->businessCards.GetCurrent()->GetObject());
}

BusinessCardBook::~BusinessCardBook() {
}

BusinessCard * BusinessCardBook::TakeIn(BusinessCard businessCard) {
	LinkedList<BusinessCard>::Node *node;

	node = this->businessCards.AppendFromTail(businessCard);
	this->length++;
	this->current = &(node->GetObject());
	
	
	return this->current;
}

BusinessCard BusinessCardBook::TakeOut(BusinessCard * index) {
	BusinessCard businessCard;
	LinkedList<BusinessCard>::Node *node;

	node = this->businessCards.LinearSeachUnique(index, CompareBusinessCards);
	businessCard = node->GetObject();
	node = this->businessCards.Delete(node);
	this->length--;
	if (this->businessCards.GetCurrent() != 0) {
		this->current = &(this->businessCards.GetCurrent()->GetObject());
	}
	else {
		this->current = 0;
	}

	return businessCard;
}

void BusinessCardBook::Find(string name, BusinessCard **(*indexes), Long * count) {
	LinkedList<BusinessCard>::Node *(*nodes);
	Long i = 0;
	*indexes = 0;

	this->businessCards.LinearSeachDuplicate(&name, &nodes, count, CompareNames);
	if (*count > 0) {
		*indexes = new BusinessCard*[*count];
	}
	while (i < *count) {
		(*indexes)[i] = &(nodes[i]->GetObject());
		i++;
	}
}

BusinessCard * BusinessCardBook::First() {
	LinkedList<BusinessCard>::Node *node;

	node = this->businessCards.First();
	this->current = &(node->GetObject());
	
	return this->current;
}

BusinessCard * BusinessCardBook::Previous() {
	LinkedList<BusinessCard>::Node *node;

	node = this->businessCards.Previous();
	this->current = &(node->GetObject());

	return this->current;
}

BusinessCard * BusinessCardBook::Next() {
	LinkedList<BusinessCard>::Node *node;

	node = this->businessCards.Next();
	this->current = &(node->GetObject());

	return this->current;
}

BusinessCard * BusinessCardBook::Last() {
	LinkedList<BusinessCard>::Node *node;

	node = this->businessCards.Last();
	this->current = &(node->GetObject());

	return this->current;
}

BusinessCard * BusinessCardBook::Move(BusinessCard * index) {
	LinkedList<BusinessCard>::Node *node;

	node = this->businessCards.LinearSeachUnique(index, CompareBusinessCards);
	node = this->businessCards.Move(node);
	this->current = &(node->GetObject());

	return this->current;
}

BusinessCard * BusinessCardBook::FindByCompanyName(string companyName) {
	LinkedList<BusinessCard>::Node *node;
	BusinessCard* index = 0;
	node = this->businessCards.LinearSeachUnique(&companyName, CompareCompanyNames);
	if (node != 0) {
		index = &(node->GetObject());
	}
	return index;
}

BusinessCardBook & BusinessCardBook::operator=(const BusinessCardBook & source) {
	
	this->businessCards = source.businessCards;
	this->length = source.length;
	this->current = &(this->businessCards.GetCurrent()->GetObject());

	return *this;
}
/*
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	BusinessCardBook businessCardBook;
	BusinessCard businessCard;
	BusinessCard *(*indexes);
	BusinessCard *index;
	Long count;
	Long i = 0;
	cout << "첫번째 명함" << endl;
	businessCard = BusinessCard("홍길동", "0101111", "hong@", "대리", "박컴", "서초", "021111", "031111", "park.com");
	index = businessCardBook.TakeIn(businessCard);
	cout << index->GetName() << " " << index->GetTelephoneNumber() << " " << index->GetEmailAddress() << " " << index->GetPosition() << " " << index->GetCompanyName() << " " << index->GetAddress() << " " << index->GetCompanyTelephoneNumber() << " " << index->GetFaxNumber() << " " << index->GetUrl() << endl;
	cout << "두번째 명함" << endl;
	businessCard = BusinessCard("이길동", "0102222", "lee@", "과장", "삼성", "강남", "02222", "032222", "samsung.com");
	index = businessCardBook.TakeIn(businessCard);
	cout << index->GetName() << "" << index->GetTelephoneNumber() << "" << index->GetEmailAddress() << " " << index->GetPosition() << " " << index->GetCompanyName() << "" << index->GetAddress() << "" << index->GetCompanyTelephoneNumber() << " " << index->GetFaxNumber() << " " << index->GetUrl() << endl;
	cout << "세번째 명함" << endl;
	businessCard = BusinessCard("이길동", "0103333", "lee2@", "부장", "삼성", "강남", "02222", "032222", "samsung.com");
	index = businessCardBook.TakeIn(businessCard);
	cout << index->GetName() << "" << index->GetTelephoneNumber() << "" << index->GetEmailAddress() << " " << index->GetPosition() << " " << index->GetCompanyName() << "" << index->GetAddress() << " " << index->GetCompanyTelephoneNumber() << " " << index->GetFaxNumber() << " " << index->GetUrl() << endl;
	cout << "Find" << endl;
	businessCardBook.Find("이길동", &indexes, &count);
	while (i < count) {
		cout << indexes[i]->GetName() << " " << indexes[i]->GetTelephoneNumber() << " " << indexes[i]->GetEmailAddress() << " " << indexes[i]->GetPosition() << " " << indexes[i]->GetCompanyName() << " " << indexes[i]->GetAddress() << " " << indexes[i]->GetCompanyTelephoneNumber() << " " << indexes[i]->GetFaxNumber() << " " << indexes[i]->GetUrl() << endl;
		i++;
	}
	cout << "Move" << endl;
	index = businessCardBook.Move(indexes[0]);
	cout << index->GetName() << " " << index->GetTelephoneNumber() << " " << index->GetEmailAddress() << " " << index->GetPosition() << " " << index->GetCompanyName() << " " << index->GetAddress() << " " << index->GetCompanyTelephoneNumber() << " " << index->GetFaxNumber() << " " << index->GetUrl() << endl;
	if (indexes != 0) {
		delete[] indexes;
	}
	cout << "First" << endl;
	index = businessCardBook.First();
	cout << index->GetName() << " " << index->GetTelephoneNumber() << " " << index->GetEmailAddress() << " " << index->GetPosition() << " " << index->GetCompanyName() << " " << index->GetAddress() << " " << index->GetCompanyTelephoneNumber() << " " << index->GetFaxNumber() << " " << index->GetUrl() << endl;
	cout << "Next" << endl;
	index = businessCardBook.Next();
	cout << index->GetName() << " " << index->GetTelephoneNumber() << " " << index->GetEmailAddress() << " " << index->GetPosition() << " " << index->GetCompanyName() << " " << index->GetAddress() << " " << index->GetCompanyTelephoneNumber() << " " << index->GetFaxNumber() << " " << index->GetUrl() << endl;
	cout << "Last" << endl;
	index = businessCardBook.Last();
	cout << index->GetName() << " " << index->GetTelephoneNumber() << " " << index->GetEmailAddress() << " " << index->GetPosition() << " " << index->GetCompanyName() << " " << index->GetAddress() << " " << index->GetCompanyTelephoneNumber() << " " << index->GetFaxNumber() << " " << index->GetUrl() << endl;
	cout << "TakeOut" << endl;
	businessCard = businessCardBook.TakeOut(index);
	cout << businessCard.GetName() << " " << businessCard.GetTelephoneNumber() << " " << businessCard.GetEmailAddress() << " " << businessCard.GetPosition() << " " << businessCard.GetCompanyName() << " " << businessCard.GetAddress() << " " << businessCard.GetCompanyTelephoneNumber() << " " << businessCard.GetFaxNumber() << " " << businessCard.GetUrl() << endl;
	cout << "Previous" << endl;
	index = businessCardBook.Previous();
	cout << index->GetName() << " " << index->GetTelephoneNumber() << " " << index->GetEmailAddress() << " " << index->GetPosition() << " " << index->GetCompanyName() << " " << index->GetAddress() << " " << index->GetCompanyTelephoneNumber() << " " << index->GetFaxNumber() << " " << index->GetUrl() << endl;
	cout << "FindByCompanyName" << endl;
	index = businessCardBook.FindByCompanyName("박컴");
	cout << index->GetName() << " " << index->GetTelephoneNumber() << " " << index->GetEmailAddress() << " " << index->GetPosition() << " " << index->GetCompanyName() << " " << index->GetAddress() << " " << index->GetCompanyTelephoneNumber() << " " << index->GetFaxNumber() << " " << index->GetUrl() << endl;

	return 0;
}
*/
int CompareNames(void * one, void * other) {
	BusinessCard *one_ = static_cast<BusinessCard*>(one);
	string *other_ = static_cast<string*>(other);
	return one_->GetName().compare(*other_);
}

int CompareCompanyNames(void * one, void * other) {
	BusinessCard *one_ = static_cast<BusinessCard*>(one);
	string *other_ = static_cast<string*>(other);
	return one_->GetName().compare(*other_);
}

int CompareBusinessCards(void * one, void * other) {
	int ret = -1;

	if (one == other) {
		ret = 0;
	}

	return ret;
}
