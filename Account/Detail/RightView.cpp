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

void CRightView::OnConnectSQL()
{
	//CString sql;
	//
	//m_inquerySQL.Format(_T("allCabinets"));
	//int index = 0;
	//try
	//{
	//	//��ģ�顢��λ���˿ںź�������Ϣ��������
	//	sql.Format(_T("select * from %s order by %s.cabinetName,%s.moduleNum,%s.slotNum asc"), m_inquerySQL, m_listName, m_listName, m_listName);
	//	theApp.m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
	//	_variant_t var;
	//	while(!theApp.m_pRecordset->adoEOF)
	//	{
	//		dataID.Empty();
	//		moduleNum.Empty();
	//		slotNum.Empty();
	//		idataID = 0;
	//		imoduleNum = 0;
	//		islotNum = 0;

	//		
	//		
	//		var = theApp.m_pRecordset->GetCollect("dataID");
	//		if(var.vt != VT_NULL)
	//		{				
	//			dataID = (char*)(_bstr_t)var;				
	//			m_list.InsertItem(index,dataID);
	//		}
	//		else
	//		{
	//			m_list.InsertItem(index,dataID);
	//		}


	//		var = theApp.m_pRecordset->GetCollect("moduleNum");
	//		if(var.vt != VT_NULL)
	//		{
	//			imoduleNum = var;				
	//			switch( imoduleNum )
	//			{
	//			case 1:
	//				moduleNum.Format(_T("ģ���"));
	//				break;
	//			case 2:
	//				moduleNum.Format(_T("ģ���"));
	//				break;
	//			case 3:
	//				moduleNum.Format(_T("ģ���"));
	//				break;
	//			default:
	//				moduleNum.Format(_T("other"));
	//			}
	//			/*moduleNum = (char*)(_bstr_t)var;*/
	//			m_list.SetItemText(index,1,moduleNum);

	//		}
	//		else
	//		{
	//			m_list.SetItemText(index,1,moduleNum);
	//		}

	//		var =theApp. m_pRecordset->GetCollect("slotNum");			
	//		if(var.vt != VT_NULL)
	//		{
	//			islotNum = var;
	//			/*slotNum = (char*)(_bstr_t)var;*/
	//			slotNum.Format(_T("%d"),islotNum);
	//			m_list.SetItemText(index,2,slotNum);

	//		}
	//		else
	//		{
	//			m_list.SetItemText(index,2,portNum);
	//		}

	//		var = theApp.m_pRecordset->GetCollect("boardName");			
	//		if(var.vt != VT_NULL)
	//		{				
	//			boardName = (char*)(_bstr_t)var;
	//			m_list.SetItemText(index,3,boardName);

	//		}
	//		else
	//		{
	//			m_list.SetItemText(index,3,boardName);
	//		}

	//		var = theApp.m_pRecordset->GetCollect("portNum");			
	//		if(var.vt != VT_NULL)
	//		{				
	//			portNum = (char*)(_bstr_t)var;
	//			m_list.SetItemText(index,4,portNum);
	//			
	//		}
	//		else
	//		{
	//			m_list.SetItemText(index,4,portNum);
	//		}

	//		var= theApp.m_pRecordset->GetCollect("timeSlot");
	//		if(var.vt != VT_NULL)
	//		{				
	//			timeSlot = (char*)(_bstr_t)var;
	//			m_list.SetItemText(index,5,timeSlot);

	//		}
	//		else
	//		{
	//			m_list.SetItemText(index,5,timeSlot);
	//		}

	//		var= theApp.m_pRecordset->GetCollect("deviceNum");
	//		if(var.vt != VT_NULL)
	//		{
	//			deviceNum = (char*)(_bstr_t)var;
	//			m_list.SetItemText(index,6,deviceNum);

	//		}
	//		else
	//		{
	//			m_list.SetItemText(index,6,timeSlot);
	//		}

	//		var= theApp.m_pRecordset->GetCollect("portType");
	//		if(var.vt != VT_NULL)
	//		{				
	//			portType = (char*)(_bstr_t)var;
	//			m_list.SetItemText(index,7,portType);

	//		}
	//		else
	//		{
	//			m_list.SetItemText(index,7,portType);
	//		}

	//		var= theApp.m_pRecordset->GetCollect("info");
	//		if(var.vt != VT_NULL)
	//		{				
	//			info = (char*)(_bstr_t)var;
	//			m_list.SetItemText(index,8,info);

	//		}
	//		else
	//		{
	//			m_list.SetItemText(index,8,info);
	//		}
	//						
	//		
	//		theApp.m_pRecordset->MoveNext();
	//		index ++;			
	//	}
	//}
	//catch(_com_error &e)
	//{
	//	MessageBox(e.Description());
	//}
}