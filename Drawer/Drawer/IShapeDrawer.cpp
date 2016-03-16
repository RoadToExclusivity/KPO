#include "stdafx.h"
#include "IShapeDrawer.h"
#include "SelectionBox.h"

IShapeDrawer::IShapeDrawer()
{
}

IShapeDrawer::~IShapeDrawer(){}

void IShapeDrawer::DrawSelectionBorder(HDC hDC, const Gdiplus::Rect* rect)
{
	CSelectionBox::DrawSelectionBorder(hDC, rect);
}