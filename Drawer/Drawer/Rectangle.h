#pragma once
#include "IShape.h"
#include "RectangleDrawer.h"

class CRectangle :
	public IShape
{
public:
	CRectangle(int x, int y, int width, int height);
	~CRectangle();
	void Draw(CDC*, LPRECT) const override;

private:
	CRectangleDrawer* m_rectDrawer;
};

