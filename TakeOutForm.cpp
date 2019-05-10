//TakeOutForm.cpp
#include "TakeOutForm.h"
#include "BusinessCardBookForm.h"
#include "BusinessCardBook.h"


BEGIN_MESSAGE_MAP(TakeOutForm,CDialog)
	ON_WM_CLOSE()
	END_MESSAGE_MAP()

TakeOutForm::TakeOutForm(CWnd * parent) :CDialog(TakeOutForm::IDD, parent) {
}

BOOL TakeOutForm::OnInitDialog() {
	CDialog::OnInitDialog(); //오버라이딩
	BusinessCardBookForm *businessCardBookForm;
	BusinessCard businessCard;
	BusinessCard *index;

	//1.1 명함철 윈도우를 찾는다.
	businessCardBookForm = (BusinessCardBookForm*)(CWnd::FindWindow("#32770", "명함철"));
	
	//1.2 명함철 윈도우의 명함철에서 뺀다.
	index = businessCardBookForm->businessCardBook->GetCurrent();
	businessCard = businessCardBookForm->businessCardBook->TakeOut(index);
	businessCardBookForm->Delete(&businessCard);
	//1.3 명함철의 개인의 이름, 전화번호, 이메일주소, 직급, 회사의 상호, 주소, 전화번호, 팩스번호, url을 빼기 윈도우에 출력한다.
	GetDlgItem(IDC_STATIC_PERSONAL_NAME_TEXT)->SetWindowText(businessCard.GetName().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER_TEXT)->SetWindowText(businessCard.GetTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS_TEXT)->SetWindowText(businessCard.GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION_TEXT)->SetWindowText(businessCard.GetPosition().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_NAME_TEXT)->SetWindowText(businessCard.GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS_TEXT)->SetWindowText(businessCard.GetAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_TELEPOHNENUMBER_TEXT)->SetWindowText(businessCard.GetCompanyTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_HOMEPAGE)->SetWindowText(businessCard.GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_URL_TEXT)->SetWindowText(businessCard.GetUrl().c_str());

	//1.4 명함철윈도우의 명함에 명함이 있으면 현재위치의 명함을 출력한다.
	if (businessCardBookForm->businessCardBook->GetCurrent() != NULL) {
		businessCardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_NAME_TEXT)->SetWindowText(businessCardBookForm->businessCardBook->GetCurrent()->GetName().c_str());
		businessCardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER_TEXT)->SetWindowText(businessCardBookForm->businessCardBook->GetCurrent()->GetTelephoneNumber().c_str());
		businessCardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS_TEXT)->SetWindowText(businessCardBookForm->businessCardBook->GetCurrent()->GetEmailAddress().c_str());
		businessCardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_POSITION_TEXT)->SetWindowText(businessCardBookForm->businessCardBook->GetCurrent()->GetPosition().c_str());
		businessCardBookForm->GetDlgItem(IDC_STATIC_COMPANY_NAME_TEXT)->SetWindowText(businessCardBookForm->businessCardBook->GetCurrent()->GetCompanyName().c_str());
		businessCardBookForm->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS_TEXT)->SetWindowText(businessCardBookForm->businessCardBook->GetCurrent()->GetAddress().c_str());
		businessCardBookForm->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER_TEXT)->SetWindowText(businessCardBookForm->businessCardBook->GetCurrent()->GetCompanyTelephoneNumber().c_str());
		businessCardBookForm->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER_TEXT)->SetWindowText(businessCardBookForm->businessCardBook->GetCurrent()->GetFaxNumber().c_str());
		businessCardBookForm->GetDlgItem(IDC_STATIC_COMPANY_URL_TEXT)->SetWindowText(businessCardBookForm->businessCardBook->GetCurrent()->GetUrl().c_str());
	}
	else {
		businessCardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_NAME_TEXT)->SetWindowText("");
		businessCardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER_TEXT)->SetWindowText("");
		businessCardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS_TEXT)->SetWindowText("");
		businessCardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_POSITION_TEXT)->SetWindowText("");
		businessCardBookForm->GetDlgItem(IDC_STATIC_COMPANY_NAME_TEXT)->SetWindowText("");
		businessCardBookForm->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS_TEXT)->SetWindowText("");
		businessCardBookForm->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER_TEXT)->SetWindowText("");
		businessCardBookForm->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER_TEXT)->SetWindowText("");
		businessCardBookForm->GetDlgItem(IDC_STATIC_COMPANY_URL_TEXT)->SetWindowText("");
	}

	return FALSE;
}

void TakeOutForm::OnClose() {
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
	int messageBox;

	messageBox = MessageBox((LPCTSTR)"명함을 끼우겠습니까?", (LPCTSTR)"확인", MB_YESNOCANCEL);
	switch (messageBox) {
	case IDYES: {
		GetDlgItem(IDC_STATIC_PERSONAL_NAME_TEXT)->GetWindowText(name);
		GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER_TEXT)->GetWindowText(telephoneNumber);
		GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS_TEXT)->GetWindowText(emailAddress);
		GetDlgItem(IDC_STATIC_PERSONAL_POSITION_TEXT)->GetWindowText(position);
		GetDlgItem(IDC_STATIC_COMPANY_NAME_TEXT)->GetWindowText(companyName);
		GetDlgItem(IDC_STATIC_COMPANY_ADDRESS_TEXT)->GetWindowText(address);
		GetDlgItem(IDC_STATIC_COMPANY_TELEPOHNENUMBER_TEXT)->GetWindowText(companyTelephoneNumber);
		GetDlgItem(IDC_STATIC_COMPANY_HOMEPAGE)->GetWindowText(faxNumber);
		GetDlgItem(IDC_STATIC_COMPANY_URL_TEXT)->GetWindowText(url);

		BusinessCard businessCard((LPCTSTR)name, (LPCTSTR)telephoneNumber, (LPCTSTR)emailAddress, (LPCTSTR)position, (LPCTSTR)companyName, (LPCTSTR)address, (LPCTSTR)companyTelephoneNumber, (LPCTSTR)faxNumber, (LPCTSTR)url);

		businessCardBookForm = (BusinessCardBookForm*)(CWnd::FindWindow("#32770", "명함철"));

		index = businessCardBookForm->businessCardBook->TakeIn(businessCard);
		businessCardBookForm->Insert(index);
		
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
		businessCardBookForm->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER_TEXT)->SetWindowText(faxNumber);
		businessCardBookForm->GetDlgItem(IDC_STATIC_COMPANY_URL_TEXT)->SetWindowText(url);

		EndDialog(0); break; 
	}
	case IDNO:
		EndDialog(0); break;
	default:
		break;
	}
}
