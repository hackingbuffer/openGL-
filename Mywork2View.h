// Mywork2View.h : interface of the CMywork2View class
//
/////////////////////////////////////////////////////////////////////////////
#include <gl/gl.h>
#include <gl/glut.h>
#include <gl/glaux.h>
#include <stdio.h>
#if !defined(AFX_MYWORK2VIEW_H__6F680EDF_0C26_4FE4_9829_0CAA130B5567__INCLUDED_)
#define AFX_MYWORK2VIEW_H__6F680EDF_0C26_4FE4_9829_0CAA130B5567__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMywork2View : public CView
{
protected: // create from serialization only
	CMywork2View();
	DECLARE_DYNCREATE(CMywork2View)

// Attributes
public:
	CMywork2Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMywork2View)
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
	GLfloat rangx;
	MyDraw();
	virtual ~CMywork2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	BOOL CreateViewGLContext(HDC hDC);
	int m_GLPixelIndex;
	HGLRC m_hGLContext;
	//{{AFX_MSG(CMywork2View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCancelMode();
	afx_msg void OnDestroy();
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnTCard(UINT idAction, DWORD dwActionData);
	afx_msg void OnPaint();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL SetWindowPixelFormat(HDC hDC);
};

#ifndef _DEBUG  // debug version in Mywork2View.cpp
inline CMywork2Doc* CMywork2View::GetDocument()
   { return (CMywork2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYWORK2VIEW_H__6F680EDF_0C26_4FE4_9829_0CAA130B5567__INCLUDED_)
