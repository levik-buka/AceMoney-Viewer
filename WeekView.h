// WeekView.h: interface for the CWeekView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WEEKVIEW_H__FD7DE3A5_9746_4AB3_859F_91359661E9C8__INCLUDED_)
#define AFX_WEEKVIEW_H__FD7DE3A5_9746_4AB3_859F_91359661E9C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GraphView.h"

#define WEEK_VIEW_COUNT 7
 
class CWeekView : public CGraphView  
{
public:
	virtual int GetWeekByDate (COleDateTime Date);
	CWeekView();
	virtual ~CWeekView();
	static void Init();
	virtual void LoadSeason (CViewerDoc* pDoc);
	virtual void PrevSeason (CViewerDoc* pDoc);
	virtual void NextSeason (CViewerDoc* pDoc);
	virtual CString GetChartDesc ();
	virtual double GetAmount (int Type, int Index);
	virtual double GetMaxAmount ();
	virtual CString GetAxelMeasure (int Index);
	virtual CString GetAxelDesc ();

protected:
	virtual CString MapIndexToDate (int Index);
	virtual int GetDayOfWeekOffset (int Year);
	virtual int MapIndexToDay (int Index);
	double Amount [2][WEEK_VIEW_COUNT];
	static double MaxAmountPerDay;
	int PartOfYear;

};

#endif // !defined(AFX_WEEKVIEW_H__FD7DE3A5_9746_4AB3_859F_91359661E9C8__INCLUDED_)
