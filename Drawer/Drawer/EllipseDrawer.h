#pragma once
#include "IShapeDrawer.h"
class CEllipseDrawer :
	public IShapeDrawer
{
public:
	CEllipseDrawer();
	~CEllipseDrawer();

	void Draw(CDC*, const LPRECT) const override;

private:
	CPen* m_pen;
	CBrush* m_brush;
};

