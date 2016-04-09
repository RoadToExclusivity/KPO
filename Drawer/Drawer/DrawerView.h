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

// DrawerView.h : interface of the CDrawerView class
//

#pragma once


class CDrawerView : public CScrollView
{
protected: // create from serialization only
	CDrawerView();
	DECLARE_DYNCREATE(CDrawerView)

// Attributes
public:
	CDrawerDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC) override;  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override;
	virtual void OnInitialUpdate() override;
protected:

// Implementation
public:
	virtual ~CDrawerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

private:
	afx_msg void OnButtonRectangle();
	afx_msg void OnButtonEllipse();
	afx_msg void OnButtonTriangle();
	afx_msg void OnEditRedo();
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);

private:
	static const int VIEW_WIDTH = 640;
	static const int VIEW_HEIGHT = 480;

	const LONG RECTANGLE_WIDTH_START = 200;
	const LONG RECTANGLE_HEIGHT_START = 100;
	const LONG ELLIPSE_WIDTH_START = 200;
	const LONG ELLIPSE_HEIGHT_START = 200;
	const LONG TRIANGLE_WIDTH_START = 100;
	const LONG TRIANGLE_HEIGHT_START = 150;

	Gdiplus::Rect GetClientRectangle() const;
	void CreateShape(ShapeType type);
	Gdiplus::Rect GetStartShapeRect(ShapeType type) const;
	void SetScrollsState();
	void SetStandardCursor();
	void GetActualPoint(Gdiplus::Point& point) const;
	void NormalizeGdiPoint(Gdiplus::Point& point) const;
	bool IsEqualPoints(const Gdiplus::Point& first, const Gdiplus::Point& second) const;
	bool IsEqualRects(const Gdiplus::Rect& first, const Gdiplus::Rect& second) const;

	mutable RECT m_clientRectangle;
	bool m_cursorCross;
	bool m_cursorNW;
	bool m_cursorNE;
	SelectionBoxMarkerState m_resizeSelectionMarker;
	Gdiplus::Point m_diffPointPosition;
	Gdiplus::Point m_startDragPoint;
	Gdiplus::Rect m_startResizeRect;
	const Gdiplus::SolidBrush m_backgroundBrush;
};

#ifndef _DEBUG  // debug version in DrawerView.cpp
inline CDrawerDoc* CDrawerView::GetDocument() const
   { return reinterpret_cast<CDrawerDoc*>(m_pDocument); }
#endif

