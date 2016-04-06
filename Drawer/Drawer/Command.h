#pragma once

class CDrawerDoc;

class IShapeCommand
{
public:
	virtual ~IShapeCommand() {};
	virtual void Undo() = 0;
	virtual void Redo() = 0;

protected:
	CDrawerDoc* m_doc;
	IShapeCommand(CDrawerDoc* doc) : m_doc(doc) {};
};