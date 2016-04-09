#pragma once
#include "Command.h"

typedef std::shared_ptr<IShapeCommand> CmdPtr;

class CCommandStack
{
public:
	CCommandStack();
	~CCommandStack();
	
	void Insert(IShapeCommand* cmd);
	void SetOnSavePoint();
	void Clear();
	
	void Undo();
	void Redo();

	bool CanUndo() const;
	bool CanRedo() const;
	bool IsOnSavePoint() const;

private:
	int m_curCmd;
	int m_savePoint;
	bool m_isSavePointDeleted;

	std::vector<CmdPtr> m_commands;
};

