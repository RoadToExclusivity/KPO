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

// DrawerDoc.h : interface of the CDrawerDoc class
//


#pragma once
#include "CShapeController.h"
#include "IControllerFactory.h"

class CDrawerDoc : public CDocument
{
protected: // create from serialization only
	CDrawerDoc();
	DECLARE_DYNCREATE(CDrawerDoc)

// Attributes
public:
	const std::vector<CtrlPtr> GetShapes() const;
	bool CreateRectangle(LPRECT);
	bool CreateEllipse(LPRECT);
	bool CreateTriangle(LPRECT);
	void SetShapeResized();
	void SetShapeUnresized();
	bool IsShapeResized() const;
	void SetSelectedShapeIndex(int shapeIndex);
	int GetSelectedShapeIndex() const;
	void SetDragged(int shapeIndex);
	void SetUndragged();
	bool IsShapeDragged() const;
	int GetDraggedShapeIndex() const;
	void DeleteShapeCtrl(int index);
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument() override;
	virtual BOOL OnOpenDocument(LPCTSTR lpszPath) override;
	virtual void Serialize(CArchive& ar) override;
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CDrawerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

private:
	void InitVars();

	const LONG RECTANGLE_WIDTH_START = 200;
	const LONG RECTANGLE_HEIGHT_START = 100;
	const LONG ELLIPSE_WIDTH_START = 200;
	const LONG ELLIPSE_HEIGHT_START = 200;
	const LONG TRIANGLE_WIDTH_START = 100;
	const LONG TRIANGLE_HEIGHT_START = 150;
	std::vector<CtrlPtr> m_shapesControllers;
	CEllipseFactory m_ellipseFactory;
	CRectangleFactory m_rectFactory;
	CTriangleFactory m_triangleFactory;

	bool m_isShapeResized;
	int m_selectedShapeIndex;
	int m_dragShapeIndex;
};
