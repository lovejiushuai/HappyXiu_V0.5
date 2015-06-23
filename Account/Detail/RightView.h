#pragma once


// CRightView view

class CRightView : public CListView
{
	DECLARE_DYNCREATE(CRightView)

protected:
	CRightView();           // protected constructor used by dynamic creation
	virtual ~CRightView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


