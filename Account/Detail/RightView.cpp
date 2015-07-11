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

	// ��ʼ�� List ����  �����ʾ����
	LoadControl();
		
}

void CRightView::LoadControl()
{
	// ��ȡ��ǰ��Ļ�ֱ���  -- ��������״̬����С
	CRect m_wRect;
	GetWindowRect(&m_wRect);
	int screenheight = m_wRect.Height();
	int screenwidth = m_wRect.Width();
	
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
	/*dwStyle |= WS_HSCROLL;*/
	m_list.SetExtendedStyle(dwStyle); //������չ���
	m_list.SetBkColor(RGB(200, 200, 200)); //���ñ�����ɫ
	m_list.SetTextBkColor(RGB(200, 200, 200)); //�����ı�������ɫ
	m_list.SetTextColor(RGB(10, 10, 80)); //�����ı���ɫ
	


	//�����еı���
	m_list.InsertColumn( 0, _T("վ��"), LVCFMT_CENTER, 80 );
	m_list.InsertColumn( 1, _T("ģ��"), LVCFMT_CENTER, 110 );

	CString strSlotNum;
	strSlotNum.Empty();
	for (int iSlot = 0; iSlot < 16; iSlot++ )
	{
		strSlotNum.Format(_T("��λ%d"),iSlot);
		m_list.InsertColumn( iSlot + 2 , strSlotNum, LVCFMT_CENTER, 80 );
	}
}