// cssample1View.cpp : implementation of the CCssample1View class
//

#include "stdafx.h"
#include "cssample1.h"

#include "cssample1Doc.h"
#include "cssample1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCssample1View

IMPLEMENT_DYNCREATE(CCssample1View, CView)

BEGIN_MESSAGE_MAP(CCssample1View, CView)
	//{{AFX_MSG_MAP(CCssample1View)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_COMMAND(ID_DBL_BUF, OnDblBuf)
	ON_COMMAND(ID_NO_DBL_BUF, OnNoDblBuf)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCssample1View construction/destruction

CCssample1View::CCssample1View()
{
	mouseDown=false;
	width=0; height=0;
	dblBuf=true;
}

CCssample1View::~CCssample1View()
{
}

BOOL CCssample1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCssample1View drawing

void CCssample1View::OnDraw(CDC* pDC)
{
	CCssample1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect rcClient;
	GetClientRect(rcClient);
	
	width=rcClient.Width();
	height=rcClient.Height();
    
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Clear buffer content, so that no old content remains in the buffer
	//glClear(GL_COLOR_BUFFER_BIT);
	
	
	// for double buffering
	//if(dblBuf)
		//glDrawBuffer(GL_BACK);
	//else
		glDrawBuffer(GL_FRONT_AND_BACK);

	wglMakeCurrent(m_hDC,m_hGLContext);


    //Add your own stuff here for OpenGL related operations  
	glColor4f(1.0, 1.0, 1.0, 0.0);
	glPushMatrix();
	glBegin(GL_LINES);
		glVertex3d(start.x, height-start.y, 0);
		glVertex3d(m_LDownPos.x, height-m_LDownPos.y, 0);
	glEnd();
	glFlush();
	glPopMatrix();

       
      
	wglMakeCurrent(m_hDC,NULL);
	wglMakeCurrent(m_hDC, m_hGLContext);

	::SwapBuffers(m_hDC);
}

/////////////////////////////////////////////////////////////////////////////
// CCssample1View printing

BOOL CCssample1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCssample1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCssample1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCssample1View diagnostics

#ifdef _DEBUG
void CCssample1View::AssertValid() const
{
	CView::AssertValid();
}

void CCssample1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCssample1Doc* CCssample1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCssample1Doc)));
	return (CCssample1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCssample1View message handlers

BOOL CCssample1View::SetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;

	pixelDesc.nSize		= sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion	= 1;
	/***************
	pixelDesc.dwFlags=PFD_DRAW_TO_WINDOW | 
					PFD_DRAW_TO_BITMAP | 
					PFD_SUPPORT_OPENGL | 
					PFD_SUPPORT_GDI | 
					PFD_STEREO_DONTCARE;
	*********************/
	//Stuff with double buffering
    pixelDesc.dwFlags =    PFD_DRAW_TO_WINDOW | 
                PFD_SUPPORT_OPENGL | 
                PFD_DOUBLEBUFFER | //set as a double buffer mode. (otherwise, single buffer mode)
                PFD_STEREO_DONTCARE;  
	
	pixelDesc.iPixelType	= PFD_TYPE_RGBA;
	pixelDesc.cColorBits	= 32;
	pixelDesc.cRedBits		= 8;
	pixelDesc.cRedShift		= 16;
	pixelDesc.cGreenBits	= 8;
	pixelDesc.cGreenShift	= 8;
	pixelDesc.cBlueBits		= 8;
	pixelDesc.cBlueShift	= 0;
	pixelDesc.cAlphaBits	= 0;
	pixelDesc.cAlphaShift	= 0;
	pixelDesc.cAccumBits	= 64;	
	pixelDesc.cAccumRedBits	= 16;
	pixelDesc.cAccumGreenBits	= 16;
	pixelDesc.cAccumBlueBits	= 16;
	pixelDesc.cAccumAlphaBits	= 0;
	pixelDesc.cDepthBits		= 32;
	pixelDesc.cStencilBits		= 8;
	pixelDesc.cAuxBuffers		= 0;
	pixelDesc.iLayerType		= PFD_MAIN_PLANE;
	pixelDesc.bReserved			= 0;
	pixelDesc.dwLayerMask		= 0;
	pixelDesc.dwVisibleMask		= 0;
	pixelDesc.dwDamageMask		= 0;

	m_GLPixelIndex = ChoosePixelFormat( hDC, &pixelDesc);
	if (m_GLPixelIndex==0) // Let's choose a default index.
	{
		m_GLPixelIndex = 1;	
		if (DescribePixelFormat(hDC, m_GLPixelIndex, sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc)==0)
		{
			return FALSE;
		}
	}

	if (SetPixelFormat( hDC, m_GLPixelIndex, &pixelDesc)==FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCssample1View::CreateViewGLContext(HDC hDC)
{
	m_hGLContext = wglCreateContext(m_hDC);
    if (m_hGLContext == NULL)
    {
        return FALSE;
    }

    if (wglMakeCurrent(m_hDC, m_hGLContext)==FALSE)
    {
        return FALSE;
    }
    return TRUE;
}

int CCssample1View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	HWND hWnd = GetSafeHwnd();
    m_hDC = ::GetDC(hWnd);

    if (SetWindowPixelFormat(m_hDC)==FALSE)
        return 0;
    if (CreateViewGLContext(m_hDC)==FALSE)
        return 0;
	return 0;
}

void CCssample1View::OnDestroy() 
{
	CView::OnDestroy();
	
	if(wglGetCurrentContext()!=NULL) 
    {
        // make the rendering context not current
        wglMakeCurrent(NULL, NULL) ;
    }
    
    if (m_hGLContext!=NULL)
    {
        wglDeleteContext(m_hGLContext);
        m_hGLContext = NULL;
    }

    // Now the associated DC can be released.
    CView::OnDestroy(); 	
}

void CCssample1View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	mouseDown = TRUE;
	m_LDownPos = point;
	glClear(GL_COLOR_BUFFER_BIT);
	//CView::OnLButtonDown(nFlags, point);
}

void CCssample1View::OnLButtonUp(UINT nFlags, CPoint point) 
{
	mouseDown=false;
	//one line has drawn, clear everything
	CView::OnLButtonUp(nFlags, point);
}

void CCssample1View::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (mouseDown)
	{
		start=m_LDownPos;
		m_LDownPos = point;
		InvalidateRect(NULL, FALSE);
	}
	CView::OnMouseMove(nFlags, point);
}

void CCssample1View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
    glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// for double buffering
	glDrawBuffer(GL_BACK);
	
}

void CCssample1View::OnDblBuf() 
{
	dblBuf=true;	
}

void CCssample1View::OnNoDblBuf() 
{
	dblBuf=false;	
}
