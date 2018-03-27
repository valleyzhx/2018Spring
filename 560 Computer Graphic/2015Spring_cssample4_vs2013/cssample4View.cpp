// cssample4View.cpp : implementation of the CCssample4View class
//

#include "stdafx.h"
#include "cssample4.h"

#include "cssample4Doc.h"
#include "cssample4View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCssample4View

IMPLEMENT_DYNCREATE(CCssample4View, CView)

BEGIN_MESSAGE_MAP(CCssample4View, CView)
	//{{AFX_MSG_MAP(CCssample4View)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_TEXTURE_DISABLE, OnViewTextureDisable)
	ON_COMMAND(ID_VIEW_TEXTURE_ENABLE, OnViewTextureEnable)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCssample4View construction/destruction

CCssample4View::CCssample4View()
{
	m_hDC=NULL;
	m_hRC=NULL;
	w=h=0; //width and height of view area
/*
	RedSurface[0]= 1.0f; RedSurface[1]=0.0f; RedSurface[2]=0.0f; RedSurface[3]=1.0f;
	GreenSurface[0]= 0.0f; GreenSurface[1]=1.0f; GreenSurface[2]=0.0f; GreenSurface[3]=1.0f;
	BlueSurface[0]= 0.0f; BlueSurface[1]=0.0f; BlueSurface[2]=1.0f; BlueSurface[3]=1.0f;
	BlackSurface[0]= 0.0f; BlackSurface[1]=0.0f; BlackSurface[2]=0.0f; BlackSurface[3]=1.0f;
*/

    rectangle[0].x=250.0;
	rectangle[0].y=100.0;
	rectangle[1].x=550.0;
	rectangle[1].y=100.0;
	rectangle[2].x=550.0;
	rectangle[2].y=300.0;
	rectangle[3].x=250.0;
	rectangle[3].y=300.0;

}

CCssample4View::~CCssample4View()
{
}

BOOL CCssample4View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCssample4View drawing

void CCssample4View::OnDraw(CDC* pDC)
{
	
	CCssample4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect rcClient;
	GetClientRect(rcClient);
	
	w=rcClient.Width();
	h=rcClient.Height();

	wglMakeCurrent(m_hDC,m_hRC);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);		
	
	glColor4f(1.0, 1.0, 1.0, 0.0);

	glViewport(0, 0, (int)(w/1.0), (int)(h/1.0));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, w, 0.0, h);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

  
	//glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	
	//rectangle + texture   //// You may rewrite this part for your own implementation
	glBegin(GL_POLYGON);
		    glTexCoord2f(0.0,0.0);
	    	glVertex3f(0.0+rectangle[0].x,0.0+rectangle[0].y,0.0);
	    	glTexCoord2f(1.0,0.0);
	    	glVertex3f(0.0+rectangle[1].x,0.0+rectangle[1].y,0.0);
	    	glTexCoord2f(1.0,1.0);
		    glVertex3f(0.0+rectangle[2].x,0.0+rectangle[2].y,0.0);
	    	glTexCoord2f(0.0,1.0);
	    	glVertex3f(0.0+rectangle[3].x,0.0+rectangle[3].y,0.0);
        glEnd();
	

	glPopMatrix();
	glFlush();
	glDisable(GL_TEXTURE_2D);

	
//	wglMakeCurrent(m_hDC,NULL);
	wglMakeCurrent(m_hDC,m_hRC);
    ::SwapBuffers(m_hDC);



}

/////////////////////////////////////////////////////////////////////////////
// CCssample4View printing

BOOL CCssample4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CCssample4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{}

void CCssample4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{}

/////////////////////////////////////////////////////////////////////////////
// CCssample4View diagnostics

#ifdef _DEBUG
void CCssample4View::AssertValid() const
{
	CView::AssertValid();
}

void CCssample4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCssample4Doc* CCssample4View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCssample4Doc)));
	return (CCssample4Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCssample4View message handlers

int CCssample4View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	int nPixelFormat;				
	m_hDC = ::GetDC(m_hWnd);			

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),	
		1,									
		PFD_DRAW_TO_WINDOW |			
		PFD_SUPPORT_OPENGL |			
		PFD_DOUBLEBUFFER,				
		PFD_TYPE_RGBA, 24, 0, 0, 0, 0, 0, 0,					
		0, 0, 0, 0, 0, 0, 0, 32, 0, 0, 
                PFD_MAIN_PLANE, 0, 0, 0, 0 
	};

    nPixelFormat = ::ChoosePixelFormat(m_hDC, &pfd);
    ::SetPixelFormat(m_hDC, nPixelFormat, &pfd);
    m_hRC = ::wglCreateContext(m_hDC);
    ::wglMakeCurrent(m_hDC,m_hRC);
    SetupGL();
    ::wglMakeCurrent(m_hDC,NULL);
	
	return 0;
}

void CCssample4View::OnDestroy() 
{
	CView::OnDestroy();
	// Clean up rendering context stuff
    ::wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd,m_hDC);	
}

void CCssample4View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
		
    ::wglMakeCurrent(m_hDC,m_hRC);
    SizeGL1(cx, cy);
    ::wglMakeCurrent(NULL,NULL);

}

// Setup GL view/projection matrices for window size.
void CCssample4View::SizeGL1(int w, int h)
{
        // Correct for zero dimensions.
        h = h ? h : 1;
        w = w ? w : 1;
 
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, w, 0, h);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glFlush();
}


void CCssample4View::SetupGL()
{
        glDepthFunc(GL_LEQUAL);
	    glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
}

BOOL CCssample4View::LoadImage(LPCTSTR fileName)
{
	HBITMAP hBmp = (HBITMAP) ::LoadImage (NULL,(LPCTSTR) fileName, 
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE |LR_CREATEDIBSECTION);

	if (hBmp == NULL){
		AfxMessageBox("Error: unable to load bitmap file");
        return FALSE;
    }

    // Get bitmap info.
	::GetObject (hBmp, sizeof(texImage), &texImage);

    // Must be 24 bit
    if (texImage.bmBitsPixel != 24){
		AfxMessageBox("Error: bitmap must be 24 bit");
        return FALSE;
    }
        
    glBindTexture(GL_TEXTURE_2D, ImgName);
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, texImage.bmWidth, texImage.bmHeight, 
			GL_BGR_EXT, GL_UNSIGNED_BYTE, texImage.bmBits);   //// texImage.bmBits stores the loaded image

    return TRUE;
}

void CCssample4View::SetTexture()
{
	glDrawBuffer(GL_BACK);
	glGenTextures(1, &ImgName);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	LoadImage("flower.bmp");
}

void CCssample4View::OnViewTextureDisable() 
{
	//your implementation here
	//	
 glDisable(GL_TEXTURE_2D);
 InvalidateRect(NULL);
}

void CCssample4View::OnViewTextureEnable() 
{
	//your implementation here
	//....

 SetTexture();
 glEnable(GL_TEXTURE_2D);
 InvalidateRect(NULL);

}



