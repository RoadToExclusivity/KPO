#include "stdafx.h"
#include "IShapeDrawer.h"
#include "SelectionBox.h"

IShapeDrawer::IShapeDrawer()
{
}

IShapeDrawer::~IShapeDrawer(){}

void IShapeDrawer::DrawSelectionBorder(CDC* pDC, const LPRECT rect)
{
	CSelectionBox::DrawSelectionBorder(pDC, rect);
}