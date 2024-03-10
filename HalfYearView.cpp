// HalfYearView.cpp: implementation of the CHalfYearView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "acemoney viewer.h"
#include "HalfYearView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHalfYearView::CHalfYearView()
{
	Count= 6;
	PartOfYear = 0;
}

CHalfYearView::~CHalfYearView()
{

}

void CHalfYearView::PrevSeason (CViewerDoc* pDoc)
{
	if (PartOfYear == 0)
	{
		Year--;
	}
	PartOfYear = !PartOfYear;
	LoadSeason (pDoc);
}

void CHalfYearView::NextSeason (CViewerDoc* pDoc)
{
	if (PartOfYear == 1)
	{
		Year++;
	}
	PartOfYear = !PartOfYear;
	LoadSeason (pDoc);
}

int CHalfYearView::MapIndexToMonth(int Index)
{
	if (Index >= 0 && Index < GetCount ())
	{
		return Index + 1 + PartOfYear * GetCount ();
	}
	return 0;
}

CString CHalfYearView::GetChartDesc ()
{
	CString Desc;
	Desc.Format ("%s - %d. half", CYearView::GetChartDesc (), PartOfYear + 1);
	return Desc;
}
