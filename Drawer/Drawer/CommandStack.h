#pragma once
#include "Command.h"

class CCommandStack
{
public:
	CCommandStack();
	~CCommandStack();
	
	void Clear();
	void Insert(IShapeCommand*);
	void Undo();
	void Redo();

	bool CanUndo() const;
	bool CanRedo() const;

private:
	int m_curCmd;
	std::vector<IShapeCommand*> m_commands;
};
