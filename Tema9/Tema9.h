
// Tema9.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTema9App:
// See Tema9.cpp for the implementation of this class
//

class CTema9App : public CWinApp
{
public:
	CTema9App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTema9App theApp;
