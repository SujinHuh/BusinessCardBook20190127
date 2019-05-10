//BusinessCardBook.cpp
#include "BusinessCardBookForm.h"
#include "TakeInForm.h"
#include "TakeOutForm.h"
#include "FindingForm.h"
#include "BusinessCardBook.h"
#include <afxdb.h>

BEGIN_MESSAGE_MAP(BusinessCardBookForm,CDialog)
	ON_BN_CLICKED(IDC_BUTTON_TAKEIN,OnTakeInButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_TAKEOUT,OnTakeOutButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND,OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIRST,OnFirstButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS,OnPreviousButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_NEXT,OnNextButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_LAST,OnLastButtonClicked)
	ON_WM_CLOSE()
	END_MESSAGE_MAP()

BusinessCardBookForm::BusinessCardBookForm(CWnd *parent)
	:CDialog(BusinessCardBookForm::IDD,parent) {
	this->businessCardBook = NULL;
}

BOOL BusinessCardBookForm::OnInitDialog() {
	CDialog::OnInitDialog(); //오버라이딩
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
	
	this->businessCardBook = new BusinessCardBook;

	this->Load();
	if (this->businessCardBook->GetCurrent() != NULL) {
		index = this->businessCardBook->First();

		name = CString(index->GetName().c_str());
		telephoneNumber = CString(index->GetTelephoneNumber().c_str());
		emailAddress = CString(index->GetEmailAddress().c_str());
		position = CString(index->GetPosition().c_str());
		companyName = CString(index->GetCompanyName().c_str());
		address = CString(index->GetAddress().c_str());
		companyTelephoneNumber = CString(index->GetCompanyTelephoneNumber().c_str());
		faxNumber = CString(index->GetFaxNumber().c_str());
		url = CString(index->GetUrl().c_str());

		GetDlgItem(IDC_STATIC_PERSONAL_NAME_TEXT)->SetWindowText(name);
		GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER_TEXT)->SetWindowText(telephoneNumber);
		GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS_TEXT)->SetWindowText(emailAddress);
		GetDlgItem(IDC_STATIC_PERSONAL_POSITION_TEXT)->SetWindowText(position);
		GetDlgItem(IDC_STATIC_COMPANY_NAME_TEXT)->SetWindowText(companyName);
		GetDlgItem(IDC_STATIC_COMPANY_ADDRESS_TEXT)->SetWindowText(address);
		GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER_TEXT)->SetWindowText(companyTelephoneNumber);
		GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER_TEXT)->SetWindowText(emailAddress);
		GetDlgItem(IDC_STATIC_COMPANY_URL_TEXT)->SetWindowText(url);
	}
	
	return FALSE;
}

void BusinessCardBookForm::Load() {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.name,Personal.telephoneNumber,Personal.emailAddress,Personal.position,Company.name,Company.address,Company.telephoneNumber, "
		"Company.faxNumber,Company.url FROM Personal INNER JOIN Company ON Personal.companyCode=Company.companyCode;";

	db.OpenEx("DSN=BusinessCardBook;UID=root;PWD=rla789456");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	CString name;
	CString telephoneNumber;
	CString emailAddress;
	CString position;
	CString companyName;
	CString address;
	CString companyTelephoneNumber;
	CString faxNumber;
	CString url;

	while (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, name);
		rs.GetFieldValue((short)1, telephoneNumber);
		rs.GetFieldValue((short)2, emailAddress);
		rs.GetFieldValue((short)3, position);
		rs.GetFieldValue((short)4, companyName);
		rs.GetFieldValue((short)5, address);
		rs.GetFieldValue((short)6, companyTelephoneNumber);
		rs.GetFieldValue((short)7, faxNumber);
		rs.GetFieldValue((short)8, url);

		BusinessCard businessCard((LPCTSTR)name, (LPCTSTR)telephoneNumber, (LPCTSTR)emailAddress, (LPCTSTR)position, (LPCTSTR)companyName, (LPCTSTR)address, (LPCTSTR)companyTelephoneNumber, (LPCTSTR)faxNumber, (LPCTSTR)url);
		this->businessCardBook->TakeIn(businessCard);
		rs.MoveNext();
	}
	rs.Close();
	db.Close();
}

void BusinessCardBookForm::Save() {
	CDatabase db;
	CRecordset rs(&db);
	CRecordset rsCompany(&db);
	BusinessCard *it;
	BusinessCard *previous = NULL;
	CString code;
	CString companyCode;
	CString sql = "SELECT Personal.code,Company.companyCode FROM Personal INNER JOIN Company ON Personal.companyCode=Company.companyCode;";

	db.OpenEx("DSN=BusinessCardBook;UID=root;PWD=rla789456");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
		
	sql = "DELETE FROM Personal;";
	db.ExecuteSQL(sql);

	sql = "DELETE FROM Company;";
	db.ExecuteSQL(sql);

	//문제있는부분
	it = this->businessCardBook->First();
	while (it != previous) {
		rs.GetFieldValue((short)0, code);
		rs.GetFieldValue((short)1, companyCode);

		sql.Format("SELECT Company.companyCode FROM Company WHERE companyCode='%s';", (LPCTSTR)companyCode);
		rsCompany.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
		
		if (rsCompany.IsEOF()== TRUE) {
			CString buffer;

				buffer = CString(it->GetCompanyName().c_str());

			CString name;
			name = CString(it->GetName().c_str());


			sql.Format("INSERT INTO Company(companyCode,name,address,telephoneNumber,faxNumber,url) VALUES('%s','%s','%s','%s','%s','%s');",
				(LPCTSTR)companyCode, it->GetCompanyName().c_str(), it->GetAddress().c_str(), 
				it->GetCompanyTelephoneNumber().c_str(),
				it->GetFaxNumber().c_str(), it->GetUrl().c_str());
			db.ExecuteSQL(sql);
		}
		sql.Format("INSERT INTO Personal(code,name,telephoneNumber,emailAddress,position,companyCode) VALUES('%s','%s','%s','%s','%s', '%s');",
			(LPCTSTR)code, it->GetName().c_str(), it->GetTelephoneNumber().c_str(), it->GetEmailAddress().c_str(), it->GetPosition().c_str(), (LPCTSTR)companyCode);
		db.ExecuteSQL(sql);
		rsCompany.Close();
		rs.MoveNext();
		previous = it;
		it = this->businessCardBook->Next();
	}
	rs.Close();
	db.Close();
}

void BusinessCardBookForm::Insert(BusinessCard *index) {
	CDatabase db;
	CRecordset rs(&db);
	CString companyCode;
	CString comapanyName;
	CString sql;

	sql.Format("SELECT Company.companyCode FROM Company WHERE Company.name='%s' AND Company.address='%s' AND Company.telephoneNumber='%s' AND Company.faxNumber='%s' AND Company.url='%s';",
		index->GetCompanyName().c_str(), index->GetAddress().c_str(), index->GetCompanyTelephoneNumber().c_str(), index->GetFaxNumber().c_str(), index->GetUrl().c_str());

	db.OpenEx("DSN=BusinessCardBook;UID=root;PWD=rla789456");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	if (rs.IsEOF()== TRUE) {
		companyCode = MakeCompanyCode();
		sql.Format("INSERT INTO Company(companyCode,name,address,telephoneNumber,faxNumber,url) VALUES('%s','%s','%s','%s','%s','%s');",
			(LPCTSTR)companyCode, index->GetCompanyName().c_str(), index->GetAddress().c_str(), index->GetCompanyTelephoneNumber().c_str(), index->GetFaxNumber().c_str(), index->GetUrl().c_str());
		db.ExecuteSQL(sql);
	}
	else {
		rs.GetFieldValue((short)0, companyCode);
	}
	sql.Format("INSERT INTO Personal(code,name,telephoneNumber,emailAddress,position,companyCode) VALUES('%s','%s','%s','%s','%s','%s');",
		(LPCTSTR)MakePersonalCode(), index->GetName().c_str(), index->GetTelephoneNumber().c_str(), index->GetEmailAddress().c_str(), index->GetPosition().c_str(), (LPCTSTR)companyCode);
	db.ExecuteSQL(sql);

	rs.Close();
	db.Close();
}

void BusinessCardBookForm::Delete(BusinessCard * index) {
	CDatabase db;
	CRecordset rs(&db);
	CString code;
	CString companyCode;
	CString sql;

	sql.Format("SELECT Personal.code,Personal.companyCode FROM Personal WHERE Personal.name='%s' AND Personal.telephoneNumber='%s' AND Personal.emailAddress='%s' AND Personal.position='%s';",
		index->GetName().c_str(), index->GetTelephoneNumber().c_str(), index->GetEmailAddress().c_str(), index->GetPosition().c_str());

	db.OpenEx("DSN=BusinessCardBook;UID=root;PWD=rla789456");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	rs.GetFieldValue((short)0, code);
	rs.GetFieldValue((short)1, companyCode);

	sql.Format("DELETE FROM Personal WHERE Personal.code='%s';", (LPCTSTR)code);
	db.ExecuteSQL(sql);

	sql.Format("SELECT Personal.companyCode FROM Personal WHERE Personal.companyCode='%s';", (LPCTSTR)companyCode);
	rs.Close();
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	if (rs.IsEOF()== TRUE) {
		sql.Format("DELETE FROM Company WHERE Company.companyCode='%s';", (LPCTSTR)companyCode);
		db.ExecuteSQL(sql);
	}

	rs.Close();
	db.Close();
}

CString BusinessCardBookForm::MakePersonalCode() {
	CDatabase db;
	CRecordset rs(&db);
	int codeInt;
	CString code = "P0001";
	CString sql = "SELECT Personal.code FROM Personal ORDER BY Personal.code DESC;";

	db.OpenEx("DSN=BusinessCardBook;UID=root;PWD=rla789456");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, code);
		code = code.Right(4);
		codeInt = _ttoi(code);
		codeInt++;
		code.Format("P%04d", codeInt);
	}

	rs.Close();
	db.Close();

	return code;
	
}

CString BusinessCardBookForm::MakeCompanyCode() {
	CDatabase db;
	CRecordset rs(&db);
	int codeInt;
	CString companyCode = "C0001";
	CString sql = "SELECT Company.companyCode FROM Company ORDER BY Company.companyCode DESC;";

	db.OpenEx("DSN=BusinessCardBook;UID=root;PWD=rla789456");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, companyCode);
		companyCode = companyCode.Right(4);
		codeInt = _ttoi(companyCode);
		codeInt++;
		companyCode.Format("C%04d", codeInt);
	}

	rs.Close();
	db.Close();

	return companyCode;
}

void BusinessCardBookForm::OnTakeInButtonClicked() {
	TakeInForm takeInForm;

	takeInForm.DoModal();
}

void BusinessCardBookForm::OnTakeOutButtonClicked() {
	TakeOutForm takeOutForm;

	takeOutForm.DoModal();
}

void BusinessCardBookForm::OnFindButtonClicked() {
	FindingForm findfingForm;

	findfingForm.DoModal();
}

void BusinessCardBookForm::OnFirstButtonClicked() {
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

	index = this->businessCardBook->First();
	name = CString(index->GetName().c_str());
	telephoneNumber = CString(index->GetTelephoneNumber().c_str());
	emailAddress = CString(index->GetEmailAddress().c_str());
	position = CString(index->GetPosition().c_str());
	companyName = CString(index->GetCompanyName().c_str());
	address = CString(index->GetAddress().c_str());
	companyTelephoneNumber = CString(index->GetCompanyTelephoneNumber().c_str());
	faxNumber = CString(index->GetFaxNumber().c_str());
	url = CString(index->GetUrl().c_str());

	GetDlgItem(IDC_STATIC_PERSONAL_NAME_TEXT)->SetWindowText(name);
	GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER_TEXT)->SetWindowText(telephoneNumber);
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS_TEXT)->SetWindowText(emailAddress);
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION_TEXT)->SetWindowText(position);
	GetDlgItem(IDC_STATIC_COMPANY_NAME_TEXT)->SetWindowText(companyName);
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS_TEXT)->SetWindowText(address);
	GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER_TEXT)->SetWindowText(companyTelephoneNumber);
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER_TEXT)->SetWindowText(emailAddress);
	GetDlgItem(IDC_STATIC_COMPANY_URL_TEXT)->SetWindowText(url);
}

void BusinessCardBookForm::OnPreviousButtonClicked() {
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

	index = this->businessCardBook->Previous();
	name = CString(index->GetName().c_str());
	telephoneNumber = CString(index->GetTelephoneNumber().c_str());
	emailAddress = CString(index->GetEmailAddress().c_str());
	position = CString(index->GetPosition().c_str());
	companyName = CString(index->GetCompanyName().c_str());
	address = CString(index->GetAddress().c_str());
	companyTelephoneNumber = CString(index->GetCompanyTelephoneNumber().c_str());
	faxNumber = CString(index->GetFaxNumber().c_str());
	url = CString(index->GetUrl().c_str());

	GetDlgItem(IDC_STATIC_PERSONAL_NAME_TEXT)->SetWindowText(name);
	GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER_TEXT)->SetWindowText(telephoneNumber);
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS_TEXT)->SetWindowText(emailAddress);
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION_TEXT)->SetWindowText(position);
	GetDlgItem(IDC_STATIC_COMPANY_NAME_TEXT)->SetWindowText(companyName);
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS_TEXT)->SetWindowText(address);
	GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER_TEXT)->SetWindowText(companyTelephoneNumber);
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER_TEXT)->SetWindowText(emailAddress);
	GetDlgItem(IDC_STATIC_COMPANY_URL_TEXT)->SetWindowText(url);
}

void BusinessCardBookForm::OnNextButtonClicked() {
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

	index = this->businessCardBook->Next();
	name = CString(index->GetName().c_str());
	telephoneNumber = CString(index->GetTelephoneNumber().c_str());
	emailAddress = CString(index->GetEmailAddress().c_str());
	position = CString(index->GetPosition().c_str());
	companyName = CString(index->GetCompanyName().c_str());
	address = CString(index->GetAddress().c_str());
	companyTelephoneNumber = CString(index->GetCompanyTelephoneNumber().c_str());
	faxNumber = CString(index->GetFaxNumber().c_str());
	url = CString(index->GetUrl().c_str());

	GetDlgItem(IDC_STATIC_PERSONAL_NAME_TEXT)->SetWindowText(name);
	GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER_TEXT)->SetWindowText(telephoneNumber);
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS_TEXT)->SetWindowText(emailAddress);
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION_TEXT)->SetWindowText(position);
	GetDlgItem(IDC_STATIC_COMPANY_NAME_TEXT)->SetWindowText(companyName);
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS_TEXT)->SetWindowText(address);
	GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER_TEXT)->SetWindowText(companyTelephoneNumber);
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER_TEXT)->SetWindowText(emailAddress);
	GetDlgItem(IDC_STATIC_COMPANY_URL_TEXT)->SetWindowText(url);
}

void BusinessCardBookForm::OnLastButtonClicked() {
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

	index = this->businessCardBook->Last();
	name = CString(index->GetName().c_str());
	telephoneNumber = CString(index->GetTelephoneNumber().c_str());
	emailAddress = CString(index->GetEmailAddress().c_str());
	position = CString(index->GetPosition().c_str());
	companyName = CString(index->GetCompanyName().c_str());
	address = CString(index->GetAddress().c_str());
	companyTelephoneNumber = CString(index->GetCompanyTelephoneNumber().c_str());
	faxNumber = CString(index->GetFaxNumber().c_str());
	url = CString(index->GetUrl().c_str());

	GetDlgItem(IDC_STATIC_PERSONAL_NAME_TEXT)->SetWindowText(name);
	GetDlgItem(IDC_STATIC_PERSONAL_TELEPHONENUMBER_TEXT)->SetWindowText(telephoneNumber);
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS_TEXT)->SetWindowText(emailAddress);
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION_TEXT)->SetWindowText(position);
	GetDlgItem(IDC_STATIC_COMPANY_NAME_TEXT)->SetWindowText(companyName);
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS_TEXT)->SetWindowText(address);
	GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER_TEXT)->SetWindowText(companyTelephoneNumber);
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER_TEXT)->SetWindowText(emailAddress);
	GetDlgItem(IDC_STATIC_COMPANY_URL_TEXT)->SetWindowText(url);
}

void BusinessCardBookForm::OnClose() {

	if (this->businessCardBook != NULL) {
		this->Save();
		delete this->businessCardBook;
		
	}
	EndDialog(0);
}
