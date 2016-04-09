#include "stdafx.h"
#include "CommandStack.h"


CCommandStack::CCommandStack()
	:m_commands(),
	m_curCmd(-1),
	m_savePoint(-1),
	m_isSavePointDeleted(false)
{
}

CCommandStack::~CCommandStack()
{
}

void CCommandStack::Clear()
{
	m_commands.clear();
	m_curCmd = -1;
	m_savePoint = -1;
	m_isSavePointDeleted = false;
}

void CCommandStack::Insert(IShapeCommand* cmd)
{
	if (m_commands.size() > 0 && ((size_t)(m_curCmd + 1) < m_commands.size()))
	{
		if (m_curCmd < m_savePoint)
		{
			m_isSavePointDeleted = true;
		}

		m_commands.erase(m_commands.cbegin() + 1 + m_curCmd, m_commands.cend());
	}
	m_commands.push_back(CmdPtr(cmd));
	m_curCmd++;
}

void CCommandStack::SetOnSavePoint()
{
	m_savePoint = m_curCmd;
	m_isSavePointDeleted = false;
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

bool CCommandStack::IsOnSavePoint() const
{
	return !m_isSavePointDeleted && (m_curCmd == m_savePoint);
}