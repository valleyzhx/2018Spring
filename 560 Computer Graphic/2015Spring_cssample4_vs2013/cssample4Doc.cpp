// cssample4Doc.cpp : implementation of the CCssample4Doc class
//

#include "stdafx.h"
#include "cssample4.h"

#include "cssample4Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CCssample4Doc

IMPLEMENT_DYNCREATE(CCssample4Doc, CDocument)

BEGIN_MESSAGE_MAP(CCssample4Doc, CDocument)
	//{{AFX_MSG_MAP(CCssample4Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCssample4Doc construction/destruction

CCssample4Doc::CCssample4Doc()
{
	// TODO: add one-time construction code here

}

CCssample4Doc::~CCssample4Doc()
{
}

BOOL CCssample4Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCssample4Doc serialization

void CCssample4Doc::Serialize(CArchive& ar)
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
// CCssample4Doc diagnostics

#ifdef _DEBUG
void CCssample4Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCssample4Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCssample4Doc commands
