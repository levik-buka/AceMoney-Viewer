// QuartalView.h: interface for the CQuartalView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUARTALVIEW_H__553B0DCD_0933_49A5_BAED_4DE9CC25530C__INCLUDED_)
#define AFX_QUARTALVIEW_H__553B0DCD_0933_49A5_BAED_4DE9CC25530C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HalfYearView.h"

class CQuartalView : public CHalfYearView  
{
public:
	CQuartalView();
	virtual ~CQuartalView();
	virtual void PrevSeason (CViewerDoc* pDoc);
	virtual void NextSeason (CViewerDoc* pDoc);
	virtual CString GetChartDesc ();

};

#endif // !defined(AFX_QUARTALVIEW_H__553B0DCD_0933_49A5_BAED_4DE9CC25530C__INCLUDED_)
