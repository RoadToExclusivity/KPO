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

private:
	CEllipseDrawer* m_ellipseDrawer;
};