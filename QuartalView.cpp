// QuartalView.cpp: implementation of the CQuartalView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "acemoney viewer.h"
#include "QuartalView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQuartalView::CQuartalView()
{
	Count = 3;
}

CQuartalView::~CQuartalView()
{

}

void CQuartalView::PrevSeason (CViewerDoc* pDoc)
{
	if (PartOfYear == 0)
	{
		Year--;
		PartOfYear = 4;
	}
	PartOfYear--;
	LoadSeason (pDoc);
}

void CQuartalView::NextSeason (CViewerDoc* pDoc)
{
	PartOfYear++;
	if (PartOfYear == 4)
	{
		Year++;
		PartOfYear = 0;
	}
	LoadSeason (pDoc);
}

CString CQuartalView::GetChartDesc ()
{
	CString Desc;
	Desc.Format ("%s - %d. quartal", CYearView::GetChartDesc (), PartOfYear + 1);
	return Desc;
}
