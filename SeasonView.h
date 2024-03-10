// SeasonView.h: interface for the CSeasonView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEASONVIEW_H__DF818562_6264_4A33_85E6_C87E6712477D__INCLUDED_)
#define AFX_SEASONVIEW_H__DF818562_6264_4A33_85E6_C87E6712477D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "QuartalView.h"

class CSeasonView : public CQuartalView  
{
public:
	CSeasonView();
	virtual ~CSeasonView();
	virtual CString GetChartDesc ();
	virtual void LoadSeason (CViewerDoc* pDoc);

protected:
	virtual int MapIndexToMonth (int Index);
};

#endif // !defined(AFX_SEASONVIEW_H__DF818562_6264_4A33_85E6_C87E6712477D__INCLUDED_)
