// 10YearsView.cpp: implementation of the C10YearsView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "acemoney viewer.h"
#include "10YearsView.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

double C10YearsView::MaxAmountPerYear = 0;

C10YearsView::C10YearsView()
{
	Count = YEARS_VIEW_COUNT;
}

C10YearsView::~C10YearsView()
{

}

void C10YearsView::LoadSeason (CViewerDoc* pDoc)
{
	if (pDoc)
	{
		for (int i = 0;i < GetCount (); i++)
		{
			Amount [INCOMES][i] = pDoc->GetAmountPerYear (MapIndexToYear (i), INCOMES + 1);	
			Amount [EXPENSES][i] = pDoc->GetAmountPerYear (MapIndexToYear (i), EXPENSES + 1);	
			if (fabs (Amount [INCOMES][i]) > MaxAmountPerYear) MaxAmountPerYear = fabs (Amount [INCOMES][i]);
			if (fabs (Amount [EXPENSES][i]) > MaxAmountPerYear) MaxAmountPerYear = fabs (Amount [EXPENSES][i]);
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

double C10YearsView::GetAmount (int Type, int Index)
{
	if (Index >= 0 && Index < GetCount () && (Type == INCOMES || Type == EXPENSES))
	{
		return Amount [Type][Index];
	}
	return 0;
}

void C10YearsView::PrevSeason (CViewerDoc* pDoc)
{
	Year -= YEARS_VIEW_COUNT;
	LoadSeason (pDoc);
}

void C10YearsView::NextSeason (CViewerDoc* pDoc)
{
	Year += YEARS_VIEW_COUNT;
	LoadSeason (pDoc);
}

CString C10YearsView::GetChartDesc ()
{
	return "";
}

CString C10YearsView::GetAxelMeasure (int Index)
{
	CString Measure;

	if (Index >= 0 && Index < GetCount ())
	{
		Measure.Format ("%d", MapIndexToYear (Index));
	}

	return Measure;
}

CString C10YearsView::GetAxelDesc ()
{
	return "years";
}


int C10YearsView::MapIndexToYear(int Index)
{
	if (Index >= 0 && Index < GetCount ())
	{
		return Year - (Year % 10) + Index;
	}
	return 0;
}

void C10YearsView::Init()
{
	MaxAmountPerYear = 0;
}

double C10YearsView::GetMaxAmount ()
{
	return MaxAmountPerYear;
}

