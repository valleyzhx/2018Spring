// cssample1.h : main header file for the CSsample1 application
//

#if !defined(AFX_CSsample1_H__FD9F6A69_2CFE_4732_A4CF_636257536A03__INCLUDED_)
#define AFX_CSsample1_H__FD9F6A69_2CFE_4732_A4CF_636257536A03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCssample1App:
// See cssample1.cpp for the implementation of this class
//

class CCssample1App : public CWinApp
{
public:
	CCssample1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCssample1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCssample1App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSsample1_H__FD9F6A69_2CFE_4732_A4CF_636257536A03__INCLUDED_)
