// cssample1Doc.cpp : implementation of the CCssample1Doc class
//

#include "stdafx.h"
#include "cssample1.h"

#include "cssample1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCssample1Doc

IMPLEMENT_DYNCREATE(CCssample1Doc, CDocument)

BEGIN_MESSAGE_MAP(CCssample1Doc, CDocument)
	//{{AFX_MSG_MAP(CCssample1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCssample1Doc construction/destruction

CCssample1Doc::CCssample1Doc()
{
	// TODO: add one-time construction code here

}

CCssample1Doc::~CCssample1Doc()
{
}

BOOL CCssample1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCssample1Doc serialization

void CCssample1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCssample1Doc diagnostics

#ifdef _DEBUG
void CCssample1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCssample1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCssample1Doc commands 