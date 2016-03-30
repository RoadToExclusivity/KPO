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
	m_triangleFactory()
{
	// TODO: add one-time construction code here

}

CDrawerDoc::~CDrawerDoc()
{
	m_shapesControllers.clear();
}

bool CDrawerDoc::CreateRectangle(const LPRECT rect)
{
	LONG width = rect->right;
	LONG height = rect->bottom;
	auto newRectController =  m_rectFactory.CreateShapeController(Gdiplus::Rect((width - RECTANGLE_WIDTH_START) / 2, 
														(height - RECTANGLE_HEIGHT_START) / 2,
														RECTANGLE_WIDTH_START, RECTANGLE_HEIGHT_START));
	if (newRectController)
	{
		m_shapesControllers.push_back(std::unique_ptr<CShapeController>(newRectController));
	}
	
	return newRectController != nullptr;
}

bool CDrawerDoc::CreateEllipse(const LPRECT rect)
{
	LONG width = rect->right;
	LONG height = rect->bottom;
	auto newEllipseController = m_ellipseFactory.CreateShapeController(Gdiplus::Rect((width - ELLIPSE_WIDTH_START) / 2,
														(height - ELLIPSE_HEIGHT_START) / 2,
														ELLIPSE_WIDTH_START, ELLIPSE_HEIGHT_START));
	if (newEllipseController)
	{
		m_shapesControllers.emplace_back(std::unique_ptr<CShapeController>(newEllipseController));
	}

	return newEllipseController != nullptr;
}

bool CDrawerDoc::CreateTriangle(const LPRECT rect)
{
	LONG width = rect->right;
	LONG height = rect->bottom;
	auto newTriangleController = m_triangleFactory.CreateShapeController(Gdiplus::Rect((width - TRIANGLE_WIDTH_START) / 2,
															(height - TRIANGLE_HEIGHT_START) / 2,
															TRIANGLE_WIDTH_START, TRIANGLE_HEIGHT_START));
	if (newTriangleController)
	{
		m_shapesControllers.emplace_back(std::unique_ptr<CShapeController>(newTriangleController));
	}

	return newTriangleController != nullptr;
}

const std::vector<std::unique_ptr<CShapeController>> CDrawerDoc::GetShapes() const
{
	return m_shapesControllers;
}

BOOL CDrawerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_shapesControllers.clear();
	
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

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
			CShapeController* newShapeCtrl = nullptr;
			switch (type)
			{
			case ShapeType::TRIANGLE:
				newShapeCtrl = m_triangleFactory.CreateShapeController(Gdiplus::Rect(x, y, width, height));
				break;
			case ShapeType::RECTANGLE:
				newShapeCtrl = m_rectFactory.CreateShapeController(Gdiplus::Rect(x, y, width, height));
				break;
			case ShapeType::ELLIPSE:
				newShapeCtrl = m_ellipseFactory.CreateShapeController(Gdiplus::Rect(x, y, width, height));
				break;
			}
			if (newShapeCtrl)
			{
				m_shapesControllers.emplace_back(std::unique_ptr<CShapeController>(newShapeCtrl));
			}
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
