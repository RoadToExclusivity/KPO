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

// Drawer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Drawer.h"
#include "MainFrm.h"
#include "DrawerDoc.h"
#include "DrawerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawerApp

BEGIN_MESSAGE_MAP(CDrawerApp, CWinAppEx)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CDrawerApp::OnNewFile)
	ON_COMMAND(ID_FILE_OPEN, &CDrawerApp::OnOpenFile)
	ON_COMMAND_RANGE(ID_FILE_MRU_FIRST, ID_FILE_MRU_LAST, &CDrawerApp::OnOpenRecentFiles)
END_MESSAGE_MAP()

// CDrawerApp construction

CDrawerApp::CDrawerApp()
{
	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Drawer.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CDrawerApp object

CDrawerApp theApp;


// CDrawerApp initialization

BOOL CDrawerApp::InitInstance()
{
	CWinAppEx::InitInstance();

	Gdiplus::GdiplusStartup(&m_gdiplusToken, &m_gdiStartupInput, nullptr);
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDrawerDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CDrawerView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}

int CDrawerApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
	AfxOleTerm(FALSE);
	
	return CWinAppEx::ExitInstance();
}

void CDrawerApp::OnClosingMainFrame(CFrameImpl* pFrameImpl)
{
	SetDocumentSaveState();

	CWinAppEx::OnClosingMainFrame(pFrameImpl);
}

// CDrawerApp message handlers

void CDrawerApp::OnNewFile()
{
	SetDocumentSaveState();

	CWinAppEx::OnFileNew();
}

void CDrawerApp::OnOpenFile()
{
	SetDocumentSaveState();

	CWinAppEx::OnFileOpen();
}

void CDrawerApp::OnOpenRecentFiles(UINT id)
{
	SetDocumentSaveState();

	CWinAppEx::OnOpenRecentFile(id);
}

// CDrawerApp customization load/save methods

void CDrawerApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CDrawerApp::SetDocumentSaveState()
{
	if (m_pMainWnd)
	{
		CDrawerDoc* doc = (CDrawerDoc*)((CFrameWndEx*)m_pMainWnd)->GetActiveDocument();
		if (doc && doc->NeedSave())
		{
			doc->SetModifiedFlag(TRUE);
		}
	}
}