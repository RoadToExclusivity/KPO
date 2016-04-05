#pragma once
#include "CShapeController.h"

class IShapeCommand
{
public:
	virtual ~IShapeCommand() {};
	virtual void Undo() = 0;
	virtual void Redo() = 0;

protected:
	CShapeController* shapeCtrl;
	IShapeCommand(CShapeController* ctrl) : shapeCtrl(ctrl) {};
};