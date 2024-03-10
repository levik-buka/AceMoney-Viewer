// MonthView.cpp: implementation of the CMonthView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "acemoney viewer.h"
#include "MonthView.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

double CMonthView::MaxAmountPerWeek = 0;

CMonthView::CMonthView()
{
	CTime Time = CTime::GetCurrentTime ();
	PartOfYear = Time.GetMonth () - 1;
	Count = GetWeekCount ();
}

CMonthView::~CMonthView()
{

}

void CMonthView::Init()
{
	MaxAmountPerWeek = 0;
}

double CMonthView::GetMaxAmount ()
{
	return MaxAmountPerWeek;
}

void CMonthView::LoadSeason (CViewerDoc* pDoc)
{
	if (pDoc)
	{
		for (int i = 0;i < GetCount (); i++)
		{
			Amount [INCOMES][i] = pDoc->GetAmountBetweenDates (MapIndexToStartDate (i), MapIndexToEndDate (i), INCOMES + 1);	
			Amount [EXPENSES][i] = pDoc->GetAmountBetweenDates (MapIndexToStartDate (i), MapIndexToEndDate (i), EXPENSES + 1);	
			if (fabs (Amount [INCOMES][i]) > MaxAmountPerWeek) MaxAmountPerWeek = fabs (Amount [INCOMES][i]);
			if (fabs (Amount [EXPENSES][i]) > MaxAmountPerWeek) MaxAmountPerWeek = fabs (Amount [EXPENSES][i]);
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

void CMonthView::PrevSeason (CViewerDoc* pDoc)
{
	if (PartOfYear == 0)
	{
		Year--;
		PartOfYear = 12;
	}
	PartOfYear--;
	Count = GetWeekCount ();
	LoadSeason (pDoc);
}

void CMonthView::NextSeason (CViewerDoc* pDoc)
{
	PartOfYear++;
	if ( PartOfYear >= 12 )
	{
		Year++;
		PartOfYear = 0;
	}
	Count = GetWeekCount ();
	LoadSeason (pDoc);
}

CString CMonthView::GetChartDesc ()
{
	COleDateTime Time (Year, PartOfYear + 1, 1, 0, 0, 0);
	return Time.Format ("%B, %Y");
}

CString CMonthView::GetAxelMeasure (int Index)
{
	CString Measure;

	if (Index >= 0 && Index < GetCount ())
	{
		Measure.Format ("%d", MapIndexToWeek (Index));
	}

	return Measure;
}

CString CMonthView::GetAxelDesc ()
{
	return "weeks";
}

int CMonthView::MapIndexToWeek(int Index)
{
	if (Index >= 0 && Index < GetCount ())
	{
		COleDateTime StartMonth (Year, PartOfYear + 1, 1, 0, 0, 0);
		COleDateTimeSpan Span (Index * WEEK_VIEW_COUNT);
		StartMonth += Span;

		return GetWeekByDate (StartMonth);
	}
	return 0;
}


CString CMonthView::MapIndexToStartDate(int Index)
{
	if (Index >= 0 && Index < GetCount ())
	{
		COleDateTime StartMonth (Year, PartOfYear + 1, 1, 0, 0, 0);
		COleDateTimeSpan Span (Index * WEEK_VIEW_COUNT);
		StartMonth += Span;

		int DayOfWeek = StartMonth.GetDayOfWeek ();
		if (DayOfWeek == 1) DayOfWeek = -(WEEK_VIEW_COUNT - 1); 
		else DayOfWeek = -(DayOfWeek - 2);
		Span.SetDateTimeSpan (DayOfWeek, 0, 0, 0);
		StartMonth += Span;

		return StartMonth.Format("%Y-%m-%d");
	}
	return "";
}

CString CMonthView::MapIndexToEndDate(int Index)
{
	if (Index >= 0 && Index < GetCount ())
	{
		COleDateTime StartMonth (Year, PartOfYear + 1, 1, 0, 0, 0);
		COleDateTimeSpan Span (Index * WEEK_VIEW_COUNT);
		StartMonth += Span;

		int DayOfWeek = StartMonth.GetDayOfWeek ();
		if (DayOfWeek == 1) DayOfWeek = 0;
		else DayOfWeek = WEEK_VIEW_COUNT - DayOfWeek + 1;
		Span.SetDateTimeSpan (DayOfWeek, 0, 0, 0);
		StartMonth += Span;

		return StartMonth.Format("%Y-%m-%d");
	}
	return "";
}

int CMonthView::GetWeekCount()
{
	COleDateTime StartMonth (Year, PartOfYear + 1, 1, 0, 0, 0);
	int StartWeek = GetWeekByDate (StartMonth);
	
	COleDateTimeSpan Span (30, 0, 0, 0);
	COleDateTime EndMonth;
	EndMonth = StartMonth + Span;
	if (EndMonth.GetMonth () != StartMonth.GetMonth ())
	{
		Span.SetDateTimeSpan (EndMonth.GetDay (), 0, 0, 0);
		EndMonth -= Span;
	}

	int EndWeek = GetWeekByDate (EndMonth);
	
	if (StartWeek > EndWeek)
	{
		COleDateTime EndYear (Year, 12, 31, 0, 0, 0);
		int WeeksInYear = GetWeekByDate (EndYear);
		if (WeeksInYear == 1)
		{
			EndYear.SetDate (Year, 12, 31 - 7);
			WeeksInYear = GetWeekByDate (EndYear);
		}

		EndWeek += WeeksInYear;
	}
	return EndWeek - StartWeek + 1;
}

