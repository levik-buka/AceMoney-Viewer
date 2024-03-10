// ViewerDoc.h : interface of the CViewerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEWERDOC_H__54156A47_9089_43D8_8D9F_C3EC20879752__INCLUDED_)
#define AFX_VIEWERDOC_H__54156A47_9089_43D8_8D9F_C3EC20879752__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)

#import <msxml3.dll>
using namespace MSXML2;

#include <map>

class CViewerDoc : public CDocument
{
protected: // create from serialization only
	CViewerDoc();
	DECLARE_DYNCREATE(CViewerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewerDoc)
	public:
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual BOOL GetCategory (long CatID);
	virtual void SetCategory(long CatID, BOOL Use);
	double GetAmountBetweenDates (CString StartDate, CString EndDate, int Type);
	double GetAmountPerDay (CString Date, int Type);
	double GetAmountPerMonth (int Year, int Month, int Type);
	double GetAmountPerYear (int Year, int Type);
	long GetCategoryCount ();
	CString GetCategoryById (long ID);
	bool LoadAceMoneyFile (CString File);
	virtual ~CViewerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	virtual void InitCategories();

	std::map <long, BOOL, std::less<long > > Categories;
	IXMLDOMDocumentPtr XMLDom;

	//{{AFX_MSG(CViewerDoc)
	afx_msg void OnNextPeriod();
	afx_msg void OnNextView();
	afx_msg void OnPrevPeriod();
	afx_msg void OnPrevView();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWERDOC_H__54156A47_9089_43D8_8D9F_C3EC20879752__INCLUDED_)
