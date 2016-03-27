#pragma once
#include "IShape.h"
#include "EllipseDrawer.h"

class CEllipse :
	public IShape
{
public:
	CEllipse(int x, int y, int width, int height);
	~CEllipse();
	void Draw(HDC, const Gdiplus::Rect*) const override;
	void DrawSelectionBox(const HDC, const Gdiplus::Rect*) const override;
	bool IsShapePoint(const Gdiplus::Point&) const override;
	bool IsCorrectSize(int newWidth, int newHeight) const override;
	ShapeType GetShapeType() const override;

private:
	static const int ELLIPSE_MIN_WIDTH = 50;
	static const int ELLIPSE_MIN_HEIGHT = 50;

	CEllipseDrawer* m_ellipseDrawer;
};