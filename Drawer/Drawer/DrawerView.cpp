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
	m_cursorCross(false),
	m_cursorNE(false),
	m_cursorNW(false),
	m_backgroundBrush(Gdiplus::Color(255, 255, 255)),
	m_resizeSelectionMarker(SelectionBoxMarkerState::NONE)
{
	SetStandardCursor();
}

CDrawerView::~CDrawerView()
{
}

BOOL CDrawerView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.cx = VIEW_WIDTH;
	cs.cy = VIEW_HEIGHT;

	return CScrollView::PreCreateWindow(cs);
}

void CDrawerView::OnInitialUpdate()
{	
	SetScrollsState();

	CScrollView::OnInitialUpdate();
}

// CDrawerView message functions

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

	auto& shapeCtrls = pDoc->GetShapes();
	for (const auto& ctrl : shapeCtrls)
	{
		ctrl->Draw(bufferHDC);
	}

	if (pDoc->IsShapeSelected())
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

	SetCapture();
	Gdiplus::Point gdiPoint(point.x, point.y);
	GetActualPoint(gdiPoint);
	auto& shapeCtrls = pDoc->GetShapes();
	if (pDoc->IsShapeSelected())
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

	pDoc->SetUnselected();
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

	Gdiplus::Point gdiPoint(point.x, point.y);
	GetActualPoint(gdiPoint);
	NormalizeGdiPoint(gdiPoint);

	if (pDoc->IsShapeResized())
	{
		auto& shapeCtrls = pDoc->GetShapes();
		shapeCtrls[pDoc->GetSelectedShapeIndex()]->ChangeShapeSize(m_resizeSelectionMarker, gdiPoint);
		if (m_resizeSelectionMarker == SelectionBoxMarkerState::BOTTOM_LEFT ||
			m_resizeSelectionMarker == SelectionBoxMarkerState::TOP_RIGHT)
		{
			if (!m_cursorNE)
			{
				SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENESW));
				m_cursorNE = true;
			}
		}
		else
		{
			if (!m_cursorNW)
			{
				SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENWSE));
				m_cursorNW = true;
			}
		}

		Invalidate();
	}
	else
	{
		if (pDoc->IsShapeDragged())
		{
			if (!m_cursorCross)
			{
				SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
				m_cursorCross = true;
			}

			auto& shapeCtrls = pDoc->GetShapes();
			auto newPos = m_diffPointPosition + gdiPoint;

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
		SetStandardCursor();

		auto& shapeCtrls = pDoc->GetShapes();
		size_t resizeIndex = pDoc->GetSelectedShapeIndex();
		auto shapeRect = shapeCtrls[resizeIndex]->GetBoundingBox();
		if (!IsEqualRects(m_startResizeRect, shapeRect))
		{
			pDoc->AddCommand(new CResizeCommand(pDoc, resizeIndex, m_startResizeRect, shapeRect));
		}

		Invalidate();
	}
	else
	{
		if (pDoc->IsShapeDragged())
		{
			SetStandardCursor();

			size_t dragIndex = pDoc->GetDraggedShapeIndex();
			auto& shapeCtrls = pDoc->GetShapes();
			pDoc->SetSelectedShapeIndex(dragIndex);
			auto shapePos = shapeCtrls[dragIndex]->GetPosition();
			if (!IsEqualPoints(m_startDragPoint, shapePos))
			{
				pDoc->AddCommand(new CMoveCommand(pDoc, dragIndex, m_startDragPoint, shapePos));
			}
			pDoc->SetUndragged();

			Invalidate();
		}
	}
	ReleaseCapture();
}

BOOL CDrawerView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

void CDrawerView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DELETE)
	{
		CDrawerDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		if (pDoc->IsShapeSelected() && !pDoc->IsShapeResized())
		{
			auto& shapes = pDoc->GetShapes();
			size_t selIndex = pDoc->GetSelectedShapeIndex();
			pDoc->AddCommand(new CDeleteShapeCommand(pDoc, shapes[selIndex]->GetShapeType(), shapes[selIndex]->GetBoundingBox(), pDoc->GetSelectedShapeIndex()));
			pDoc->DeleteShapeCtrl(pDoc->GetSelectedShapeIndex());
			pDoc->SetUnselected();
			
			Invalidate();
		}
	}
}

void CDrawerView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);
	SetScrollsState();
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

// CDrawerView internal functions

Gdiplus::Rect CDrawerView::GetClientRectangle() const
{
	GetClientRect(&m_clientRectangle);
	m_clientRectangle.right = max(VIEW_WIDTH, m_clientRectangle.right);
	m_clientRectangle.bottom = max(VIEW_HEIGHT, m_clientRectangle.bottom);

	return Gdiplus::Rect(0, 0, m_clientRectangle.right, m_clientRectangle.bottom);
}

void CDrawerView::CreateShape(ShapeType type)
{
	CDrawerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Gdiplus::Rect drawRect = GetStartShapeRect(type);

	bool isCreated = pDoc->CreateShapeCtrl(type, drawRect);
	pDoc->AddCommand(new CCreateShapeCommand(pDoc, type, drawRect));

	if (isCreated)
	{
		pDoc->SetUnselected();
		Invalidate();
	}
}

Gdiplus::Rect CDrawerView::GetStartShapeRect(ShapeType type) const
{
	Gdiplus::Rect resultRect;

	auto clientRectangle = GetClientRectangle();
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

	resultRect.Width = width;
	resultRect.Height = height;
	resultRect.X = (clientRectangle.Width - width) / 2;
	resultRect.Y = (clientRectangle.Height - height) / 2;

	return resultRect;
}

void CDrawerView::SetScrollsState()
{
	auto clientRect = GetClientRectangle();
	SetScrollSizes(MM_TEXT, CSize(clientRect.Width, clientRect.Height));
}

void CDrawerView::SetStandardCursor()
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	m_cursorCross = m_cursorNE = m_cursorNW = false;
}

void CDrawerView::GetActualPoint(Gdiplus::Point &point) const
{
	BOOL hasHBar = false, hasVBar = false;
	CheckScrollBars(hasHBar, hasVBar);
	auto scrollPoint = GetScrollPosition();

	if (hasHBar)
	{
		point.X += scrollPoint.x;
	}

	if (hasVBar)
	{
		point.Y += scrollPoint.y;
	}
}

void CDrawerView::NormalizeGdiPoint(Gdiplus::Point &point) const
{
	auto clientRect = GetClientRectangle();
	if (point.X < 0) point.X = 0;
	if (point.X > clientRect.Width) point.X = clientRect.Width;
	if (point.Y < 0) point.Y = 0;
	if (point.Y > clientRect.Height) point.Y = clientRect.Height;
}

bool CDrawerView::IsEqualPoints(const Gdiplus::Point &first, const Gdiplus::Point &second) const
{
	return (first.X == second.X) && (first.Y == second.Y);
}

bool CDrawerView::IsEqualRects(const Gdiplus::Rect &first, const Gdiplus::Rect &second) const
{
	return (first.X == second.X) && (first.Y == second.Y) && (first.Width == second.Width) && (first.Height == second.Height);
}