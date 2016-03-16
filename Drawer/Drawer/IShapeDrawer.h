#pragma once

class IShapeDrawer
{
public:
	virtual ~IShapeDrawer();
	virtual void Draw(HDC, const Gdiplus::Rect*) const = 0;
	void DrawSelectionBorder(HDC, const Gdiplus::Rect*);

protected:
	IShapeDrawer();
};

