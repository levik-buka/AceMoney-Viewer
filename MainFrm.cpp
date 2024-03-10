// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include <afxadv.h> //Has CRecentFileList class definition.
#include "AceMoney Viewer.h"

#include "MainFrm.h"
#include "viewermenuview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_MRU_FILE1, OnFileMruFile1)
	ON_COMMAND(ID_INCOMING_SUM, OnIncomingSum)
	ON_COMMAND(ID_OUTCOMING_SUM, OnOutcomingSum)
	ON_COMMAND(ID_INCOMES_GRAPH, OnIncomesGraph)
	ON_COMMAND(ID_EXPENSES_GRAPH, OnExpensesGraph)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
//	m_wndSplitter.SetColumnInfo (0, 100, 50);
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
/*	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndReBar.Create(this) ||	
		!m_wndReBar.AddBar(&m_wndToolBar))// || !m_wndReBar.AddBar(&m_wndDlgBar)) 
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}
*/
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// create a splitter with 1 row, 2 columns
	if (!m_wndSplitter.CreateStatic(this, 1, 2, WS_CHILD | WS_VISIBLE ))
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

	// add the first splitter pane - the default view in column 0
	if (!m_wndSplitter.CreateView(0, 0,
		RUNTIME_CLASS(CViewerMenuView), CSize(190, 50), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}

	// add the second splitter pane - an input view in column 1
	if (!m_wndSplitter.CreateView(0, 1,
		RUNTIME_CLASS(CViewerChartView), CSize(0, 0), pContext))
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}

	// activate the input view
	SetActiveView((CView*)m_wndSplitter.GetPane(0,1));
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnFileOpen() 
{
	CFileDialog fileDlg (true);
	if(	fileDlg.DoModal ()==IDOK )
	{	
		CString pathName = fileDlg.GetPathName();
   
		// Implement opening and reading file in here.
		//Change the window's title to the opened file's title.
		
		AfxGetApp()->AddToRecentFileList(pathName);

		OnFileMruFile1 ();	// Open document and updates title
	}
}

void CMainFrame::OnFileMruFile1() 
{
 	CString recentFile = (*((CViewerApp*)AfxGetApp())->GetRecentFileList ()) [0];
	
	CString appTitle;
	appTitle.LoadString(AFX_IDS_APP_TITLE);
	SetWindowText (recentFile + " - " + appTitle);

	//AfxMessageBox (recentFile);

	ASSERT (GetActiveDocument()->IsKindOf(RUNTIME_CLASS(CViewerDoc)));
	GetMenuView ()->ReInit ();
	((CViewerDoc*)GetActiveDocument ())->OnOpenDocument (recentFile);
	if (((CViewerDoc*)GetActiveDocument ())->LoadAceMoneyFile (recentFile))
	{
		GetMenuView ()->InitCategories ();
		GetChartView ()->ReInit ();
	}
}

CViewerChartView* CMainFrame::GetChartView()
{
	ASSERT (m_wndSplitter.GetPane(0,1)->IsKindOf(RUNTIME_CLASS(CViewerChartView)));
	return (CViewerChartView*)m_wndSplitter.GetPane(0,1);
}


CViewerMenuView* CMainFrame::GetMenuView()
{
	ASSERT (m_wndSplitter.GetPane(0,0)->IsKindOf(RUNTIME_CLASS(CViewerMenuView)));
	return (CViewerMenuView*)m_wndSplitter.GetPane(0,0);
}

void CMainFrame::OnIncomingSum() 
{
	CMenu *menu = this->GetMenu ();//->GetSubMenu (0);
	UINT state = menu->GetMenuState(ID_INCOMING_SUM, MF_BYCOMMAND);

	if (state & MF_CHECKED)
	{
		menu->CheckMenuItem(ID_INCOMING_SUM, MF_UNCHECKED | MF_BYCOMMAND);
		GetChartView ()->ShowAverage (INCOMES, FALSE);
	}
	else
	{
		menu->CheckMenuItem(ID_INCOMING_SUM, MF_CHECKED | MF_BYCOMMAND);
		GetChartView ()->ShowAverage (INCOMES, TRUE);
	}
	GetChartView ()->ReInit ();
}

void CMainFrame::OnOutcomingSum() 
{
	CMenu *menu = this->GetMenu ();//->GetSubMenu (0);
	UINT state = menu->GetMenuState(ID_OUTCOMING_SUM, MF_BYCOMMAND);
	if (state & MF_CHECKED)
	{
		menu->CheckMenuItem(ID_OUTCOMING_SUM, MF_UNCHECKED | MF_BYCOMMAND);
		GetChartView ()->ShowAverage (EXPENSES, FALSE);
	}
	else
	{
		menu->CheckMenuItem(ID_OUTCOMING_SUM, MF_CHECKED | MF_BYCOMMAND);
		GetChartView ()->ShowAverage (EXPENSES, TRUE);
	}
	GetChartView ()->ReInit ();
}

void CMainFrame::OnIncomesGraph() 
{
	CMenu *menu = this->GetMenu ();//->GetSubMenu (0);
	UINT state = menu->GetMenuState(ID_INCOMES_GRAPH, MF_BYCOMMAND);

	if (state & MF_CHECKED)
	{
		menu->CheckMenuItem(ID_INCOMES_GRAPH, MF_UNCHECKED | MF_BYCOMMAND);
		GetChartView ()->ShowGraph (INCOMES, FALSE);
	}
	else
	{
		menu->CheckMenuItem(ID_INCOMES_GRAPH, MF_CHECKED | MF_BYCOMMAND);
		GetChartView ()->ShowGraph (INCOMES, TRUE);
	}
	GetChartView ()->ReInit ();
}

void CMainFrame::OnExpensesGraph() 
{
	CMenu *menu = this->GetMenu ();//->GetSubMenu (0);
	UINT state = menu->GetMenuState(ID_EXPENSES_GRAPH, MF_BYCOMMAND);
	if (state & MF_CHECKED)
	{
		menu->CheckMenuItem(ID_EXPENSES_GRAPH, MF_UNCHECKED | MF_BYCOMMAND);
		GetChartView ()->ShowGraph (EXPENSES, FALSE);
	}
	else
	{
		menu->CheckMenuItem(ID_EXPENSES_GRAPH, MF_CHECKED | MF_BYCOMMAND);
		GetChartView ()->ShowGraph (EXPENSES, TRUE);
	}
	GetChartView ()->ReInit ();
}
