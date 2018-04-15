// cssample4Doc.h : interface of the CCssample4Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSsample4DOC_H__CAABC39D_901E_4C3D_95AA_6D485A153940__INCLUDED_)
#define AFX_CSsample4DOC_H__CAABC39D_901E_4C3D_95AA_6D485A153940__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCssample4Doc : public CDocument
{
protected: // create from serialization only
	CCssample4Doc();
	DECLARE_DYNCREATE(CCssample4Doc)

// Attributes
public:

// Operations
public:


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCssample4Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCssample4Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCssample4Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSsample4DOC_H__CAABC39D_901E_4C3D_95AA_6D485A153940__INCLUDED_)
