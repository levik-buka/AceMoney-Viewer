// MonthView.h: interface for the CMonthView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONTHVIEW_H__D93B87C7_A6A4_49E8_BEE8_9DF0EBC49227__INCLUDED_)
#define AFX_MONTHVIEW_H__D93B87C7_A6A4_49E8_BEE8_9DF0EBC49227__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WeekView.h"

#define MONTH_VIEW_COUNT 6

class CMonthView : public CWeekView  
{
public:
	CMonthView();
	virtual ~CMonthView();
	static void Init();
	virtual void LoadSeason (CViewerDoc* pDoc);
	virtual void PrevSeason (CViewerDoc* pDoc);
	virtual void NextSeason (CViewerDoc* pDoc);
	virtual CString GetChartDesc ();
	virtual CString GetAxelMeasure (int Index);
	virtual CString GetAxelDesc ();
	virtual double GetMaxAmount ();

protected:
	virtual int GetWeekCount ();
	virtual CString MapIndexToStartDate (int Index);
	virtual CString MapIndexToEndDate (int Index);
	virtual int MapIndexToWeek (int Index); 
	static double MaxAmountPerWeek;

};

#endif // !defined(AFX_MONTHVIEW_H__D93B87C7_A6A4_49E8_BEE8_9DF0EBC49227__INCLUDED_)
