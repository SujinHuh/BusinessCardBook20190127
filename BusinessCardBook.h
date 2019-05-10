//BusinessCardBook.h
#ifndef _BUSINESSCARDBOOK_H
#define _BUSINESSCARDBOOK_H
#include "BusinessCard.h"
#include "LinkedList.h"
#include <string>

using namespace std;
typedef signed long int Long;

class BusinessCardBook {
public:
	BusinessCardBook();
	BusinessCardBook(const BusinessCardBook& source);
	~BusinessCardBook();
	BusinessCard* TakeIn(BusinessCard businessCard);
	BusinessCard TakeOut(BusinessCard *index);
	void Find(string name, BusinessCard **(*indexes), Long *count);
	BusinessCard* First();
	BusinessCard* Previous();
	BusinessCard* Next();
	BusinessCard* Last();
	BusinessCard* Move(BusinessCard *index);
	BusinessCard* FindByCompanyName(string companyName);
	//연산함수
	BusinessCardBook& operator=(const BusinessCardBook& source);
	//Get
	Long GetLength() const;
	BusinessCard* GetCurrent() const;
private:
	LinkedList<BusinessCard> businessCards;
	Long length;
	BusinessCard *current;
};

inline Long BusinessCardBook::GetLength() const {
	return this->length;
}

inline BusinessCard * BusinessCardBook::GetCurrent() const {
	return const_cast<BusinessCard*>(this->current);
}

int CompareNames(void *one, void *other);
int CompareCompanyNames(void *one, void *other);
int CompareBusinessCards(void *one, void *other);
#endif // !_BUSINESSCARDBOOK_H
