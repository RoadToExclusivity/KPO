#pragma once
#include "IShape.h"
#include "RectangleDrawer.h"

class CRectangle :
	public IShape
{
public:
	CRectangle(Gdiplus::Rect&&);
	~CRectangle();
	bool IsShapePoint(const Gdiplus::Point&) const override;
	bool IsCorrectSize(int newWidth, int newHeight) const override;
	ShapeType GetShapeType() const override;

private:
	static const int RECTANGLE_MIN_WIDTH = 20;
	static const int RECTANGLE_MIN_HEIGHT = 20;
};

