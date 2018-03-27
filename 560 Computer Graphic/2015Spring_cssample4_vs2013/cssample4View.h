// cssample4View.h : interface of the CCssample4View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSsample4VIEW_H__72070A70_2B2E_4625_A38B_3C3967F61AFB__INCLUDED_)
#define AFX_CSsample4VIEW_H__72070A70_2B2E_4625_A38B_3C3967F61AFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCssample4View : public CView
{
protected: // create from serialization only
	CCssample4View();
	DECLARE_DYNCREATE(CCssample4View)

// Attributes
public:
	CCssample4Doc* GetDocument();

// Operations
public:

	int m_GLPixelIndex;	
	HDC m_hDC;
	HGLRC m_hRC;

	CPoint m_LDownPos;
	BOOL m_LButtonDown;

	CPoint rectangle[4];

	int w, h;

	GLfloat RedSurface[4];
	GLfloat GreenSurface[4];
	GLfloat YellowSurface[4];
	GLfloat WhiteSurface[4];
	GLfloat BlueSurface[4];
	GLfloat BlackSurface[4];
	
	// Setup GL view/projection matrices for window size.
    void SizeGL1(int w, int h);
    // Setup default params (lighting, etc...) for GL.
    void SetupGL();
    // Render scene using OpenGL.

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCssample4View)
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
	void SetTexture();
	GLuint ImgName;
	BITMAP texImage;//// storing the loaded image
	BOOL LoadImage(LPCTSTR fileName);
	virtual ~CCssample4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCssample4View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewTextureDisable();
	afx_msg void OnViewTextureEnable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in cssample4View.cpp
inline CCssample4Doc* CCssample4View::GetDocument()
   { return (CCssample4Doc*)m_pDocument; }
#endif


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSsample4VIEW_H__72070A70_2B2E_4625_A38B_3C3967F61AFB__INCLUDED_)
