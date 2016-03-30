#pragma once
#include "stdafx.h"
#include "CShapeController.h"

class IControllerFactory
{
public:
	virtual CShapeController* CreateShapeController(Gdiplus::Rect&&) const = 0;
};

class CEllipseFactory : public IControllerFactory
{
public:
	CShapeController* CreateShapeController(Gdiplus::Rect&& rect) const
	{
		return new CEllipseController(std::forward<Gdiplus::Rect>(rect));
	}
};

class CRectangleFactory : public IControllerFactory
{
public:
	CShapeController* CreateShapeController(Gdiplus::Rect&& rect) const
	{
		return new CRectangleController(std::forward<Gdiplus::Rect>(rect));
	}
};

class CTriangleFactory : public IControllerFactory
{
public:
	CShapeController* CreateShapeController(Gdiplus::Rect&& rect) const
	{
		return new CTriangleController(std::forward<Gdiplus::Rect>(rect));
	}
};