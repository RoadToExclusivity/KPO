// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// Drawer.h : main header file for the Drawer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CDrawerApp:
// See Drawer.cpp for the implementation of this class
//

class CDrawerApp : public CWinAppEx
{
public:
	CDrawerApp();

// Overrides
public:
	virtual BOOL InitInstance() override;
	virtual int ExitInstance() override;
protected:
	afx_msg void OnClosingMainFrame(CFrameImpl* pFrameImpl) override;

// Implementation
public:
	UINT  m_nAppLook;
	virtual void PreLoadState();
	DECLARE_MESSAGE_MAP()

private:
	afx_msg void OnNewFile();
	afx_msg void OnOpenFile();
	afx_msg void OnOpenRecentFiles(UINT id);

private:
	void SetDocumentSaveState();

	Gdiplus::GdiplusStartupInput m_gdiStartupInput;
	ULONG_PTR m_gdiplusToken;
};

extern CDrawerApp theApp;
