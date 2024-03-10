#if !defined(AFX_VIEWERMENUVIEW_H__A3142059_67CA_4728_8861_919C9D2543CD__INCLUDED_)
#define AFX_VIEWERMENUVIEW_H__A3142059_67CA_4728_8861_919C9D2543CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewerMenuView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewerMenuView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "viewerdoc.h" 
#include "afxtempl.h"

class CViewerMenuView : public CFormView
{
protected:
	CViewerMenuView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewerMenuView)

// Form Data
public:
	//{{AFX_DATA(CViewerMenuView)
	enum { IDD = IDD_VIEWERMENUVIEW_FORM };
	CListCtrl	m_CategoryList;
	CComboBox	comboView;
	BOOL	m_SelectAll;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	virtual void ReInit ();
	virtual void InitCategories ();
	virtual void SetGraphView (int Index);
	CViewerDoc* GetDocument ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewerMenuView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnCheckSelected (BOOL Selection);
	virtual void ResizeCategoryList();
	virtual ~CViewerMenuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CViewerMenuView)
	afx_msg void OnSelchangeComboView();
	afx_msg void OnNextView();
	afx_msg void OnPrevView();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnItemchangedCategoryList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickCategoryList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool UserAction;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWERMENUVIEW_H__A3142059_67CA_4728_8861_919C9D2543CD__INCLUDED_)
