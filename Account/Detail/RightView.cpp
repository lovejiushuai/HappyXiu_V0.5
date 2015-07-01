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

	CListCtrl& m_list = GetListCtrl();//�õ����õ�listctrl����
	LONG lStyle;
	lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);//��ȡ��ǰ���ڷ��
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //���ñ�����
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle); //���ô��ڷ��
	DWORD dwStyle = m_list.GetExtendedStyle();

	//ѡ��ĳ��ʹ���и�����ֻ�����ڱ������listctrl��
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ�����뱨�����listctrl��
	m_list.SetExtendedStyle(dwStyle); //������չ���
	m_list.SetBkColor(RGB(200, 200, 200)); //���ñ�����ɫ
	m_list.SetTextBkColor(RGB(200, 200, 200)); //�����ı�������ɫ
	m_list.SetTextColor(RGB(10, 10, 80)); //�����ı���ɫ
	//�����еı��⣬Ϊ�˼��������ֻ��������
	m_list.InsertColumn( 0, _T("ͼ��֡��"), LVCFMT_CENTER, 80 );
	m_list.InsertColumn( 1, _T("�ɼ����ж�"), LVCFMT_CENTER, 110 );
	m_list.InsertColumn( 2, _T("���ŶȽ��"), LVCFMT_CENTER, 110 );
	
}
