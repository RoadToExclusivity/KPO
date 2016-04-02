#pragma once
#include "stdafx.h"
#include "CShapeController.h"

typedef std::shared_ptr<CShapeController> CtrlPtr;

class IControllerFactory
{
public:
	virtual CtrlPtr CreateShapeController(Gdiplus::Rect&&) const = 0;
};

class CEllipseFactory : public IControllerFactory
{
public:
	CtrlPtr CreateShapeController(Gdiplus::Rect&& rect) const
	{
		return CtrlPtr(new CEllipseController(std::forward<Gdiplus::Rect>(rect)));
	}
};

class CRectangleFactory : public IControllerFactory
{
public:
	CtrlPtr CreateShapeController(Gdiplus::Rect&& rect) const
	{
		return CtrlPtr(new CRectangleController(std::forward<Gdiplus::Rect>(rect)));
	}
};

class CTriangleFactory : public IControllerFactory
{
public:
	CtrlPtr CreateShapeController(Gdiplus::Rect&& rect) const
	{
		return CtrlPtr(new CTriangleController(std::forward<Gdiplus::Rect>(rect)));
	}
};