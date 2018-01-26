// cssample1Doc.h : interface of the CCssample1Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSsample1DOC_H__329B7432_0171_4740_93FC_4E0B83182F2B__INCLUDED_)
#define AFX_CSsample1DOC_H__329B7432_0171_4740_93FC_4E0B83182F2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 

class CCssample1Doc : public CDocument
{
protected: // create from serialization only
	CCssample1Doc();
	DECLARE_DYNCREATE(CCssample1Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCssample1Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCssample1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCssample1Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSsample1DOC_H__329B7432_0171_4740_93FC_4E0B83182F2B__INCLUDED_)
