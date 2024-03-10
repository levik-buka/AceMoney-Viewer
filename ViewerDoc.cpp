// ViewerDoc.cpp : implementation of the CViewerDoc class
//

#include "stdafx.h"
#include "AceMoney Viewer.h"
#include "mainfrm.h"
#include "ViewerDoc.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewerDoc

IMPLEMENT_DYNCREATE(CViewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CViewerDoc, CDocument)
	//{{AFX_MSG_MAP(CViewerDoc)
	ON_COMMAND(ID_NEXT_PERIOD, OnNextPeriod)
	ON_COMMAND(ID_NEXT_VIEW, OnNextView)
	ON_COMMAND(ID_PREV_PERIOD, OnPrevPeriod)
	ON_COMMAND(ID_PREV_VIEW, OnPrevView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewerDoc construction/destruction

CViewerDoc::CViewerDoc()
{
	// TODO: add one-time construction code here
   CoInitialize(NULL);

}

CViewerDoc::~CViewerDoc()
{
	Categories.clear ();
	if (XMLDom) XMLDom.Release();
	CoUninitialize();
}


/////////////////////////////////////////////////////////////////////////////
// CViewerDoc serialization

void CViewerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CViewerDoc diagnostics

#ifdef _DEBUG
void CViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewerDoc commands

bool CViewerDoc::LoadAceMoneyFile(CString File)
{
	HRESULT hr;

	hr= XMLDom.CreateInstance(__uuidof(DOMDocument30));
	if (FAILED(hr)) 
	{
		AfxMessageBox ("Failed to instantiate an XML DOM.\n");
		return false;
	}

	XMLDom->async = VARIANT_FALSE; // default - true,

	if(XMLDom->load((LPCSTR)File)!=VARIANT_TRUE)
	{
		AfxMessageBox ("Failed to load:\n" + XMLDom->parseError->Getreason());
		return false;
	}

	InitCategories ();
	return true;
}


BOOL CViewerDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	if (XMLDom) XMLDom.Release ();
	
	return TRUE;
}

CString CViewerDoc::GetCategoryById(long ID)
{
	CString Cat;

	if (XMLDom)
	{
		CString Filter;
		Filter.Format ("/AceMoneyDocument/CategoryCollection/Category[@ID = %ld]", ID);
		IXMLDOMNodePtr pNode = XMLDom->selectSingleNode((LPCSTR)Filter);
		
		if (pNode)
		{
			IXMLDOMNamedNodeMapPtr AttrMap = pNode->attributes;
			if (AttrMap)
			{
				IXMLDOMNodePtr AttrValue = AttrMap->getNamedItem ("Name");
				if (AttrValue)
				{
					Cat += AttrValue->text;
					AttrValue.Release ();
				}
				AttrMap.Release ();
			}
			pNode.Release ();
		}
	}
	return Cat;
}



long CViewerDoc::GetCategoryCount()
{
	long Count = 0;
	if (XMLDom)
	{
		// All categories: /catalog/cd[not(@country=preceding-sibling::cd/@country)]/@country
		IXMLDOMNodeListPtr Nodes = XMLDom->selectNodes ("/AceMoneyDocument/CategoryCollection/Category/@ID");
		if (Nodes)
		{
			IXMLDOMNodePtr pNode = Nodes->Getitem (Nodes->length - 1);
			if (pNode)
			{
				Count = atol (pNode->text);
				pNode.Release ();
			}
			Nodes.Release ();
		}
	}
	return Count;
}


double CViewerDoc::GetAmountPerDay(CString Date, int Type)
{
	double Amount = 0;

	if (XMLDom)
	{
		CString Filter; 
		Filter.Format ("/AceMoneyDocument/TransactionCollection/Transaction[@Date = '%s' and @Type = %d]", 
			Date, Type);
		//AfxMessageBox (Filter);
		IXMLDOMNodeListPtr pNodeList = XMLDom->selectNodes((LPCSTR)Filter);
		
		if (pNodeList)
		{
			for (long i = 0; i < pNodeList->length; i++)
			{
				IXMLDOMNodePtr pNode = pNodeList->Getitem (i);
				if (pNode)
				{
					IXMLDOMNamedNodeMapPtr pAttrs = pNode->Getattributes ();
					if (pAttrs)
					{
						IXMLDOMNodePtr pAmount	= pAttrs->getNamedItem ("Amount");
						IXMLDOMNodePtr pCatID	= pAttrs->getNamedItem ("CategoryID");

						if (GetCategory (atol(pCatID->text)))
						{
							Amount += atof (pAmount->text);
						}

						pAmount.Release ();
						pCatID.Release ();
						pAttrs.Release ();
					}
					pNode.Release ();
				}
			}
			pNodeList.Release ();
		}
	}
	return Amount;
}

double CViewerDoc::GetAmountBetweenDates (CString StartDate, CString EndDate, int Type)
{
	double Amount = 0;

	if (XMLDom)
	{
		CString Filter; 
		Filter.Format ("/AceMoneyDocument/TransactionCollection/Transaction[@Date >= '%s' and @Date <= '%s' and @Type = %d]", 
			StartDate, EndDate, Type);
		//AfxMessageBox (Filter);
		IXMLDOMNodeListPtr pNodeList = XMLDom->selectNodes((LPCSTR)Filter);
		
		if (pNodeList)
		{
			for (long i = 0; i < pNodeList->length; i++)
			{
				IXMLDOMNodePtr pNode = pNodeList->Getitem (i);
				if (pNode)
				{
					IXMLDOMNamedNodeMapPtr pAttrs = pNode->Getattributes ();
					if (pAttrs)
					{
						IXMLDOMNodePtr pAmount	= pAttrs->getNamedItem ("Amount");
						IXMLDOMNodePtr pCatID	= pAttrs->getNamedItem ("CategoryID");

						if (GetCategory (atol(pCatID->text)))
						{
							Amount += atof (pAmount->text);
						}

						pAmount.Release ();
						pCatID.Release ();
						pAttrs.Release ();
					}
					pNode.Release ();
				}
			}
			pNodeList.Release ();
		}
	}
	return Amount;
}


double CViewerDoc::GetAmountPerMonth(int Year, int Month, int Type)
{
	CString StartDate, EndDate;
	StartDate.Format ("%d-%.2d-01", Year, Month);
	EndDate.Format ("%d-%.2d-31", Year, Month);
	return GetAmountBetweenDates (StartDate, EndDate, Type);
}

double CViewerDoc::GetAmountPerYear(int Year, int Type)
{
	CString StartDate, EndDate;
	StartDate.Format ("%d-01-01", Year);
	EndDate.Format ("%d-12-31", Year);
	return GetAmountBetweenDates (StartDate, EndDate, Type);
}

void CViewerDoc::OnNextPeriod() 
{
	// TODO: Add your command handler code here
	((CMainFrame*)AfxGetMainWnd ())->GetChartView ()->SendMessage (WM_COMMAND, ID_NEXT_PERIOD);
}

void CViewerDoc::OnNextView() 
{
	// TODO: Add your command handler code here
	((CMainFrame*)AfxGetMainWnd ())->GetMenuView ()->SendMessage (WM_COMMAND, ID_NEXT_VIEW);
}

void CViewerDoc::OnPrevPeriod() 
{
	// TODO: Add your command handler code here
	((CMainFrame*)AfxGetMainWnd ())->GetChartView ()->SendMessage (WM_COMMAND, ID_PREV_PERIOD);
}

void CViewerDoc::OnPrevView() 
{
	// TODO: Add your command handler code here
	((CMainFrame*)AfxGetMainWnd ())->GetMenuView ()->SendMessage (WM_COMMAND, ID_PREV_VIEW);
}

void CViewerDoc::InitCategories()
{
	Categories.clear ();

	long catCount = GetCategoryCount ();

	for (long i = 1; i <= catCount; i++)
	{
		CString catName = GetCategoryById(i);
		if (!catName.IsEmpty ())
		{
			SetCategory (i, TRUE);
		}
	}

}

void CViewerDoc::SetCategory(long CatID, BOOL Use)
{
	Categories [CatID] = !Use;	// Because by default categories are FALSE
}

BOOL CViewerDoc::GetCategory(long CatID)
{
	return !Categories[CatID];	// Because by default categories are FALSE
}
