#pragma once
//BusinessCardBookForm.h
#ifndef _BUSINESSCARDBOOKFORM_H
#define _BUSINESSCARDBOOKFORM_H
#include <afxwin.h>
#include "resource.h"

class BusinessCardBook;
class BusinessCard;

class BusinessCardBookForm :public CDialog {
public:
	enum { IDD = IDD_BUSINESSCARDBOOKFORM };
public:
	BusinessCardBookForm(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
	void Load();
	void Save();
	void Insert(BusinessCard *index);
	void Delete(BusinessCard *index);
	CString MakePersonalCode();
	CString MakeCompanyCode();
public:
	BusinessCardBook *businessCardBook;
protected:
	afx_msg void OnTakeInButtonClicked();
	afx_msg void OnTakeOutButtonClicked();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnFirstButtonClicked();
	afx_msg void OnPreviousButtonClicked();
	afx_msg void OnNextButtonClicked();
	afx_msg void OnLastButtonClicked();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};
#endif // !_BUSINESSCARDBOOKFORM_H
