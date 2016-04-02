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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawerView

IMPLEMENT_DYNCREATE(CDrawerView, CView)

BEGIN_MESSAGE_MAP(CDrawerView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_KEYUP()
	ON_COMMAND(ID_BUTTON_RECTANGLE, &CDrawerView::OnButtonRectangle)
	ON_COMMAND(ID_BUTTON_ELLIPSE, &CDrawerView::OnButtonEllipse)
	ON_COMMAND(ID_BUTTON_TRIANGLE, &CDrawerView::OnButtonTriangle)
END_MESSAGE_MAP()

// CDrawerView construction/destruction

CDrawerView::CDrawerView()
	:m_clientRectangle(nullptr),
	m_diffPointPosition(),
	m_backgroundBrush(Gdiplus::Color(255, 255, 255)),
	m_cursorChangeToCross(false),
	m_cursorChangeToNormal(false),
	m_cursorChangeToSizeEW(false),
	m_cursorChangeToSizeWE(false),
	m_resizeSelectionMarker(SelectionBoxMarkerState::NONE)
{
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
	
	auto clientRect = GetClientRectangle();
	HDC mainHDC = pDC->GetSafeHdc();
	HDC bufferHDC = CreateCompatibleDC(mainHDC);
	const int memDC = SaveDC(bufferHDC);

	HBITMAP buff = CreateCompatibleBitmap(mainHDC, clientRect->right, clientRect->bottom);
	SelectObject(bufferHDC, buff);

	Gdiplus::Graphics g(bufferHDC);
	g.FillRectangle(&m_backgroundBrush, 0, 0, clientRect->right, clientRect->bottom);

	auto shapeCtrls = pDoc->GetShapes();
	for (const auto& ctrl : shapeCtrls)
	{
		ctrl->Draw(bufferHDC);
	}

	if (pDoc->GetSelectedShapeIndex() != -1)
	{
		shapeCtrls[pDoc->GetSelectedShapeIndex()]->DrawSelectionBox(bufferHDC);
	}

	RECT clipRect;
	GetClipBox(mainHDC, &clipRect);
	BitBlt(mainHDC, clipRect.left, clipRect.top, clipRect.right - clipRect.left, clipRect.bottom - clipRect.top, 
			bufferHDC, clipRect.left, clipRect.top, SRCCOPY);
	RestoreDC(bufferHDC, memDC);
	DeleteObject(buff);
}

void CDrawerView::OnLButtonDown(UINT /* nFlags */, CPoint point)
{	
	CDrawerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Gdiplus::Point gdiPoint(point.x, point.y);
	auto shapeCtrls = pDoc->GetShapes();
	if (pDoc->GetSelectedShapeIndex() != -1)
	{
		const auto& curShapeCtrl = shapeCtrls[pDoc->GetSelectedShapeIndex()];
		m_resizeSelectionMarker = curShapeCtrl->IsPointAtMarker(gdiPoint);
		if (m_resizeSelectionMarker != SelectionBoxMarkerState::NONE)
		{
			pDoc->SetShapeResized();

			return;
		}
	}

	pDoc->SetSelectedShapeIndex(-1);
	for (int i = shapeCtrls.size() - 1; i >= 0; --i)
	{
		if (shapeCtrls[i]->IsShapePoint(gdiPoint))
		{
			pDoc->SetDragged(i);
			m_diffPointPosition = shapeCtrls[i]->GetPosition() - gdiPoint;
			return;
		}
	}

	Invalidate();
}

void CDrawerView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags && MK_LBUTTON)
	{
		CDrawerDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		if (pDoc->IsShapeResized())
		{
			auto shapeCtrls = pDoc->GetShapes();

			shapeCtrls[pDoc->GetSelectedShapeIndex()]->ChangeShapeSize(m_resizeSelectionMarker, Gdiplus::Point(point.x, point.y));
			if (m_resizeSelectionMarker == SelectionBoxMarkerState::BOTTOM_LEFT ||
				m_resizeSelectionMarker == SelectionBoxMarkerState::TOP_RIGHT)
			{
				m_cursorChangeToSizeEW = true;
			}
			else
			{
				m_cursorChangeToSizeWE = true;
			}

			Invalidate();
		}
		else
		{
			if (pDoc->IsShapeDragged())
			{
				m_cursorChangeToCross = true;
				auto shapeCtrls = pDoc->GetShapes();
				shapeCtrls[pDoc->GetDraggedShapeIndex()]->SetPosition(m_diffPointPosition + Gdiplus::Point(point.x, point.y));

				Invalidate();
			}
		}
	}
}

void CDrawerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDrawerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (pDoc->IsShapeResized())
	{
		pDoc->SetShapeUnresized();
		m_cursorChangeToNormal = true;
		OnSetCursor(this, 0, 0); //empty call for cursor changing runtime
	}
	else
	{
		if (pDoc->IsShapeDragged())
		{
			m_cursorChangeToNormal = true;
			OnSetCursor(this, 0, 0); //empty call for cursor changing runtime

			pDoc->SetSelectedShapeIndex(pDoc->GetDraggedShapeIndex());
			pDoc->SetUndragged();

			Invalidate();
		}
	}
}

BOOL CDrawerView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

BOOL CDrawerView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (m_cursorChangeToNormal)
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		m_cursorChangeToNormal = false;
		return TRUE;
	}

	if (m_cursorChangeToCross)
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
		m_cursorChangeToCross = false;
		return TRUE;
	}

	if (m_cursorChangeToSizeEW)
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENESW));
		m_cursorChangeToSizeEW = false;
		return TRUE;
	}

	if (m_cursorChangeToSizeWE)
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENWSE));
		m_cursorChangeToSizeWE = false;
		return TRUE;
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}

void CDrawerView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DELETE)
	{
		CDrawerDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		if (pDoc->GetSelectedShapeIndex() != -1 && !pDoc->IsShapeResized())
		{
			pDoc->DeleteShapeCtrl(pDoc->GetSelectedShapeIndex());
			pDoc->SetSelectedShapeIndex(-1);

			Invalidate();
		}
	}
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
	CDrawerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	auto rect = pDoc->CreateRectangle(GetClientRectangle());
	if (rect)
	{
		pDoc->SetSelectedShapeIndex(-1);
		Invalidate();
	}
}

void CDrawerView::OnButtonEllipse()
{
	CDrawerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	auto ellipse = pDoc->CreateEllipse(GetClientRectangle());
	if (ellipse)
	{
		pDoc->SetSelectedShapeIndex(-1);
		Invalidate();
	}
}

void CDrawerView::OnButtonTriangle()
{
	CDrawerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	auto triangle = pDoc->CreateTriangle(GetClientRectangle());
	if (triangle)
	{
		pDoc->SetSelectedShapeIndex(-1);
		Invalidate();
	}
}
