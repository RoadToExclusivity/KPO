#include "stdafx.h"
#include "CommandStack.h"


CCommandStack::CCommandStack()
	:m_commands(),
	m_curCmd(-1)
{
}

CCommandStack::~CCommandStack()
{
}

void CCommandStack::Clear()
{
	m_commands.clear();
	m_curCmd = -1;
}

void CCommandStack::Insert(IShapeCommand* cmd)
{
	m_commands.push_back(cmd);
	m_curCmd++;
}

void CCommandStack::Undo()
{
	if (m_curCmd > -1)
	{
		m_commands[m_curCmd]->Undo();
		m_curCmd--;
	}
}

void CCommandStack::Redo()
{
	if (m_curCmd < m_commands.size())
	{
		m_commands[m_curCmd]->Redo();
		m_curCmd++;
	}
}

bool CCommandStack::CanUndo() const
{
	return m_curCmd > -1;
}

bool CCommandStack::CanRedo() const
{
	return m_curCmd < m_commands.size();
}