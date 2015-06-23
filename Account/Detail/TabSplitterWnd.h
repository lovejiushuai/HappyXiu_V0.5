#pragma once


// CTabSplitterWnd

class  CTabSplitterWnd : public CSplitterWnd 
{
	DECLARE_DYNAMIC(CTabSplitterWnd)
public:
	CTabSplitterWnd();

	// for registry
	void SetSection(LPCTSTR szSection);
// for workspace
	void SetPropertyItem(CRuntimeClass *pPropertyItemClass);
	void SetSize(int nCur,int nMin);
	void Apply();
	BOOL IsEmpty();
	void SetBackground(COLORREF color){m_crBg = color;}
	virtual void SaveSize();	
	virtual CWnd *GetActiveWnd();
public:
// Overrides	
	virtual void Serialize(CArchive& ar);
	virtual BOOL CreateView( int row, int col, CRuntimeClass* pViewClass, SIZE sizeInit, CCreateContext* pContext );
	virtual void ActivateNext(BOOL bPrev);
	virtual void OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect);
protected:
	virtual void StopTracking(BOOL bAccept);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
// Generated message map functions
protected:
	//{{AFX_MSG(CTabSplitterWnd)
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnPaint();
	//}}AFX_MSG
	LRESULT OnAppSplitterMouseWheel(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
protected:
	CString m_strSection;
	int m_nCurRow;
	int m_nCurCol;
	int m_cxCur;
	int m_cyCur;
	int m_cxMin;
	int m_cyMin;
	COLORREF m_crBg;
private:
	static LPCTSTR szSplitterSection;
	static LPCTSTR szPaneWidthCurrent;
	static LPCTSTR szPaneWidthMinimum;
	static LPCTSTR szPaneHeightCurrent;
	static LPCTSTR szPaneHeightMinimum;
};


