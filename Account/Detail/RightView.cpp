// RightView.cpp : implementation file
//

#include "stdafx.h"
#include "Detail.h"
#include "RightView.h"


// CRightView

IMPLEMENT_DYNCREATE(CRightView, CListView)

CRightView::CRightView()
{

}

CRightView::~CRightView()
{
}

BEGIN_MESSAGE_MAP(CRightView, CListView)
END_MESSAGE_MAP()


// CRightView diagnostics

#ifdef _DEBUG
void CRightView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CRightView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRightView message handlers


void CRightView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class

	CListCtrl& m_list = GetListCtrl();//得到内置的listctrl引用
	LONG lStyle;
	lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);//获取当前窗口风格
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置报表风格
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle); //设置窗口风格
	DWORD dwStyle = m_list.GetExtendedStyle();

	//选中某行使整行高亮（只适用于报表风格的listctrl）
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与报表风格的listctrl）
	m_list.SetExtendedStyle(dwStyle); //设置扩展风格
	m_list.SetBkColor(RGB(200, 200, 200)); //设置背景颜色
	m_list.SetTextBkColor(RGB(200, 200, 200)); //设置文本背景颜色
	m_list.SetTextColor(RGB(10, 10, 80)); //设置文本颜色
	//插入列的标题，为了简单起见，我只插入三列
	m_list.InsertColumn( 0, _T("图像帧号"), LVCFMT_CENTER, 80 );
	m_list.InsertColumn( 1, _T("可见性判断"), LVCFMT_CENTER, 110 );
	m_list.InsertColumn( 2, _T("置信度结果"), LVCFMT_CENTER, 110 );
	
}
