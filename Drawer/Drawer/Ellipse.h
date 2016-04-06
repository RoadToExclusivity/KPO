#pragma once
#include "IShape.h"
#include "EllipseDrawer.h"

class CEllipse :
	public IShape
{
public:
	CEllipse(const Gdiplus::Rect&);
	~CEllipse();
	bool IsShapePoint(const Gdiplus::Point&) const override;
	bool IsCorrectWidth(int newWidth) const override;
	bool IsCorrectHeight(int newHeight) const override;
	ShapeType GetShapeType() const override;

private:
	static const int ELLIPSE_MIN_WIDTH = 50;
	static const int ELLIPSE_MIN_HEIGHT = 50;
};