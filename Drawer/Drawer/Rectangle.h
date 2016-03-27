#pragma once
#include "IShape.h"
#include "RectangleDrawer.h"

class CRectangle :
	public IShape
{
public:
	CRectangle(int x, int y, int width, int height);
	~CRectangle();
	void Draw(HDC, const Gdiplus::Rect*) const override;
	void DrawSelectionBox(const HDC, const Gdiplus::Rect*) const override;
	bool IsShapePoint(const Gdiplus::Point&) const override;
	bool IsCorrectSize(int newWidth, int newHeight) const override;
	ShapeType GetShapeType() const override;

private:
	static const int RECTANGLE_MIN_WIDTH = 20;
	static const int RECTANGLE_MIN_HEIGHT = 20;

	CRectangleDrawer* m_rectDrawer;
};

