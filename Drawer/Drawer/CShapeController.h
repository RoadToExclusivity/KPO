#pragma once
#include "IShape.h"
#include "IShapeDrawer.h"
#include "SelectionBoxDrawer.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "Triangle.h"

class CShapeController
{
public:
	virtual ~CShapeController();
	Gdiplus::Rect GetBoundingBox() const;
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
	IShape* m_shape;
	IShapeDrawer* m_shapeDrawer;
	CSelectionBox* m_selectionBox;
};

class CEllipseController : public CShapeController
{
public:
	CEllipseController(Gdiplus::Rect &&rect)
		:CShapeController(new CEllipse(std::forward<Gdiplus::Rect>(rect)), new CEllipseDrawer())
	{
	}
};

class CRectangleController : public CShapeController
{
public:
	CRectangleController(Gdiplus::Rect &&rect)
		:CShapeController(new CRectangle(std::forward<Gdiplus::Rect>(rect)), new CRectangleDrawer())
	{
	}
};

class CTriangleController : public CShapeController
{
public:
	CTriangleController(Gdiplus::Rect &&rect)
		:CShapeController(new CTriangle(std::forward<Gdiplus::Rect>(rect)), new CTriangleDrawer())
	{
	}
};