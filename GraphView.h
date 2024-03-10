// GraphView.h: interface for the CGraphView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHVIEW_H__E2F08C6F_29F6_4838_A2DB_0DD28CE3F5A8__INCLUDED_)
#define AFX_GRAPHVIEW_H__E2F08C6F_29F6_4838_A2DB_0DD28CE3F5A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "viewerdoc.h"

#define INCOMES  0
#define EXPENSES 1

class CGraphView  
{
public:
	virtual double GetMaxAmount () = 0;
	virtual double GetTotalAmount (int Type);
	virtual double GetAmount (int Type, int Index) = 0;
	virtual void LoadSeason (CViewerDoc* pDoc) = 0;
	virtual void PrevSeason (CViewerDoc* pDoc) = 0;
	virtual void NextSeason (CViewerDoc* pDoc) = 0;
	virtual CString GetChartDesc () = 0;
	virtual void Draw (CDC *pDC, int right, int bottom);
	virtual void DrawChart (CDC *pDC, int right, int bottom, int Type);
	virtual void DrawAverage (CDC *pDC, int right, int bottom, int Type);
	virtual CString GetAxelMeasure (int Index) = 0;
	virtual CString GetAxelDesc () = 0;
	virtual int GetCount() const;

	virtual void ShowAverage (int Type, BOOL Show = TRUE);
	virtual void ShowGraph (int Type, BOOL Show = TRUE);
	
	CGraphView();
	virtual ~CGraphView();

protected:
	static BOOL Avg[2];
	static BOOL Graph[2];
	int Count;
	static int Year;
};

#endif // !defined(AFX_GRAPHVIEW_H__E2F08C6F_29F6_4838_A2DB_0DD28CE3F5A8__INCLUDED_)
