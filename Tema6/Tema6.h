
// Tema6.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTema6App:
// See Tema6.cpp for the implementation of this class
//

class CTema6App : public CWinApp
{
public:
	CTema6App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTema6App theApp;
