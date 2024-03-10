// SeasonView.cpp: implementation of the CSeasonView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "acemoney viewer.h"
#include "SeasonView.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSeasonView::CSeasonView()
{

}

CSeasonView::~CSeasonView()
{

}

CString CSeasonView::GetChartDesc ()
{
	CString Season;
	switch (PartOfYear)
	{
	case 0 : Season = "winter";
		break;
	case 1 : Season = "spring";
		break;
	case 2 : Season = "summer";
		break;
	case 3 : Season = "autumn";
	}

	CString Desc;
	Desc.Format ("%s - %s", CYearView::GetChartDesc (), Season);
	return Desc;
}

void CSeasonView::LoadSeason (CViewerDoc* pDoc)
{
	if (pDoc)
	{
		for (int i = 0;i < GetCount (); i++)
		{
			int Month = MapIndexToMonth (i);
			int Year = this->Year;
			if (Month == 12) Year--; // Reading prev year

			Amount [INCOMES][i] = pDoc->GetAmountPerMonth (Year, Month, INCOMES + 1);	
			Amount [EXPENSES][i] = pDoc->GetAmountPerMonth (Year, Month, EXPENSES + 1);	
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

int CSeasonView::MapIndexToMonth(int Index)
{
	if (Index + PartOfYear * GetCount () == 0)
	{
		return 12;
	}
	return CHalfYearView::MapIndexToMonth (Index) - 1;
}
