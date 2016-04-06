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
#include "MoveCommand.h"
#include "CreateShapeCommand.h"
#include "DeleteShapeCommand.h"
#include "ResizeCommand.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawerView

IMPLEMENT_DYNCREATE(CDrawerView, CScrollView)

BEGIN_MESSAGE_MAP(CDrawerView, CScrollView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_KEYUP()
	ON_WM_SIZE()
	ON_COMMAND(ID_BUTTON_RECTANGLE, &CDrawerView::OnButtonRectangle)
	ON_COMMAND(ID_BUTTON_ELLIPSE, &CDrawerView::OnButtonEllipse)
	ON_COMMAND(ID_BUTTON_TRIANGLE, &CDrawerView::OnButtonTriangle)
	ON_COMMAND(ID_EDIT_REDO, &CDrawerView::OnEditRedo)
	ON_COMMAND(ID_EDIT_UNDO, &CDrawerView::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CDrawerView::OnUpdateEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CDrawerView::OnUpdateEditRedo)
END_MESSAGE_MAP()

CDrawerView::CDrawerView()
	:m_clientRectangle(),
	m_diffPointPosition(),
	m_startDragPoint(),
	m_startResizeRect(),
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
}

Gdiplus::Rect CDrawerView::GetClientRectangle()
{
	GetClientRect(&m_clientRectangle);
	m_clientRectangle.right = max(VIEW_WIDTH, m_clientRectangle.right);
	m_clientRectangle.bottom = max(VIEW_HEIGHT, m_clientRectangle.bottom);

	return Gdiplus::Rect(0, 0, m_clientRectangle.right, m_clientRectangle.bottom);
}

BOOL CDrawerView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

void CDrawerView::OnInitialUpdate()
{	
	auto clientRect = GetClientRectangle();

	CSize size;
	size.cx = clientRect.Width;
	size.cy = clientRect.Height;
	SetScrollSizes(MM_TEXT, size);

	CScrollView::OnInitialUpdate();
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

	HBITMAP buff = CreateCompatibleBitmap(mainHDC, clientRect.Width, clientRect.Height);
	SelectObject(bufferHDC, buff);

	Gdiplus::Graphics g(bufferHDC);
	g.FillRectangle(&m_backgroundBrush, 0, 0, clientRect.Width, clientRect.Height);

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

	//SetCapture();
	Gdiplus::Point gdiPoint(point.x, point.y);
	auto shapeCtrls = pDoc->GetShapes();
	if (pDoc->GetSelectedShapeIndex() != -1)
	{
		const auto& curShapeCtrl = shapeCtrls[pDoc->GetSelectedShapeIndex()];
		m_resizeSelectionMarker = curShapeCtrl->IsPointAtMarker(gdiPoint);
		if (m_resizeSelectionMarker != SelectionBoxMarkerState::NONE)
		{
			pDoc->SetShapeResized();
			m_startResizeRect = curShapeCtrl->GetBoundingBox();

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
			m_startDragPoint = shapeCtrls[i]->GetPosition();
			return;
		}
	}

	Invalidate();
}

void CDrawerView::OnMouseMove(UINT /*nFlags*/, CPoint point)
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
			auto newPos = m_diffPointPosition + Gdiplus::Point(point.x, point.y);
			//if (newPos.X < 0) newPos.X = 0;
			//if (newPos.Y < 0) newPos.Y = 0;
			shapeCtrls[pDoc->GetDraggedShapeIndex()]->SetPosition(newPos);
			Invalidate();
		}
	}
}

void CDrawerView::OnLButtonUp(UINT /*nFlags*/, CPoint point)
{
	CDrawerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (pDoc->IsShapeResized())
	{
		pDoc->SetShapeUnresized();
		m_cursorChangeToNormal = true;
		OnSetCursor(this, 0, 0);

		auto& shapeCtrls = pDoc->GetShapes();
		int resizeIndex = pDoc->GetSelectedShapeIndex();
		pDoc->AddCommand(new CResizeCommand(pDoc, resizeIndex, m_startResizeRect, shapeCtrls[resizeIndex]->GetBoundingBox()));

		Invalidate();
	}
	else
	{
		if (pDoc->IsShapeDragged())
		{
			m_cursorChangeToNormal = true;
			OnSetCursor(this, 0, 0);

			int dragIndex = pDoc->GetDraggedShapeIndex();
			auto& shapeCtrls = pDoc->GetShapes();
			pDoc->SetSelectedShapeIndex(dragIndex);
			pDoc->AddCommand(new CMoveCommand(pDoc, dragIndex, m_startDragPoint, shapeCtrls[dragIndex]->GetPosition()));
			pDoc->SetUndragged();

			Invalidate();
		}
	}
	//ReleaseCapture();
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
			auto& shapes = pDoc->GetShapes();
			int selIndex = pDoc->GetSelectedShapeIndex();
			pDoc->AddCommand(new CDeleteShapeCommand(pDoc, shapes[selIndex]->GetShapeType(), shapes[selIndex]->GetBoundingBox(), pDoc->GetSelectedShapeIndex()));
			pDoc->DeleteShapeCtrl(pDoc->GetSelectedShapeIndex());
			pDoc->SetSelectedShapeIndex(-1);
			
			Invalidate();
		}
	}
}

void CDrawerView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

	auto clientRect = GetClientRectangle();
	CSize size;
	size.cx = clientRect.Width;
	size.cy = clientRect.Height;
	SetScrollSizes(MM_TEXT, size);
}
// CDrawerView diagnostics

#ifdef _DEBUG
void CDrawerView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDrawerView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDrawerDoc* CDrawerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawerDoc)));
	return (CDrawerDoc*)m_pDocument;
}
#endif //_DEBUG


void CDrawerView::CreateShape(ShapeType type)
{
	CDrawerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	auto clientRectangle = GetClientRectangle();
	Gdiplus::Rect drawRect;
	LONG width = 0;
	LONG height = 0;
	switch (type)
	{
	case ShapeType::TRIANGLE:
		{
			width = TRIANGLE_WIDTH_START;
			height = TRIANGLE_HEIGHT_START;
		}
		break;
	case ShapeType::RECTANGLE:
		{
			width = RECTANGLE_WIDTH_START;
			height = RECTANGLE_HEIGHT_START;
		}
		break;
	case ShapeType::ELLIPSE:
		{
			width = ELLIPSE_WIDTH_START;
			height = ELLIPSE_HEIGHT_START;
		}
		break;
	}
	drawRect.Width = width;
	drawRect.Height = height;
	drawRect.X = (clientRectangle.Width - width) / 2;
	drawRect.Y = (clientRectangle.Height - height) / 2;

	auto shapeCtrl = pDoc->CreateShapeCtrl(type, drawRect);
	pDoc->AddCommand(new CCreateShapeCommand(pDoc, type, drawRect));

	if (shapeCtrl)
	{
		pDoc->SetSelectedShapeIndex(-1);
		Invalidate();
	}
}

// CDrawerView message handlers

void CDrawerView::OnButtonRectangle()
{
	CreateShape(ShapeType::RECTANGLE);
}

void CDrawerView::OnButtonEllipse()
{
	CreateShape(ShapeType::ELLIPSE);
}

void CDrawerView::OnButtonTriangle()
{
	CreateShape(ShapeType::TRIANGLE);
}

void CDrawerView::OnEditRedo()
{
	CDrawerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->Redo();
	Invalidate();
}

void CDrawerView::OnEditUndo()
{
	CDrawerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->Undo();
	Invalidate();
}

void CDrawerView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	CDrawerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (pDoc->CanUndo())
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}


void CDrawerView::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	CDrawerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (pDoc->CanRedo())
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}
