// YearView.h: interface for the CYearView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YEARVIEW_H__DF1F75BF_1DC2_4AFD_BD9E_6500047A83B8__INCLUDED_)
#define AFX_YEARVIEW_H__DF1F75BF_1DC2_4AFD_BD9E_6500047A83B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GraphView.h"

#define YEAR_VIEW_COUNT 12

class CYearView : public CGraphView  
{
public:
	static void Init();
	virtual void LoadSeason (CViewerDoc* pDoc);
	virtual void PrevSeason (CViewerDoc* pDoc);
	virtual void NextSeason (CViewerDoc* pDoc);
	virtual CString GetChartDesc ();
	virtual double GetAmount (int Type, int Index);
	virtual double GetMaxAmount ();
	virtual CString GetAxelMeasure (int Index);
	virtual CString GetAxelDesc ();
	CYearView();
	virtual ~CYearView();

protected:
	virtual int MapIndexToMonth (int Index);
	double Amount [2][YEAR_VIEW_COUNT];
	static double MaxAmountPerMonth;
};

#endif // !defined(AFX_YEARVIEW_H__DF1F75BF_1DC2_4AFD_BD9E_6500047A83B8__INCLUDED_)
