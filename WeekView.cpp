// WeekView.cpp: implementation of the CWeekView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "acemoney viewer.h"
#include "WeekView.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

double CWeekView::MaxAmountPerDay = 0;

CWeekView::CWeekView()
{
	Count = WEEK_VIEW_COUNT;
	COleDateTime Time = COleDateTime::GetCurrentTime ();
	PartOfYear = GetWeekByDate (Time) - 1;
}

CWeekView::~CWeekView()
{

}

void CWeekView::LoadSeason (CViewerDoc* pDoc)
{
	if (pDoc)
	{
		for (int i = 0;i < GetCount (); i++)
		{
			Amount [INCOMES][i] = pDoc->GetAmountPerDay (MapIndexToDate (i), INCOMES + 1);	
			Amount [EXPENSES][i] = pDoc->GetAmountPerDay (MapIndexToDate (i), EXPENSES + 1);	
			if (fabs (Amount [INCOMES][i]) > MaxAmountPerDay) MaxAmountPerDay = fabs (Amount [INCOMES][i]);
			if (fabs (Amount [EXPENSES][i]) > MaxAmountPerDay) MaxAmountPerDay = fabs (Amount [EXPENSES][i]);
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

double CWeekView::GetAmount (int Type, int Index)
{
	if (Index >= 0 && Index < GetCount () && (Type == INCOMES || Type == EXPENSES))
	{
		return Amount [Type][Index];
	}
	return 0;
}

void CWeekView::PrevSeason (CViewerDoc* pDoc)
{
	if (PartOfYear == 0)
	{
		COleDateTime Time (Year, 1, MapIndexToDay (3), 0, 0, 0);
		COleDateTimeSpan Span (WEEK_VIEW_COUNT, 0, 0, 0);
		Time -= Span;

		PartOfYear = GetWeekByDate (Time);
		Year--;
	}
	PartOfYear--;
	LoadSeason (pDoc);
}

void CWeekView::NextSeason (CViewerDoc* pDoc)
{
	PartOfYear++;
	if ( PartOfYear > 51 && MapIndexToDay (3) < 10 )	// Thursday is in january
	{
		Year++;
		PartOfYear = 0;
	}
	LoadSeason (pDoc);
}

CString CWeekView::GetChartDesc ()
{
	COleDateTime Time (Year, 1, 1, 0, 0, 0);
	COleDateTimeSpan Span (PartOfYear * WEEK_VIEW_COUNT - GetDayOfWeekOffset (Year) + 3); // Thuesday
	Time += Span;

	CString Desc;
	Desc.Format ("%s - week %d", Time.Format ("%B, %Y"), PartOfYear + 1);
	return Desc;
}

CString CWeekView::GetAxelMeasure (int Index)
{
	CString Measure;

	if (Index >= 0 && Index < GetCount ())
	{
		Measure.Format ("%d", MapIndexToDay (Index));
	}

	return Measure;
}

CString CWeekView::GetAxelDesc ()
{
	return "days";
}

int CWeekView::MapIndexToDay(int Index)
{
	if (Index >= 0 && Index < GetCount ())
	{
		COleDateTime Time (Year, 1, 1, 0, 0, 0);
		COleDateTimeSpan Span (PartOfYear * WEEK_VIEW_COUNT - GetDayOfWeekOffset (Year) + Index, 0, 0, 0);
		Time += Span;

		return Time.GetDay ();
	}
	return 0;
}

void CWeekView::Init()
{
	MaxAmountPerDay = 0;
}

double CWeekView::GetMaxAmount ()
{
	return MaxAmountPerDay;
}


int CWeekView::GetDayOfWeekOffset(int Year)
{
	COleDateTime Time (Year, 1, 1, 0, 0, 0);
	
	int DayOfWeek = Time.GetDayOfWeek ();
	if (DayOfWeek > 5) DayOfWeek = DayOfWeek - WEEK_VIEW_COUNT - 2;
	else if (DayOfWeek > 1 && DayOfWeek <= 5) DayOfWeek -= 2;
	else if (DayOfWeek == 1) DayOfWeek = -DayOfWeek;

	return DayOfWeek;
}

CString CWeekView::MapIndexToDate(int Index)
{
	if (Index >= 0 && Index < GetCount ())
	{
		COleDateTime Time (Year, 1, 1, 0, 0, 0);
		COleDateTimeSpan Span (PartOfYear * WEEK_VIEW_COUNT - GetDayOfWeekOffset (Year) + Index, 0, 0, 0);
		Time += Span;

		return Time.Format ("%Y-%m-%d");
	}
	return "";
}

int CWeekView::GetWeekByDate(COleDateTime Date)
{
	int DayOfWeek = Date.GetDayOfWeek ();
	COleDateTimeSpan Span;
	if (DayOfWeek == 1) Span.SetDateTimeSpan (6, 0, 0, 0);	// Sunday
	else Span.SetDateTimeSpan (DayOfWeek - 2, 0, 0, 0);
	Date -= Span;

	int Week = ((Date.GetDayOfYear () + GetDayOfWeekOffset (Date.GetYear ())) / WEEK_VIEW_COUNT) + 1;
	if (Week > 52)
	{
		Span.SetDateTimeSpan (3, 0, 0, 0);
		Date += Span;
		if (Date.GetDay () < 10) Week = 1;
	}
	return Week;
}
