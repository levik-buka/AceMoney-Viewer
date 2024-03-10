// YearView.cpp: implementation of the CYearView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "acemoney viewer.h"
#include "YearView.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

double CYearView::MaxAmountPerMonth = 0;

CYearView::CYearView()
{
	Count = YEAR_VIEW_COUNT;
}

CYearView::~CYearView()
{

}

void CYearView::LoadSeason (CViewerDoc* pDoc)
{
	if (pDoc)
	{
		for (int i = 0;i < GetCount (); i++)
		{
			Amount [INCOMES][i] = pDoc->GetAmountPerMonth (Year, MapIndexToMonth (i), INCOMES + 1);	
			Amount [EXPENSES][i] = pDoc->GetAmountPerMonth (Year, MapIndexToMonth (i), EXPENSES + 1);	
			if (fabs (Amount [INCOMES][i]) > MaxAmountPerMonth) MaxAmountPerMonth = fabs (Amount [INCOMES][i]);
			if (fabs (Amount [EXPENSES][i]) > MaxAmountPerMonth) MaxAmountPerMonth = fabs (Amount [EXPENSES][i]);
		}
	}
	else
	{
		for (int i = 0;i < GetCount (); i++)
		{
			Amount [INCOMES][i] = 0;	
			Amount [EXPENSES][i] = 0;
		}
	}
}

double CYearView::GetAmount (int Type, int Index)
{
	if (Index >= 0 && Index < GetCount () && (Type == INCOMES || Type == EXPENSES))
	{
		return Amount [Type][Index];
	}
	return 0;
}

void CYearView::PrevSeason (CViewerDoc* pDoc)
{
	Year--;
	LoadSeason (pDoc);
}

void CYearView::NextSeason (CViewerDoc* pDoc)
{
	Year++;
	LoadSeason (pDoc);
}

CString CYearView::GetChartDesc ()
{
	CString Desc;
	Desc.Format ("Year %d", Year);
	return Desc;
}

CString CYearView::GetAxelMeasure (int Index)
{
	CString Measure;

	if (Index >= 0 && Index < GetCount ())
	{
		Measure.Format ("%d", MapIndexToMonth (Index));
	}

	return Measure;
}

CString CYearView::GetAxelDesc ()
{
	return "months";
}

int CYearView::MapIndexToMonth(int Index)
{
	if (Index >= 0 && Index < GetCount ())
	{
		return Index + 1;
	}
	return 0;
}

void CYearView::Init()
{
	MaxAmountPerMonth = 0;
}

double CYearView::GetMaxAmount ()
{
	return MaxAmountPerMonth;
}

