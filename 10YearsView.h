// 10YearsView.h: interface for the C10YearsView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_10YEARSVIEW_H__622B0639_1DB0_4F3E_8EF5_34B2DDB72278__INCLUDED_)
#define AFX_10YEARSVIEW_H__622B0639_1DB0_4F3E_8EF5_34B2DDB72278__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GraphView.h"

#define YEARS_VIEW_COUNT 10

class C10YearsView : public CGraphView  
{
public:
	static void Init ();
	C10YearsView();
	virtual ~C10YearsView();
	virtual void LoadSeason (CViewerDoc* pDoc);
	virtual void PrevSeason (CViewerDoc* pDoc);
	virtual void NextSeason (CViewerDoc* pDoc);
	virtual CString GetChartDesc ();
	virtual double GetAmount (int Type, int Index);
	virtual double GetMaxAmount ();
	virtual CString GetAxelMeasure (int Index);
	virtual CString GetAxelDesc ();

protected:
	static double MaxAmountPerYear;
	virtual int MapIndexToYear (int Index);
	double Amount [2][YEARS_VIEW_COUNT];

};

#endif // !defined(AFX_10YEARSVIEW_H__622B0639_1DB0_4F3E_8EF5_34B2DDB72278__INCLUDED_)
