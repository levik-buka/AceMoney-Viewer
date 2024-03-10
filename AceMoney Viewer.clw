; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "acemoney viewer.h"
LastPage=0

ClassCount=8
Class1=CViewerApp
Class2=CAboutDlg
Class3=CMainFrame
Class4=CViewerDoc
Class5=CViewerView

ResourceCount=6
Resource1=IDR_VIEWERCHARTVIEW_TMPL (English (U.S.))
Resource2=IDD_VIEWERCHARTVIEW_FORM (English (U.S.))
Resource3=IDD_VIEWERMENUVIEW_FORM (English (U.S.))
Class6=CViewerChartView
Resource4=IDR_VIEWERMENUVIEW_TMPL (English (U.S.))
Class7=CViewerMenuView
Resource5=IDD_ABOUTBOX (English (U.S.))
Class8=CToolBarView
Resource6=IDR_MAINFRAME (English (U.S.))

[CLS:CViewerApp]
Type=0
BaseClass=CWinApp
HeaderFile=AceMoney Viewer.h
ImplementationFile=AceMoney Viewer.cpp
Filter=N
VirtualFilter=AC
LastObject=CViewerApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=AceMoney Viewer.cpp
ImplementationFile=AceMoney Viewer.cpp
LastObject=CAboutDlg

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
LastObject=IDC_BUTTON_TEST2
Filter=T
VirtualFilter=fWC

[CLS:CViewerDoc]
Type=0
BaseClass=CDocument
HeaderFile=ViewerDoc.h
ImplementationFile=ViewerDoc.cpp
Filter=N
VirtualFilter=DC
LastObject=CViewerDoc

[CLS:CViewerView]
Type=0
BaseClass=CView
HeaderFile=ViewerView.h
ImplementationFile=ViewerView.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_FILE_PRINT
Command6=ID_APP_ABOUT
Command7=ID_CONTEXT_HELP
Command8=ID_INCOMES_GRAPH
Command9=ID_EXPENSES_GRAPH
Command10=ID_INCOMING_SUM
Command11=ID_OUTCOMING_SUM
CommandCount=11

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_PRINT
Command3=ID_FILE_PRINT_PREVIEW
Command4=ID_FILE_PRINT_SETUP
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_WINDOW_SPLIT
Command14=ID_INCOMES_GRAPH
Command15=ID_EXPENSES_GRAPH
Command16=ID_INCOMING_SUM
Command17=ID_OUTCOMING_SUM
Command18=ID_HELP_FINDER
Command19=ID_APP_ABOUT
CommandCount=19

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_NEXT_VIEW
Command10=ID_HELP
Command11=ID_CONTEXT_HELP
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_PREV_PERIOD
Command17=ID_NEXT_PERIOD
Command18=ID_PREV_VIEW
Command19=ID_EDIT_CUT
Command20=ID_EDIT_UNDO
CommandCount=20

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CToolBarView
ControlCount=0

[DLG:IDD_VIEWERCHARTVIEW_FORM (English (U.S.))]
Type=1
Class=CViewerChartView
ControlCount=0

[CLS:CViewerChartView]
Type=0
HeaderFile=ViewerChartView.h
ImplementationFile=ViewerChartView.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC
LastObject=CViewerChartView

[MNU:IDR_VIEWERCHARTVIEW_TMPL (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[DLG:IDD_VIEWERMENUVIEW_FORM (English (U.S.))]
Type=1
Class=CViewerMenuView
ControlCount=4
Control1=IDC_COMBO_VIEW,combobox,1344340995
Control2=IDC_STATIC,static,1342308352
Control3=IDC_CATEGORY_LIST,SysListView32,1350615313
Control4=IDC_CHECK_ALL,button,1342242819

[CLS:CViewerMenuView]
Type=0
HeaderFile=ViewerMenuView.h
ImplementationFile=ViewerMenuView.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC
LastObject=IDC_CATEGORY_LIST

[MNU:IDR_VIEWERMENUVIEW_TMPL (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[CLS:CToolBarView]
Type=0
HeaderFile=ToolBarView.h
ImplementationFile=ToolBarView.cpp
BaseClass=CDialog
Filter=D
LastObject=CToolBarView
VirtualFilter=dWC

