//TakeInForm.cpp
#include "TakeInForm.h"
#include "BusinessCardBookForm.h"
#include "BusinessCardBook.h"

BEGIN_MESSAGE_MAP(TakeInForm,CDialog)
	ON_BN_CLICKED(IDC_BUTTON_TAKEIN,OnTakeInButtonClicked)
	ON_EN_KILLFOCUS(IDC_EDIT_COMPANY_NAME,OnCompanyNameKillFocus)
	ON_WM_CLOSE()
	END_MESSAGE_MAP()

TakeInForm::TakeInForm(CWnd * parent)
	:CDialog(TakeInForm::IDD,parent) {
}

BOOL TakeInForm::OnInitDialog() {
	CDialog::OnInitDialog();
	((CComboBox*)GetDlgItem(IDC_COMBO_PERSONAL_EMAILADDRESS))->AddString("gmail.com");
	((CComboBox*)GetDlgItem(IDC_COMBO_PERSONAL_EMAILADDRESS))->AddString("naver.com");
	((CComboBox*)GetDlgItem(IDC_COMBO_PERSONAL_EMAILADDRESS))->AddString("hanmail.net");
	((CComboBox*)GetDlgItem(IDC_COMBO_PERSONAL_EMAILADDRESS))->AddString("parkcom.com");

	((CComboBox*)GetDlgItem(IDC_COMBO_PERSONAL_POSITION))->AddString("사원");
	((CComboBox*)GetDlgItem(IDC_COMBO_PERSONAL_POSITION))->AddString("대리");
	((CComboBox*)GetDlgItem(IDC_COMBO_PERSONAL_POSITION))->AddString("과장");
	((CComboBox*)GetDlgItem(IDC_COMBO_PERSONAL_POSITION))->AddString("사장");
	
	return FALSE;
}

void TakeInForm::OnTakeInButtonClicked() {
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

	GetDlgItem(IDC_EDIT_PERSONAL_NAME)->GetWindowText(name);
	GetDlgItem(IDC_EDIT_PERSONAL_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
	GetDlgItem(IDC_EDIT_PERSONAL_EMAILADDRESS)->GetWindowText(emailAddress);
	GetDlgItem(IDC_COMBO_PERSONAL_EMAILADDRESS)->GetWindowText(domain);
	emailAddress.Format("%s@%s", (LPCTSTR)emailAddress, (LPCTSTR)domain);
	GetDlgItem(IDC_COMBO_PERSONAL_POSITION)->GetWindowText(position);

	GetDlgItem(IDC_EDIT_COMPANY_NAME)->GetWindowText(companyName);
	GetDlgItem(IDC_EDIT_COMPANY_ADDRESS)->GetWindowText(address);
	GetDlgItem(IDC_EDIT_COMPANY_TELEPHONENUMBER)->GetWindowText(companyTelephoneNumber);
	GetDlgItem(IDC_EDIT_COMPANY_FAXNUMBER)->GetWindowText(faxNumber);
	GetDlgItem(IDC_EDIT_COMPANY_URL)->GetWindowText(url);

	BusinessCard businessCard((LPCTSTR)name, (LPCTSTR)telephoneNumber, (LPCTSTR)emailAddress, (LPCTSTR)position, (LPCTSTR)companyName, (LPCTSTR)address,
		(LPCTSTR)companyTelephoneNumber, (LPCTSTR)faxNumber, (LPCTSTR)url);

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
	businessCardBookForm->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER_TEXT)->SetWindowText(emailAddress);
	businessCardBookForm->GetDlgItem(IDC_STATIC_COMPANY_URL_TEXT)->SetWindowText(url);

	EndDialog(0);
}

void TakeInForm::OnCompanyNameKillFocus() {
	BusinessCardBookForm *businessCardBookForm;
	BusinessCard *index;
	CString companyName;
	CString address;
	CString companyTelephoneNumber;
	CString faxNumber;
	CString url;

	GetDlgItem(IDC_EDIT_COMPANY_NAME)->GetWindowText(companyName);

	businessCardBookForm = (BusinessCardBookForm*)(CWnd::FindWindow("#32770", "명함철"));

	index = businessCardBookForm->businessCardBook->FindByCompanyName((LPCTSTR)companyName);
	if (index != NULL) {
		address = CString(index->GetAddress().c_str());
		companyTelephoneNumber = CString(index->GetCompanyTelephoneNumber().c_str());
		faxNumber = CString(index->GetFaxNumber().c_str());
		url = CString(index->GetUrl().c_str());

		GetDlgItem(IDC_EDIT_COMPANY_ADDRESS)->SetWindowText(address);
		GetDlgItem(IDC_EDIT_COMPANY_TELEPHONENUMBER)->SetWindowText(companyTelephoneNumber);
		GetDlgItem(IDC_EDIT_COMPANY_FAXNUMBER)->SetWindowText(faxNumber);
		GetDlgItem(IDC_EDIT_COMPANY_URL)->SetWindowText(url);
	}
}

void TakeInForm::OnClose() {
	EndDialog(0);
}
