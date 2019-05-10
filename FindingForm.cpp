//FindingForm.cpp
#include "FindingForm.h"
#include "BusinessCardBookForm.h"
#include "BusinessCardBook.h"

BEGIN_MESSAGE_MAP(FindingForm,CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIND,OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIRST,OnFirstButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS,OnPreviousButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_NEXT,OnNextButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_LAST,OnLastButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_SELECT,OnSelectButtonClicked)
	ON_WM_CLOSE()
	ON_STN_CLICKED(IDC_STATIC_PERSONAL_EMAILADDRESS_TEXT, &FindingForm::OnStnClickedStaticPersonalEmailaddressText)
END_MESSAGE_MAP()

FindingForm::FindingForm(CWnd * parent)
	:CDialog(FindingForm::IDD,parent) {

	this->indexes = NULL;
	this->current = 0;
	this->count = -1;
}

void FindingForm::OnFindButtonClicked() {
	BusinessCardBookForm *businessCardBookForm;
	CString name;
	CString telephoneNumber;
	CString emailAddress;
	CString position;
	CString companyName;
	CString address;
	CString companyTelephoneNumber;
	CString faxNumber;
	CString url;

	GetDlgItem(IDC_EDIT_CONDITION_NAME)->GetWindowText(name);

	businessCardBookForm = (BusinessCardBookForm*)(CWnd::FindWindow("#32770", "명함철"));

	if (this->indexes != NULL) {
		delete[] this->indexes;
		this->indexes = NULL;
	}

	businessCardBookForm->businessCardBook->Find((LPCTSTR)name, &(this->indexes), &(this->count));

	if (this->count > 0) {
		this->current = 0;
		name = CString(this->indexes[this->current]->GetName().c_str());
		telephoneNumber = CString(this->indexes[this->current]->GetTelephoneNumber().c_str());
		emailAddress = CString(this->indexes[this->current]->GetEmailAddress().c_str());
		position = CString(this->indexes[this->current]->GetPosition().c_str());
		companyName = CString(this->indexes[this->current]->GetCompanyName().c_str());
		address = CString(this->indexes[this->current]->GetAddress().c_str());
		companyTelephoneNumber = CString(this->indexes[this->current]->GetCompanyTelephoneNumber().c_str());
		faxNumber = CString(this->indexes[this->current]->GetFaxNumber().c_str());
		url = CString(this->indexes[this->current]->GetUrl().c_str());

		GetDlgItem(IDC_STATIC_PERSONAL_NAME_TEXT)->SetWindowText(name);
		GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER_TEXT)->SetWindowText(telephoneNumber);
		GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS_TEXT)->SetWindowText(emailAddress);
		GetDlgItem(IDC_STATIC_PERSONAL_POSITION_TEXT)->SetWindowText(position);
		GetDlgItem(IDC_STATIC_COMPANY_NAME_TEXT)->SetWindowText(companyName);
		GetDlgItem(IDC_STATIC_COMPANY_ADDRESS_TEXT)->SetWindowText(address);
		GetDlgItem(IDC_STATIC_COMPANY_TELEPOHNENUMBER_TEXT)->SetWindowText(companyTelephoneNumber);
		GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER_TEXT)->SetWindowText(faxNumber);
		GetDlgItem(IDC_STATIC_COMPANY_HOMEPAGE_TEXT)->SetWindowText(url);


	}
	else {//공백처리
		GetDlgItem(IDC_STATIC_PERSONAL_NAME_TEXT)->SetWindowText("");
		GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER_TEXT)->SetWindowText("");
		GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS_TEXT)->SetWindowText("");
		GetDlgItem(IDC_STATIC_PERSONAL_POSITION_TEXT)->SetWindowText("");
		GetDlgItem(IDC_STATIC_COMPANY_NAME_TEXT)->SetWindowText("");
		GetDlgItem(IDC_STATIC_COMPANY_ADDRESS_TEXT)->SetWindowText("");
		GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER_TEXT)->SetWindowText("");
		GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER_TEXT)->SetWindowText("");
		GetDlgItem(IDC_STATIC_COMPANY_HOMEPAGE_TEXT)->SetWindowText("");
	}
}

void FindingForm::OnFirstButtonClicked() {
	CString name;
	CString telephoneNumber;
	CString emailAddress;
	CString position;
	CString companyName;
	CString address;
	CString companyTelephoneNumber;
	CString faxNumber;
	CString url;

	this->current = 0;
	name = CString(this->indexes[this->current]->GetName().c_str());
	telephoneNumber = CString(this->indexes[this->current]->GetTelephoneNumber().c_str());
	emailAddress = CString(this->indexes[this->current]->GetEmailAddress().c_str());
	position = CString(this->indexes[this->current]->GetPosition().c_str());
	companyName = CString(this->indexes[this->current]->GetCompanyName().c_str());
	address = CString(this->indexes[this->current]->GetAddress().c_str());
	companyTelephoneNumber = CString(this->indexes[this->current]->GetCompanyTelephoneNumber().c_str());
	faxNumber = CString(this->indexes[this->current]->GetFaxNumber().c_str());
	url = CString(this->indexes[this->current]->GetUrl().c_str());

	GetDlgItem(IDC_STATIC_PERSONAL_NAME_TEXT)->SetWindowText(name);
	GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER_TEXT)->SetWindowText(telephoneNumber);
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS_TEXT)->SetWindowText(emailAddress);
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION_TEXT)->SetWindowText(position);
	GetDlgItem(IDC_STATIC_COMPANY_NAME_TEXT)->SetWindowText(companyName);
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS_TEXT)->SetWindowText(address);
	GetDlgItem(IDC_STATIC_COMPANY_TELEPOHNENUMBER_TEXT)->SetWindowText(companyTelephoneNumber);
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER_TEXT)->SetWindowText(faxNumber);
	GetDlgItem(IDC_STATIC_COMPANY_HOMEPAGE_TEXT)->SetWindowText(url);
}

void FindingForm::OnPreviousButtonClicked() {
	CString name;
	CString telephoneNumber;
	CString emailAddress;
	CString position;
	CString companyName;
	CString address;
	CString companyTelephoneNumber;
	CString faxNumber;
	CString url;

	this->current--;
	if (this->current < 0) {
		this->current = 0;
	}
	name = CString(this->indexes[this->current]->GetName().c_str());
	telephoneNumber = CString(this->indexes[this->current]->GetTelephoneNumber().c_str());
	emailAddress = CString(this->indexes[this->current]->GetEmailAddress().c_str());
	position = CString(this->indexes[this->current]->GetPosition().c_str());
	companyName = CString(this->indexes[this->current]->GetCompanyName().c_str());
	address = CString(this->indexes[this->current]->GetAddress().c_str());
	companyTelephoneNumber = CString(this->indexes[this->current]->GetCompanyTelephoneNumber().c_str());
	faxNumber = CString(this->indexes[this->current]->GetFaxNumber().c_str());
	url = CString(this->indexes[this->current]->GetUrl().c_str());

	GetDlgItem(IDC_STATIC_PERSONAL_NAME_TEXT)->SetWindowText(name);
	GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER_TEXT)->SetWindowText(telephoneNumber);
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS_TEXT)->SetWindowText(emailAddress);
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION_TEXT)->SetWindowText(position);
	GetDlgItem(IDC_STATIC_COMPANY_NAME_TEXT)->SetWindowText(companyName);
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS_TEXT)->SetWindowText(address);
	GetDlgItem(IDC_STATIC_COMPANY_TELEPOHNENUMBER_TEXT)->SetWindowText(companyTelephoneNumber);
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER_TEXT)->SetWindowText(faxNumber);
	GetDlgItem(IDC_STATIC_COMPANY_HOMEPAGE_TEXT)->SetWindowText(url);
}

void FindingForm::OnNextButtonClicked() {
	CString name;
	CString telephoneNumber;
	CString emailAddress;
	CString position;
	CString companyName;
	CString address;
	CString companyTelephoneNumber;
	CString faxNumber;
	CString url;

	this->current++;
	if (this->current >= this->count) {
		this->current = this->count - 1;
	}
	name = CString(this->indexes[this->current]->GetName().c_str());
	telephoneNumber = CString(this->indexes[this->current]->GetTelephoneNumber().c_str());
	emailAddress = CString(this->indexes[this->current]->GetEmailAddress().c_str());
	position = CString(this->indexes[this->current]->GetPosition().c_str());
	companyName = CString(this->indexes[this->current]->GetCompanyName().c_str());
	address = CString(this->indexes[this->current]->GetAddress().c_str());
	companyTelephoneNumber = CString(this->indexes[this->current]->GetCompanyTelephoneNumber().c_str());
	faxNumber = CString(this->indexes[this->current]->GetFaxNumber().c_str());
	url = CString(this->indexes[this->current]->GetUrl().c_str());

	GetDlgItem(IDC_STATIC_PERSONAL_NAME_TEXT)->SetWindowText(name);
	GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER_TEXT)->SetWindowText(telephoneNumber);
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS_TEXT)->SetWindowText(emailAddress);
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION_TEXT)->SetWindowText(position);
	GetDlgItem(IDC_STATIC_COMPANY_NAME_TEXT)->SetWindowText(companyName);
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS_TEXT)->SetWindowText(address);
	GetDlgItem(IDC_STATIC_COMPANY_TELEPOHNENUMBER_TEXT)->SetWindowText(companyTelephoneNumber);
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER_TEXT)->SetWindowText(faxNumber);
	GetDlgItem(IDC_STATIC_COMPANY_HOMEPAGE_TEXT)->SetWindowText(url);
}

void FindingForm::OnLastButtonClicked() {
	CString name;
	CString telephoneNumber;
	CString emailAddress;
	CString position;
	CString companyName;
	CString address;
	CString companyTelephoneNumber;
	CString faxNumber;
	CString url;

	this->current = this->count - 1;
	name = CString(this->indexes[this->current]->GetName().c_str());
	telephoneNumber = CString(this->indexes[this->current]->GetTelephoneNumber().c_str());
	emailAddress = CString(this->indexes[this->current]->GetEmailAddress().c_str());
	position = CString(this->indexes[this->current]->GetPosition().c_str());
	companyName = CString(this->indexes[this->current]->GetCompanyName().c_str());
	address = CString(this->indexes[this->current]->GetAddress().c_str());
	companyTelephoneNumber = CString(this->indexes[this->current]->GetCompanyTelephoneNumber().c_str());
	faxNumber = CString(this->indexes[this->current]->GetFaxNumber().c_str());
	url = CString(this->indexes[this->current]->GetUrl().c_str());

	GetDlgItem(IDC_STATIC_PERSONAL_NAME_TEXT)->SetWindowText(name);
	GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER_TEXT)->SetWindowText(telephoneNumber);
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS_TEXT)->SetWindowText(emailAddress);
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION_TEXT)->SetWindowText(position);
	GetDlgItem(IDC_STATIC_COMPANY_NAME_TEXT)->SetWindowText(companyName);
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS_TEXT)->SetWindowText(address);
	GetDlgItem(IDC_STATIC_COMPANY_TELEPOHNENUMBER_TEXT)->SetWindowText(companyTelephoneNumber);
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER_TEXT)->SetWindowText(faxNumber);
	GetDlgItem(IDC_STATIC_COMPANY_HOMEPAGE_TEXT)->SetWindowText(url);
}

void FindingForm::OnSelectButtonClicked() {
	BusinessCardBookForm *businessCardBookForm;
	BusinessCard *index;
	CString name;
	CString telephoneNumber;
	CString emailAddress;
	CString position;
	CString companyName;
	CString address;
	CString companyTelephoneNumber;
	CString faxNumber;
	CString url;
	CString domain;

	businessCardBookForm = (BusinessCardBookForm*)(CWnd::FindWindow("#32770", "명함철"));

	index = businessCardBookForm->businessCardBook->Move(this->indexes[this->current]);
	name = CString(index->GetName().c_str());
	telephoneNumber = CString(index->GetTelephoneNumber().c_str());
	emailAddress = CString(index->GetEmailAddress().c_str());
	position = CString(index->GetPosition().c_str());
	companyName = CString(index->GetCompanyName().c_str());
	address = CString(index->GetAddress().c_str());
	companyTelephoneNumber = CString(index->GetCompanyTelephoneNumber().c_str());
	faxNumber = CString(index->GetFaxNumber().c_str());
	url = CString(index->GetUrl().c_str());

	businessCardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_NAME_TEXT)->SetWindowText(name);
	businessCardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER_TEXT)->SetWindowText(telephoneNumber);
	businessCardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS_TEXT)->SetWindowText(emailAddress);
	businessCardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_POSITION_TEXT)->SetWindowText(position);
	businessCardBookForm->GetDlgItem(IDC_STATIC_COMPANY_NAME_TEXT)->SetWindowText(companyName);
	businessCardBookForm->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS_TEXT)->SetWindowText(address);
	businessCardBookForm->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER_TEXT)->SetWindowText(companyTelephoneNumber);
	businessCardBookForm->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER_TEXT)->SetWindowText(emailAddress);
	businessCardBookForm->GetDlgItem(IDC_STATIC_COMPANY_URL_TEXT)->SetWindowText(url);

	if (this->indexes != NULL) {
		delete[] this->indexes;
	}
	EndDialog(0);
}

void FindingForm::OnClose() {

	if (this->indexes != NULL) {
		delete[] this->indexes;
	}
	EndDialog(0);
}


void FindingForm::OnStnClickedStaticPersonalEmailaddressText()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
