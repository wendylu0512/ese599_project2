
// ese599_project2.h : main header file for the ese599_project2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Cese599_project2App:
// See ese599_project2.cpp for the implementation of this class
//

class Cese599_project2App : public CWinApp
{
public:
	Cese599_project2App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Cese599_project2App theApp;
