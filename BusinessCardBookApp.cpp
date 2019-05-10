// BusinessCardBookApp.cpp
#include "BusinessCardBookApp.h"
#include "BusinessCardBookForm.h"

BOOL BusinessCardBookApp::InitInstance() {
	BusinessCardBookForm businessCardBookForm;

	this->m_pMainWnd = &businessCardBookForm;

	businessCardBookForm.DoModal();

	return TRUE;
}
BusinessCardBookApp businessCardBookApp;