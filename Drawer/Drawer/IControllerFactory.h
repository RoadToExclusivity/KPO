#pragma once
#include "stdafx.h"
#include "CShapeController.h"

typedef std::shared_ptr<CShapeController> CtrlPtr;

class IControllerFactory
{
public:
	virtual CtrlPtr CreateShapeController(const Gdiplus::Rect&) const = 0;
};

class CEllipseFactory : public IControllerFactory
{
public:
	CtrlPtr CreateShapeController(const Gdiplus::Rect& rect) const
	{
		return CtrlPtr(new CEllipseController(rect));
	}
};

class CRectangleFactory : public IControllerFactory
{
public:
	CtrlPtr CreateShapeController(const Gdiplus::Rect& rect) const
	{
		return CtrlPtr(new CRectangleController(rect));
	}
};

class CTriangleFactory : public IControllerFactory
{
public:
	CtrlPtr CreateShapeController(const Gdiplus::Rect& rect) const
	{
		return CtrlPtr(new CTriangleController(rect));
	}
};