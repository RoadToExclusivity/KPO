#pragma once

class IShapeDrawer
{
public:
	virtual ~IShapeDrawer();
	virtual void Draw(CDC*, const LPRECT) const = 0;
	void DrawSelectionBorder(CDC*, const LPRECT);

protected:
	IShapeDrawer();
};

