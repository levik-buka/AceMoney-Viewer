// HalfYearView.h: interface for the CHalfYearView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HALFYEARVIEW_H__A7DC48E7_D3BB_41C6_84CC_3E44A1ECBC10__INCLUDED_)
#define AFX_HALFYEARVIEW_H__A7DC48E7_D3BB_41C6_84CC_3E44A1ECBC10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "YearView.h"

class CHalfYearView : public CYearView  
{
public:
	CHalfYearView();
	virtual ~CHalfYearView();
	virtual void PrevSeason (CViewerDoc* pDoc);
	virtual void NextSeason (CViewerDoc* pDoc);
	virtual CString GetChartDesc ();

protected:
	virtual int MapIndexToMonth (int Index);

protected:
	int PartOfYear;
};

#endif // !defined(AFX_HALFYEARVIEW_H__A7DC48E7_D3BB_41C6_84CC_3E44A1ECBC10__INCLUDED_)
