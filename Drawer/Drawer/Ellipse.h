#pragma once
#include "IShape.h"
#include "EllipseDrawer.h"

class CEllipse :
	public IShape
{
public:
	CEllipse(int x, int y, int width, int height);
	~CEllipse();
	void Draw(CDC*, LPRECT) const override;

private:
	CEllipseDrawer* m_ellipseDrawer;
};

