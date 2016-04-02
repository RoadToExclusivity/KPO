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


class CDrawerView : public CView
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
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
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
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtonRectangle();
	afx_msg void OnButtonEllipse();
	afx_msg void OnButtonTriangle();
private:
	const LPRECT GetClientRectangle();
	LPRECT m_clientRectangle;

	bool m_cursorChangeToCross;
	bool m_cursorChangeToNormal;
	bool m_cursorChangeToSizeWE;
	bool m_cursorChangeToSizeEW;
	SelectionBoxMarkerState m_resizeSelectionMarker;
	Gdiplus::Point m_diffPointPosition;
	Gdiplus::SolidBrush m_backgroundBrush;
};

#ifndef _DEBUG  // debug version in DrawerView.cpp
inline CDrawerDoc* CDrawerView::GetDocument() const
   { return reinterpret_cast<CDrawerDoc*>(m_pDocument); }
#endif

