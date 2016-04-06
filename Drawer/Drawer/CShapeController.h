#pragma once
#include "IShape.h"
#include "IShapeDrawer.h"
#include "SelectionBoxDrawer.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "Triangle.h"

typedef std::unique_ptr<IShape> ShapePtr;
typedef std::unique_ptr<IShapeDrawer> ShapeDrawerPtr;
typedef std::unique_ptr<CSelectionBoxDrawer> SelectionDrawerPtr;

class CShapeController
{
public:
	virtual ~CShapeController();
	Gdiplus::Rect GetBoundingBox() const;
	void SetBoundingBox(const Gdiplus::Rect&);
	void Draw(const HDC) const;
	void DrawSelectionBox(const HDC) const;
	Gdiplus::Point GetPosition() const;
	void SetPosition(const Gdiplus::Point&);
	ShapeType GetShapeType() const;
	bool IsShapePoint(const Gdiplus::Point&) const;
	SelectionBoxMarkerState IsPointAtMarker(const Gdiplus::Point&) const;
	void ChangeShapeSize(SelectionBoxMarkerState state, const Gdiplus::Point&);

protected:
	CShapeController(IShape*, IShapeDrawer*);
private:
	ShapePtr m_shape;
	ShapeDrawerPtr m_shapeDrawer;
	SelectionDrawerPtr m_selectionBox;
};

class CEllipseController : public CShapeController
{
public:
	CEllipseController(const Gdiplus::Rect &rect)
		:CShapeController(new CEllipse(rect), new CEllipseDrawer())
	{
	}
};

class CRectangleController : public CShapeController
{
public:
	CRectangleController(const Gdiplus::Rect &rect)
		:CShapeController(new CRectangle(rect), new CRectangleDrawer())
	{
	}
};

class CTriangleController : public CShapeController
{
public:
	CTriangleController(const Gdiplus::Rect &rect)
		:CShapeController(new CTriangle(rect), new CTriangleDrawer())
	{
	}
};