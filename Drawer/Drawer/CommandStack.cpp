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
	if (m_commands.size() > 0 && ((size_t)(m_curCmd + 1) < m_commands.size()))
	{
		m_commands.erase(m_commands.begin() + 1 + m_curCmd, m_commands.end());
	}
	m_commands.push_back(CmdPtr(cmd));
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
	if ((size_t)(m_curCmd + 1) < m_commands.size())
	{
		m_commands[m_curCmd + 1]->Redo();
		m_curCmd++;
	}
}

bool CCommandStack::CanUndo() const
{
	return m_curCmd > -1;
}

bool CCommandStack::CanRedo() const
{
	return (size_t)(m_curCmd + 1) < m_commands.size();
}