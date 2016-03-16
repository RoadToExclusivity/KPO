// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// DrawerView.cpp : implementation of the CDrawerView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Drawer.h"
#endif

#include "DrawerDoc.h"
#include "DrawerView.h"
#include "Rectangle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawerView

IMPLEMENT_DYNCREATE(CDrawerView, CView)

BEGIN_MESSAGE_MAP(CDrawerView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_BUTTON_RECTANGLE, &CDrawerView::OnButtonRectangle)
	ON_COMMAND(ID_BUTTON_ELLIPSE, &CDrawerView::OnButtonEllipse)
	ON_COMMAND(ID_BUTTON_TRIANGLE, &CDrawerView::OnButtonTriangle)
END_MESSAGE_MAP()

// CDrawerView construction/destruction

CDrawerView::CDrawerView()
	:m_clientRectangle(nullptr),
	m_isShapeDragged(false),
	m_dragShapeIndex(-1),
	m_prevPointPosition(),
	m_startPointPosition()
{
	// TODO: add construction code here

}

CDrawerView::~CDrawerView()
{
	if (m_clientRectangle)
	{
		delete m_clientRectangle;
	}
}

const LPRECT CDrawerView::GetClientRectangle()
{
	if (!m_clientRectangle)
	{
		m_clientRectangle = new RECT();
	}
	GetClientRect(m_clientRectangle);

	return m_clientRectangle;
}

BOOL CDrawerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CDrawerView drawing

void CDrawerView::OnDraw(CDC* pDC)
{
	CDrawerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	auto shapes = pDoc->GetShapes();
	for (const auto shape: shapes)
	{
		shape->Draw(pDC->GetSafeHdc(), shape->GetBoundingBox());
	}
}

void CDrawerView::OnLButtonDown(UINT /* nFlags */, CPoint point)
{
	Gdiplus::Point gdiPoint(point.x, point.y);
	
	CDrawerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	auto shapes = pDoc->GetShapes();
	for (int i = shapes.size() - 1; i >= 0; --i)
	{
		if (shapes[i]->IsShapePoint(gdiPoint))
		{
			m_isShapeDragged = true;
			m_dragShapeIndex = i;
			m_prevPointPosition = gdiPoint;
			m_startPointPosition = shapes[i]->GetPosition();
			break;
		}
	}
}

void CDrawerView::OnMouseMove(UINT /* nFlags */, CPoint point)
{
	if (m_isShapeDragged)
	{
		CDrawerDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		auto shapes = pDoc->GetShapes();
		shapes[m_dragShapeIndex]->SetPosition(m_startPointPosition + Gdiplus::Point(point.x, point.y) - m_prevPointPosition);

		Invalidate();
	}
}

void CDrawerView::OnLButtonUp(UINT /* nFlags */, CPoint point)
{
	if (m_isShapeDragged)
	{
		m_isShapeDragged = false;
		m_dragShapeIndex = -1;
	}
}

void CDrawerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDrawerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDrawerView diagnostics

#ifdef _DEBUG
void CDrawerView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawerDoc* CDrawerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawerDoc)));
	return (CDrawerDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawerView message handlers

void CDrawerView::OnButtonRectangle()
{
	auto rect = GetDocument()->CreateRectangle(GetClientRectangle());
	if (rect)
	{
		Invalidate();
	}
}


void CDrawerView::OnButtonEllipse()
{
	auto ellipse = GetDocument()->CreateEllipse(GetClientRectangle());
	if (ellipse)
	{
		Invalidate();
	}
}


void CDrawerView::OnButtonTriangle()
{
	auto triangle = GetDocument()->CreateTriangle(GetClientRectangle());
	if (triangle)
	{
		Invalidate();
	}
}
