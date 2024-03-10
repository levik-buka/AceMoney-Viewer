#if !defined(AFX_VIEWERCHARTVIEW_H__358F0101_A4B9_4F89_9232_787F4A8A943C__INCLUDED_)
#define AFX_VIEWERCHARTVIEW_H__358F0101_A4B9_4F89_9232_787F4A8A943C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewerChartView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewerChartView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "viewerdoc.h"
#include "GraphView.h"

class CViewerChartView : public CFormView
{
protected:
	CViewerChartView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewerChartView)
// Form Data
public:
	//{{AFX_DATA(CViewerChartView)
	enum { IDD = IDD_VIEWERCHARTVIEW_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	virtual void ShowAverage (int Type, BOOL Show = TRUE);
	virtual void ShowGraph (int Type, BOOL Show = TRUE);

// Operations
public:
	virtual void ReInit();
	virtual void SetView (CGraphView *View);
	CViewerDoc* GetDocument ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewerChartView)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewerChartView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CViewerChartView)
	afx_msg void OnNextPeriod();
	afx_msg void OnPrevPeriod();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CGraphView* View;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWERCHARTVIEW_H__358F0101_A4B9_4F89_9232_787F4A8A943C__INCLUDED_)
