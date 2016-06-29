// Mywork2View.cpp : implementation of the CMywork2View class
//

#include "stdafx.h"
#include "Mywork2.h"

#include "Mywork2Doc.h"
#include "Mywork2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMywork2View

IMPLEMENT_DYNCREATE(CMywork2View, CView)

BEGIN_MESSAGE_MAP(CMywork2View, CView)
	//{{AFX_MSG_MAP(CMywork2View)
	ON_WM_CREATE()
	ON_WM_CANCELMODE()
	ON_WM_DESTROY()
	ON_WM_CAPTURECHANGED()
	ON_WM_SIZE()
	ON_WM_CHAR()
	ON_WM_TIMER()
	ON_WM_TCARD()
	ON_WM_PAINT()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMywork2View construction/destruction

CMywork2View::CMywork2View()
{
	// TODO: add construction code here
	this->m_hGLContext=NULL;
	this->m_GLPixelIndex=0;
	rangx=30.0f;
}

CMywork2View::~CMywork2View()
{
}

BOOL CMywork2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style|=(WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMywork2View drawing

void CMywork2View::OnDraw(CDC* pDC)
{
	CMywork2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	static BOOL bBusy = FALSE;

    if(bBusy) 	return;
    bBusy = TRUE;

	glClearColor(0.0f,0.0f,0.0f,0.0f);
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	MyDraw(); 
	glPopMatrix();
	glFinish();
	SwapBuffers(wglGetCurrentDC());
	bBusy = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CMywork2View printing

BOOL CMywork2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMywork2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMywork2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMywork2View diagnostics

#ifdef _DEBUG
void CMywork2View::AssertValid() const
{
	CView::AssertValid();
}

void CMywork2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMywork2Doc* CMywork2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMywork2Doc)));
	return (CMywork2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMywork2View message handlers

BOOL CMywork2View::SetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pfd={
		sizeof(PIXELFORMATDESCRIPTOR),//pdf的大小
			1,//版本号
			PFD_DRAW_TO_WINDOW| //支持窗口
		 	PFD_DRAW_TO_BITMAP|
			PFD_SUPPORT_GDI|
		 	PFD_STEREO_DONTCARE|
			PFD_SUPPORT_OPENGL|  //支持0PENGL
			PFD_DOUBLEBUFFER,//双缓存
			PFD_TYPE_RGBA,//RGBA类型
			24,//24位颜色深度
			0,0,0,0,0,0, //忽略颜色位
			0,  //无alpha缓存
			0, //忽略转换位
			0, //无累计缓存
			0,0,0,0, //忽略累计位
			32, //32位深度缓存
			0,//无模板缓存
			0, //无辅助缓存
			PFD_MAIN_PLANE, //主层
			0,// 保留
			0,0,0 
	};	 
	 this->m_GLPixelIndex=ChoosePixelFormat(hDC, &pfd);
	 if(this->m_GLPixelIndex==0)
	{
		this->m_GLPixelIndex=1;
		if(0== DescribePixelFormat(hDC, this->m_GLPixelIndex,
								sizeof(PIXELFORMATDESCRIPTOR),
								&pfd))
		{					
			return false;
		}
	}
	if(SetPixelFormat(hDC, this->m_GLPixelIndex,&pfd)==false)
	{
		return false;
	}
		return true;
}

BOOL CMywork2View::CreateViewGLContext(HDC hDC)
{
	this->m_hGLContext=wglCreateContext(hDC);
	if(this->m_hGLContext==NULL)
	{
		return false;
	}
	if(wglMakeCurrent(hDC,this->m_hGLContext)==false)
	{
		return false;
	}
	return true;
}

int CMywork2View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	HWND hWnd=this->GetSafeHwnd();
	HDC hDC=::GetDC(hWnd);
	if(this->SetWindowPixelFormat(hDC)==false)
	{
		return 0;
	}
	if(CreateViewGLContext(hDC)==false)
	{
		return 0;
	}
	return 0;
}

void CMywork2View::OnCancelMode() 
{
	CView::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CMywork2View::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	if(wglGetCurrentContext()!=NULL)
	{
		wglMakeCurrent(NULL,NULL);

	}
	if(this->m_hGLContext!=NULL)
	{
		wglDeleteContext(this->m_hGLContext);
		this->m_hGLContext=NULL;
	}
}

void CMywork2View::OnCaptureChanged(CWnd *pWnd) 
{
	// TODO: Add your message handler code here
	
	CView::OnCaptureChanged(pWnd);
}

CMywork2View::MyDraw()
{
	glTranslatef(0.0f,0.0f,-2.0f);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LINE_STIPPLE);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	
	glRotated(rangx,1.0,0.0,0.0); //绕x轴旋转rangx
	//------------------------飞机模型-begin-----------------------------------------
	////////////////////////////飞机的线框////////////////////////////////////////
	glColor3f(1.0f,0.50f,1.0f);

	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); //线框形式的 

	glBegin(GL_TRIANGLES);
		glVertex3f(-0.18f,0.0f,0.0f); //飞机右翼             ①
		glVertex3f(0.1f,0.0f,-0.15f);//						 ②
		glVertex3f(0.09f,0.0f,-0.01f);//					 ③

		glVertex3f(-0.18f,0.0f,0.0f); //中间Part 1		①			
		glVertex3f(0.09f,0.0f,-0.01f); //				③
		glVertex3f(0.08f,-0.05f,0.0f); //				④

		glVertex3f(-0.18f,0.0f,0.0f); //中间Part 2	①
		glVertex3f(0.08f,-0.05f,0.0f);//			④
		glVertex3f(0.09f,0.0f,0.01f);//				⑤

		glVertex3f(-0.18f,0.0f,0.0f); //飞机左翼		①
		glVertex3f(0.09f,0.0f,0.01f); //				⑤
		glVertex3f(0.1f,0.0f,0.15f);	 //					⑥
	glEnd();
//////////////////////////////////////////////////////////////////////////


///////////////////////////////fill飞机模型///////////////////////////////
	glColor3f(1.0f,0.7f,1.0f); //浅粉色
//glPolygonMode(GL_FRONT, GL_FILL); //填充"前面"的绘制面
	glPolygonMode(GL_BACK, GL_FILL); //填充"后面"的绘制面
//glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLE_FAN); //三角扇

//三角形扇绘制"fill飞机模型"的结果与"飞机线框"模型的结果相同,但是绘制语句明显减少
//因为三角形扇方式下绘制以下6点的等价于4个三角形顶点绘制
// 1 - 2 - 3; 1 - 3 - 4; 1 - 4 - 5; 1 - 5 - 6
// 三角形扇的圆心是①,扇的四周沿顺时针为②,③,④,⑤,⑥
		glVertex3f(-0.18f,0.0f,0.0f); //①
		glVertex3f(0.1f,0.0f,-0.15f); //②
		glVertex3f(0.09f,0.0f,-0.01f); //③

		glVertex3f(0.08f,-0.05f,0.0f); //④
		glVertex3f(0.09f,0.0f,0.01f); //⑤
		glVertex3f(0.1f,0.0f,0.15f); //⑥
	glEnd();

	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_LINE_STIPPLE);
	glDisable(GL_TEXTURE_2D);
}

void CMywork2View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	GLsizei width,height;
	GLdouble aspect;
	width=cx;
	height=cy;
	if(0==cy)
		aspect=(GLdouble)width;
	else
		aspect=(GLdouble)width/(GLdouble)height;
	glViewport(0,0,width,height);//设置视区尺寸
	//  以下两行是重置坐标系统，使投影变换复位
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();
	//	gluOrtho2D(0.0,500.0*aspect,0.0,500.0); 用于二维图片
	gluPerspective(45.0, aspect, 1.0, 10.0);//二维的时候，需要注销改句
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDrawBuffer(GL_BACK);

	/*
	if(cy > 0)
	{ 
        my_oldRect.right = cx;
        my_oldRect.bottom = cy;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
		glFrustum(-1.0,1.0,-1.0*cy/cx,1.0*cy/cx,5.0,9.0);
		glViewport(0, 0, cx, cy);
    }
	RedrawWindow();
	*/
}

void CMywork2View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default	
	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CMywork2View::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	rangx-=1.15f;
	if(rangx<=-360.0f){
		rangx+=360.0f;
	}
	InvalidateRect(NULL,FALSE);//角度更新，通知其重绘

/*	if(nIDEvent==1){
	if(rangx==360.0f){rangx=10.0f;};
	rangx=rangx+10.0f;
		Invalidate(FALSE);
	};
*/	
	CView::OnTimer(nIDEvent);
}

void CMywork2View::OnTCard(UINT idAction, DWORD dwActionData) 
{
	// TODO: Add your message handler code here
	
}

void CMywork2View::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CView::OnPaint() for painting messages
	OnPrepareDC(&dc);
	OnDraw(&dc);
}

void CMywork2View::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	
}
