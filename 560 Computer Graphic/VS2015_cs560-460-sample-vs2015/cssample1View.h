// cssample1View.h : interface of the CCssample1View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSsample1VIEW_H__C6C32F57_5FBE_4F63_841C_74E2F1DDEDF4__INCLUDED_)
#define AFX_CSsample1VIEW_H__C6C32F57_5FBE_4F63_841C_74E2F1DDEDF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCssample1View : public CView
{
protected: // create from serialization only
	CCssample1View();
	DECLARE_DYNCREATE(CCssample1View)

// Attributes
public:
	CCssample1Doc* GetDocument();

// Operations
public:
	int height;
	int width;
	bool mouseDown;
	CPoint current;
	CPoint start;
//	void Init();

	HDC m_hDC;
	HGLRC m_hGLContext;
	BOOL SetWindowPixelFormat(HDC hDC);
	BOOL CreateViewGLContext(HDC hDC);
	int m_GLPixelIndex;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCssample1View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL dblBuf;
	CPoint m_LDownPos;
	virtual ~CCssample1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCssample1View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDblBuf();
	afx_msg void OnNoDblBuf();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in cssample1View.cpp
inline CCssample1Doc* CCssample1View::GetDocument()
   { return (CCssample1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSsample1VIEW_H__C6C32F57_5FBE_4F63_841C_74E2F1DDEDF4__INCLUDED_)
