#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Drawer.h"
#endif

#include "DrawerDoc.h"

#include <propkey.h>
#include "CShapeController.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDrawerDoc

IMPLEMENT_DYNCREATE(CDrawerDoc, CDocument)

BEGIN_MESSAGE_MAP(CDrawerDoc, CDocument)
END_MESSAGE_MAP()


// CDrawerDoc construction/destruction

CDrawerDoc::CDrawerDoc()
	:m_shapesControllers(),
	m_ellipseFactory(),
	m_rectFactory(),
	m_triangleFactory(),
	m_isShapeResized(false),
	m_isShapeSelected(false),
	m_isShapeDragged(false),
	m_selectedShapeIndex(0),
	m_draggedShapeIndex(0),
	m_commands()
{
	m_factories[0] = &m_triangleFactory;
	m_factories[1] = &m_rectFactory;
	m_factories[2] = &m_ellipseFactory;
}

CDrawerDoc::~CDrawerDoc()
{
}

void CDrawerDoc::InitVars()
{
	m_shapesControllers.clear();
	m_isShapeResized = false;
	m_isShapeSelected = false;
	m_isShapeDragged = false;
	m_selectedShapeIndex = 0;
	m_draggedShapeIndex = 0;

	m_commands.Clear();
}

BOOL CDrawerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
	{
		return FALSE;
	}
		
	InitVars();

	return TRUE;
}

BOOL CDrawerDoc::OnOpenDocument(LPCTSTR lpszPath)
{
	InitVars();

	if (!CDocument::OnOpenDocument(lpszPath))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDrawerDoc::OnSaveDocument(LPCTSTR lpszPath)
{
	if (!CDocument::OnSaveDocument(lpszPath))
	{
		return FALSE;
	}

	m_commands.SetOnSavePoint();
	SetModifiedFlag(FALSE);

	return TRUE;
}
// CDrawerDoc serialization

void CDrawerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_shapesControllers.size();
		for (size_t i = 0; i < m_shapesControllers.size(); ++i)
		{
			const auto& ctrl = m_shapesControllers[i];
			auto box = ctrl->GetBoundingBox();
			ar << (int)(ctrl->GetShapeType()) << box.X << box.Y << box.Width << box.Height;
		}
	}
	else
	{
		size_t shapesCount;
		ar >> shapesCount;
		for (size_t i = 0; i < shapesCount; ++i)
		{
			int intType;
			ar >> intType;
			ShapeType type = ShapeType(intType);
			int x, y, width, height;
			ar >> x >> y >> width >> height;
			CreateShapeCtrl(type, Gdiplus::Rect(x, y, width, height));
		}
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CDrawerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CDrawerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CDrawerDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CDrawerDoc diagnostics

#ifdef _DEBUG
void CDrawerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDrawerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDrawerDoc commands

const std::vector<CtrlPtr>& CDrawerDoc::GetShapes() const
{
	return m_shapesControllers;
}

size_t CDrawerDoc::GetShapesCount() const
{
	return m_shapesControllers.size();
}

bool CDrawerDoc::CreateShapeCtrl(ShapeType type, const Gdiplus::Rect& rect, int pos)
{
	LONG width = rect.Width;
	LONG height = rect.Height;

	const IControllerFactory* factory = m_factories[(int)type];
	CtrlPtr newRectController = factory->CreateShapeController(rect);

	if (newRectController)
	{
		if (pos == -1)
		{
			m_shapesControllers.push_back(newRectController);
		}
		else
		{
			m_shapesControllers.insert(m_shapesControllers.cbegin() + pos, newRectController);
		}
	}

	return newRectController != nullptr;
}

void CDrawerDoc::SetShapeResized()
{
	m_isShapeResized = true;
}

void CDrawerDoc::SetShapeUnresized()
{
	m_isShapeResized = false;
}

bool CDrawerDoc::IsShapeResized() const
{
	return m_isShapeResized;
}

void CDrawerDoc::SetSelectedShapeIndex(size_t shapeIndex)
{
	m_isShapeSelected = true;
	m_selectedShapeIndex = shapeIndex;
}

void CDrawerDoc::SetUnselected()
{
	m_isShapeSelected = false;
}

bool CDrawerDoc::IsShapeSelected() const
{
	return m_isShapeSelected;
}

size_t CDrawerDoc::GetSelectedShapeIndex() const
{
	return m_selectedShapeIndex;
}

void CDrawerDoc::SetDragged(size_t shapeIndex)
{
	m_isShapeDragged = true;
	m_draggedShapeIndex = shapeIndex;
}

void CDrawerDoc::SetUndragged()
{
	m_isShapeDragged = false;
}

bool CDrawerDoc::IsShapeDragged() const
{
	return m_isShapeDragged;
}

size_t CDrawerDoc::GetDraggedShapeIndex() const
{
	return m_draggedShapeIndex;
}

void CDrawerDoc::DeleteShapeCtrl(size_t index)
{
	m_shapesControllers.erase(m_shapesControllers.begin() + index);
}

void CDrawerDoc::AddCommand(IShapeCommand* cmd)
{
	m_commands.Insert(cmd);
}

void CDrawerDoc::Undo()
{
	m_commands.Undo();
}

void CDrawerDoc::Redo()
{
	m_commands.Redo();
}

bool CDrawerDoc::CanUndo() const
{
	return m_commands.CanUndo();
}

bool CDrawerDoc::CanRedo() const
{
	return m_commands.CanRedo();
}

bool CDrawerDoc::NeedSave() const
{
	return !m_commands.IsOnSavePoint();
}