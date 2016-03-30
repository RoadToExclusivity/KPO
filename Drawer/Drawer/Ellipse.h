#pragma once
#include "IShape.h"
#include "EllipseDrawer.h"

class CEllipse :
	public IShape
{
public:
	CEllipse(Gdiplus::Rect&&);
	~CEllipse();
	bool IsShapePoint(const Gdiplus::Point&) const override;
	bool IsCorrectSize(int newWidth, int newHeight) const override;
	ShapeType GetShapeType() const override;

private:
	static const int ELLIPSE_MIN_WIDTH = 50;
	static const int ELLIPSE_MIN_HEIGHT = 50;
};