#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Drawer.h"
#endif

#include "DrawerDoc.h"

#include <propkey.h>
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDrawerDoc

IMPLEMENT_DYNCREATE(CDrawerDoc, CDocument)

BEGIN_MESSAGE_MAP(CDrawerDoc, CDocument)
END_MESSAGE_MAP()


// CDrawerDoc construction/destruction

CDrawerDoc::CDrawerDoc()
	:m_shapes()
{
	// TODO: add one-time construction code here

}

CDrawerDoc::~CDrawerDoc()
{
}

IShape* CDrawerDoc::CreateRectangle(const LPRECT rect)
{
	LONG width = rect->right;
	LONG height = rect->bottom;
	auto newRect = new CRectangle((width - RECTANGLE_WIDTH_START) / 2, (height - RECTANGLE_HEIGHT_START) / 2,
									RECTANGLE_WIDTH_START, RECTANGLE_HEIGHT_START);
	if (newRect)
	{
		m_shapes.push_back(newRect);
	}
	
	return newRect;
}

IShape* CDrawerDoc::CreateEllipse(const LPRECT rect)
{
	LONG width = rect->right;
	LONG height = rect->bottom;
	auto newEllipse = new CEllipse((width - ELLIPSE_WIDTH_START) / 2, (height - ELLIPSE_HEIGHT_START) / 2,
		ELLIPSE_WIDTH_START, ELLIPSE_HEIGHT_START);
	if (newEllipse)
	{
		m_shapes.push_back(newEllipse);
	}

	return newEllipse;
}

IShape* CDrawerDoc::CreateTriangle(const LPRECT rect)
{
	LONG width = rect->right;
	LONG height = rect->bottom;
	auto newTriangle = new CTriangle((width - TRIANGLE_WIDTH_START) / 2, (height - TRIANGLE_HEIGHT_START) / 2,
		TRIANGLE_WIDTH_START, TRIANGLE_HEIGHT_START);
	if (newTriangle)
	{
		m_shapes.push_back(newTriangle);
	}

	return newTriangle;
}

const std::vector<IShape*> CDrawerDoc::GetShapes() const
{
	return m_shapes;
}

void CDrawerDoc::PushShape(IShape* shape)
{
	m_shapes.push_back(shape);
}

BOOL CDrawerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_shapes.clear();
	
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// CDrawerDoc serialization

void CDrawerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_shapes.size();
		for (size_t i = 0; i < m_shapes.size(); ++i)
		{
			auto box = m_shapes[i]->GetBoundingBox();
			ar << (int)m_shapes[i]->GetShapeType() << box->X << box->Y << box->Width << box->Height;
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
			IShape* newShape = nullptr;
			switch (type)
			{
			case ShapeType::TRIANGLE:
				newShape = new CTriangle(x, y, width, height);
				break;
			case ShapeType::RECTANGLE:
				newShape = new CRectangle(x, y, width, height);
				break;
			case ShapeType::ELLIPSE:
				newShape = new CEllipse(x, y, width, height);
				break;
			}
			m_shapes.push_back(newShape);
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
