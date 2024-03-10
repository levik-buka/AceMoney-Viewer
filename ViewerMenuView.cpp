// ViewerMenuView.cpp : implementation file
//

#include "stdafx.h"
#include "acemoney viewer.h"
#include "10YearsView.h"
#include "YearView.h"
#include "HalfYearView.h"
#include "QuartalView.h"
#include "SeasonView.h"
#include "WeekView.h"
#include "MonthView.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewerMenuView

IMPLEMENT_DYNCREATE(CViewerMenuView, CFormView)

CViewerMenuView::CViewerMenuView()
	: CFormView(CViewerMenuView::IDD)
{
	//{{AFX_DATA_INIT(CViewerMenuView)
	m_SelectAll = FALSE;
	//}}AFX_DATA_INIT

	UserAction = false;
}

CViewerMenuView::~CViewerMenuView()
{
}

void CViewerMenuView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewerMenuView)
	DDX_Control(pDX, IDC_CATEGORY_LIST, m_CategoryList);
	DDX_Control(pDX, IDC_COMBO_VIEW, comboView);
	DDX_Check(pDX, IDC_CHECK_ALL, m_SelectAll);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewerMenuView, CFormView)
	//{{AFX_MSG_MAP(CViewerMenuView)
	ON_CBN_SELCHANGE(IDC_COMBO_VIEW, OnSelchangeComboView)
	ON_COMMAND(ID_NEXT_VIEW, OnNextView)
	ON_COMMAND(ID_PREV_VIEW, OnPrevView)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_CATEGORY_LIST, OnItemchangedCategoryList)
	ON_NOTIFY(NM_CLICK, IDC_CATEGORY_LIST, OnClickCategoryList)
	ON_BN_CLICKED(IDC_CHECK_ALL, OnCheckAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewerMenuView diagnostics

#ifdef _DEBUG
void CViewerMenuView::AssertValid() const
{
	CFormView::AssertValid();
}

void CViewerMenuView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewerMenuView message handlers

CViewerDoc* CViewerMenuView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CViewerDoc)));
	return (CViewerDoc*)m_pDocument;
}

void CViewerMenuView::OnSelchangeComboView() 
{
	// TODO: Add your control notification handler code here
	SetGraphView (comboView.GetCurSel ());
}

void CViewerMenuView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	comboView.AddString ("Week View");
	comboView.SetItemDataPtr (0, new CWeekView ());
	comboView.AddString ("Month View");
	comboView.SetItemDataPtr (1, new CMonthView ());
	comboView.AddString ("Season View");
	comboView.SetItemDataPtr (2, new CSeasonView ());
	comboView.AddString ("Quartal View");
	comboView.SetItemDataPtr (3, new CQuartalView ());
	comboView.AddString ("Half-Year View");
	comboView.SetItemDataPtr (4, new CHalfYearView ());
	comboView.AddString ("Year View");
	comboView.SetItemDataPtr (5, new CYearView ());
	comboView.AddString ("10 Years View");
	comboView.SetItemDataPtr (6, new C10YearsView ());

	m_SelectAll = TRUE;

	m_CategoryList.SetExtendedStyle(m_CategoryList.GetExtendedStyle()|LVS_EX_CHECKBOXES);
	m_CategoryList.InsertColumn (0, "", LVCFMT_LEFT, 300);
	ResizeCategoryList ();

	SetGraphView (5);	// Setting default view (Year View)

	UpdateData (FALSE);
}

void CViewerMenuView::SetGraphView(int Index)
{
	if (Index >= 0 && Index < comboView.GetCount ())
	{
		comboView.SetCurSel (Index);
		((CMainFrame*)AfxGetMainWnd ())->GetChartView ()->SetView ((CGraphView*)comboView.GetItemDataPtr (Index));
	}
}

void CViewerMenuView::OnNextView() 
{
	// TODO: Add your command handler code here
	int CurSel = comboView.GetCurSel ();
	CurSel++;
	if (CurSel == comboView.GetCount ())
	{
		CurSel = 0;
	}

	comboView.SetCurSel (CurSel);
	SetGraphView (CurSel);
}

void CViewerMenuView::OnPrevView() 
{
	// TODO: Add your command handler code here
	int CurSel = comboView.GetCurSel ();
	if (CurSel == 0)
	{
		CurSel = comboView.GetCount ();
	}
	CurSel--;

	comboView.SetCurSel (CurSel);
	SetGraphView (CurSel);
}

void CViewerMenuView::ReInit()
{
	CWeekView::Init ();
	CMonthView::Init ();
	CYearView::Init ();
	C10YearsView::Init ();

	InitCategories ();
}

void CViewerMenuView::OnDestroy() 
{
	for ( int Index = 0; Index < comboView.GetCount (); Index++)
	{
		delete comboView.GetItemDataPtr (Index);
	}

	CFormView::OnDestroy();
}

void CViewerMenuView::InitCategories()
{
	m_SelectAll = TRUE;
	m_CategoryList.DeleteAllItems ();
	UpdateData (FALSE);

	long catCount = GetDocument ()->GetCategoryCount ();

	CString mixed;
	mixed.LoadString (IDS_STRING_MIXED);

	int Index = m_CategoryList.InsertItem (0, mixed);
	m_CategoryList.SetItemData (Index, 0);
	m_CategoryList.SetCheck (Index, m_SelectAll);

	for (long i = 1; i <= catCount; i++)
	{
		CString catName = GetDocument ()->GetCategoryById(i);
		if (!catName.IsEmpty ())
		{
			int Index = m_CategoryList.InsertItem (1, catName);
			m_CategoryList.SetItemData (Index, i);
			m_CategoryList.SetCheck (Index, m_SelectAll);
		}
	}
}

void CViewerMenuView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	ResizeCategoryList ();
}

void CViewerMenuView::ResizeCategoryList()
{
	if (m_CategoryList.m_hWnd != NULL)
	{
		RECT vSize;
		GetClientRect (&vSize);
		//m_CategoryList.GetClientRect (&lSize);
		m_CategoryList.SetWindowPos (NULL, 0, 0, vSize.right - 22, vSize.bottom - 70, 
			SWP_NOMOVE | SWP_NOREPOSITION | SWP_NOZORDER );
	}
}

void CViewerMenuView::OnItemchangedCategoryList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	if (UserAction)
	{
		UserAction = false;
		int Select = -1;
		if ((pNMListView->uOldState == 4096 && pNMListView->uNewState == 8192))
			Select = 1;
		else if ((pNMListView->uOldState == 8192 && pNMListView->uNewState == 4096))
			Select = 0;

		if (Select >= 0)
		{
			if (m_CategoryList.GetItemState(pNMListView->iItem, LVIS_SELECTED) == LVIS_SELECTED)
			{
				OnCheckSelected (Select);
			}
			else
			{
				GetDocument ()->SetCategory(m_CategoryList.GetItemData (pNMListView->iItem), Select);
			}

			((CMainFrame*)AfxGetMainWnd ())->GetChartView ()->ReInit ();		
		}
	}
	*pResult = 0;
}

void CViewerMenuView::OnClickCategoryList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UserAction = true;
	*pResult = 0;
}


void CViewerMenuView::OnCheckAll() 
{
	UpdateData (TRUE);
	for (int i = 0; i < m_CategoryList.GetItemCount (); i++)
	{
		m_CategoryList.SetCheck (i, m_SelectAll);
		GetDocument()->SetCategory(m_CategoryList.GetItemData (i), m_SelectAll);
	}
	((CMainFrame*)AfxGetMainWnd ())->GetChartView ()->ReInit ();		
}

void CViewerMenuView::OnCheckSelected(BOOL Selection)
{
	POSITION pos = m_CategoryList.GetFirstSelectedItemPosition ();
	while (pos)
	{
		int Index = m_CategoryList.GetNextSelectedItem (pos);
		m_CategoryList.SetCheck (Index, Selection);
		GetDocument()->SetCategory(m_CategoryList.GetItemData (Index), Selection);
	}
}
