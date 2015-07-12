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

	// 初始化 List 窗口  添加显示数据
	LoadControl();
		
}

void CRightView::LoadControl()
{
	// 获取当前屏幕分辨率  -- 但不包括状态栏大小
	CRect m_wRect;
	GetWindowRect(&m_wRect);
	int screenheight = m_wRect.Height();
	int screenwidth = m_wRect.Width();
	

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
	/*dwStyle |= WS_HSCROLL;*/
	m_list.SetExtendedStyle(dwStyle); //设置扩展风格
	m_list.SetBkColor(RGB(200, 200, 200)); //设置背景颜色
	m_list.SetTextBkColor(RGB(200, 200, 200)); //设置文本背景颜色
	m_list.SetTextColor(RGB(10, 10, 80)); //设置文本颜色
	


	//插入列的标题
	m_list.InsertColumn( 0, _T("站名"), LVCFMT_CENTER, 80 );
	m_list.InsertColumn( 1, _T("模块"), LVCFMT_CENTER, 110 );

	CString strSlotNum;
	strSlotNum.Empty();
	for (int iSlot = 0; iSlot < 16; iSlot++ )
	{
		strSlotNum.Format(_T("槽位%d"),iSlot);
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
	//	//按模块、槽位、端口号和描述信息升序排序
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
	//				moduleNum.Format(_T("模块Ⅰ"));
	//				break;
	//			case 2:
	//				moduleNum.Format(_T("模块Ⅱ"));
	//				break;
	//			case 3:
	//				moduleNum.Format(_T("模块Ⅲ"));
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