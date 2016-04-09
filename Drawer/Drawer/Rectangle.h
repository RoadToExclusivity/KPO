#pragma once
#include "IShape.h"
#include "RectangleDrawer.h"

class CRectangle :
	public IShape
{
public:
	CRectangle(const Gdiplus::Rect& rect);
	
	bool IsShapePoint(const Gdiplus::Point& shapePoint) const override;
	bool IsCorrectWidth(int newWidth) const override;
	bool IsCorrectHeight(int newHeight) const override;
	ShapeType GetShapeType() const override;

private:
	static const int RECTANGLE_MIN_WIDTH = 20;
	static const int RECTANGLE_MIN_HEIGHT = 20;
};

