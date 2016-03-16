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

private:
	CRectangleDrawer* m_rectDrawer;
};

