// GraphView.cpp: implementation of the CGraphView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "acemoney viewer.h"
#include "GraphView.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int CGraphView::Year = 0;
BOOL CGraphView::Avg[2] = {TRUE, TRUE};
BOOL CGraphView::Graph[2] = {TRUE, TRUE};

CGraphView::CGraphView()
{
	if (!Year)
	{
		CTime t = CTime::GetCurrentTime ();
		Year = t.GetYear ();
	}

	Count = 0;
}

CGraphView::~CGraphView()
{

}

int CGraphView::GetCount() const
{
	return Count;
}

double CGraphView::GetTotalAmount (int Type)
{
	double Total = 0;
	for (int i = 0; i < GetCount (); i++)
	{
		Total += GetAmount (Type, i);
	}
	return Total;
}

void CGraphView::Draw(CDC *pDC, int right, int bottom)
{
	// Drawing axel
	pDC->MoveTo (20, bottom - 30);
	pDC->LineTo (right - 20, bottom - 30);

	for (int i = 0; i < GetCount (); i++)
	{
		int x = i * (right / GetCount ()) + 20;

		pDC->MoveTo (x, bottom - 32);
		pDC->LineTo (x, bottom - 27);

		pDC->TextOut (x - 5, bottom - 25, GetAxelMeasure (i));
	}

	pDC->TextOut (right - 50, bottom - 50, GetAxelDesc ());
	pDC->TextOut (20, 20, GetChartDesc ());

	if (Graph[EXPENSES])
		DrawChart (pDC, right, bottom, EXPENSES);
	if (Graph[INCOMES])
		DrawChart (pDC, right, bottom, INCOMES);

	if (Avg[EXPENSES])
		DrawAverage (pDC, right, bottom, EXPENSES);
	if (Avg[INCOMES])
		DrawAverage (pDC, right, bottom, INCOMES);
}

void CGraphView::DrawAverage(CDC *pDC, int right, int bottom, int Type)
{
 	CPen pen;
 	if (Type == INCOMES)	// Incomes
 	{
 		pen.CreatePen (PS_SOLID, 1, RGB(255,0,0) );
	}
 	else 
 	{
 		pen.CreatePen (PS_SOLID, 1, RGB(0,0,255) );
 	}
 	CPen *orgPen = pDC->SelectObject (&pen);

	if (fabs (GetTotalAmount (Type)) > 0)
 	{
 		int y = bottom - 30 - (int)(((bottom - 30 - 50) * fabs (GetTotalAmount (Type) / GetCount ())) / GetMaxAmount ());
 		pDC->MoveTo (20, y);
 		pDC->LineTo ((GetCount () - 1) * (right / GetCount ()) + 20, y);
 
 		CString TotalStr;
 		TotalStr.Format ("%.2f ", GetTotalAmount (Type) / GetCount ());
 		pDC->TextOut (20, y - 10, TotalStr);
 	}

	pDC->SelectObject (orgPen);
}

void CGraphView::DrawChart(CDC *pDC, int right, int bottom, int Type)
{
 	CPen pen;
 	if (Type == INCOMES)	// Incomes
 	{
 		pen.CreatePen (PS_SOLID, 1, RGB(255,0,0) );
	}
 	else 
 	{
 		pen.CreatePen (PS_SOLID, 1, RGB(0,0,255) );
 	}
 	CPen *orgPen = pDC->SelectObject (&pen);

 	for (int i = 0; i < GetCount (); i++)
 	{
 		int x = i * (right / GetCount ()) + 20;

		if (GetMaxAmount () > 0)
 		{
 			int y = bottom - 30 - (int)(((bottom - 30 - 50) * fabs (GetAmount (Type, i))) / GetMaxAmount ());
 			
 			if (GetAmount (Type, i) != 0)
 			{
 				CString AmountStr;
 				AmountStr.Format ("%.2f", GetAmount (Type, i));
 				pDC->TextOut (x + 5, y, AmountStr);

 				if (i > 0)
 				{
 					int xPrev = (i - 1) * (right / GetCount ()) + 20;
 					int yPrev = bottom - 30 - (int)(((bottom - 30 - 50) * fabs (GetAmount (Type, i - 1))) / GetMaxAmount ());
					
 					pDC->MoveTo (xPrev, yPrev);
 					pDC->LineTo (x, y);
				}
 			}
 			else if (i > 0 && GetAmount (Type, i - 1) != 0)
 			{
 				int xPrev = (i - 1) * (right / GetCount ()) + 20;
 				int yPrev = bottom - 30 - (int)(((bottom - 30 - 50) * fabs (GetAmount (Type, i - 1))) / GetMaxAmount ());
 				pDC->MoveTo (xPrev, yPrev);
 				pDC->LineTo (x, y);
 			}
 
 			pDC->Ellipse (x - 3, y - 3, x + 3, y + 3);
		}
 
	}

	pDC->SelectObject (orgPen);
}

/*	
	
	YearStr.Format ("%d ( %.2f euro )", Year, Diff);

*/

void CGraphView::ShowAverage (int Type, BOOL Show)
{
	if (Type >= 0 && Type <= 1)
		Avg[Type] = Show;
}

void CGraphView::ShowGraph (int Type, BOOL Show)
{
	if (Type >= 0 && Type <= 1)
		Graph[Type] = Show;
}

