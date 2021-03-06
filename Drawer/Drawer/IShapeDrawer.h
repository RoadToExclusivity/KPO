#pragma once

class IShapeDrawer
{
public:
	virtual ~IShapeDrawer();
	virtual void Draw(const HDC hDC, const Gdiplus::Rect&) const = 0;

protected:
	IShapeDrawer();
};

