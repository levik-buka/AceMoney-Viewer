// ViewerChartView.cpp : implementation file
//

#include "stdafx.h"
#include "acemoney viewer.h"
#include "ViewerChartView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewerChartView

IMPLEMENT_DYNCREATE(CViewerChartView, CFormView)

CViewerChartView::CViewerChartView()
	: CFormView(CViewerChartView::IDD)
{
	View = NULL;
	//{{AFX_DATA_INIT(CViewerChartView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CViewerChartView::~CViewerChartView()
{
}

void CViewerChartView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewerChartView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}



BEGIN_MESSAGE_MAP(CViewerChartView, CFormView)
	//{{AFX_MSG_MAP(CViewerChartView)
	ON_COMMAND(ID_NEXT_PERIOD, OnNextPeriod)
	ON_COMMAND(ID_PREV_PERIOD, OnPrevPeriod)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewerChartView diagnostics

#ifdef _DEBUG
void CViewerChartView::AssertValid() const
{
	CFormView::AssertValid();
}

void CViewerChartView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewerChartView message handlers

CViewerDoc* CViewerChartView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CViewerDoc)));
	return (CViewerDoc*)m_pDocument;
}

void CViewerChartView::OnDraw(CDC* pDC) 
{
	if (View != NULL)
	{
		RECT Rect;
		GetClientRect (&Rect);

		//CString Ikkuna;
		//Ikkuna.Format ("Left: %d, Top: %d, Right: %d, Botton: %d\n", Rect.left, Rect.top, Rect.right, Rect.bottom);
		//TRACE (Ikkuna);

		View->Draw (pDC, Rect.right, Rect.bottom);
	}
}

void CViewerChartView::OnNextPeriod() 
{
	// TODO: Add your command handler code here
	if (View)
	{
		CViewerDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		View->NextSeason (pDoc);

		Invalidate ();
		UpdateWindow ();
	}
}

void CViewerChartView::OnPrevPeriod() 
{
	// TODO: Add your command handler code here
	if (View)
	{
		CViewerDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		View->PrevSeason (pDoc);

		Invalidate ();
		UpdateWindow ();
	}
}

void CViewerChartView::SetView(CGraphView *View)
{
	if (View)
	{
		CViewerDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		this->View = View;
		this->View->LoadSeason (pDoc);

		Invalidate ();
		UpdateWindow ();
	}
}

void CViewerChartView::ReInit()
{
	if (View)
	{
		CViewerDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		View->LoadSeason (pDoc);

		Invalidate ();
		UpdateWindow ();
	}
}


void CViewerChartView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	Invalidate ();
	UpdateWindow ();
}

void CViewerChartView::ShowAverage (int Type, BOOL Show)
{
	if (View)
		View->ShowAverage (Type, Show);
}

void CViewerChartView::ShowGraph (int Type, BOOL Show)
{
	if (View)
		View->ShowGraph (Type, Show);
}

