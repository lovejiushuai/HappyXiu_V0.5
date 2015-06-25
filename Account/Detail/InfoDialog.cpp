// InfoDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Detail.h"
#include "InfoDialog.h"
#include "afxdialogex.h"


// CInfoDialog dialog

IMPLEMENT_DYNAMIC(CInfoDialog, CDialog)

CInfoDialog::CInfoDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CInfoDialog::IDD, pParent)
{	
	dataID.Empty();
	moduleNum.Empty();
	slotNum.Empty();
	boardName.Empty();
	portNum.Empty();
	timeSlot.Empty();
	deviceNum.Empty();	
	portType.Empty();	
	info.Empty();
	m_containValue = 0;
}

CInfoDialog::~CInfoDialog()
{
}

void CInfoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);	
}


BEGIN_MESSAGE_MAP(CInfoDialog, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	ON_BN_CLICKED( IDC_BUTTON_ADD, OnAddData)
	ON_BN_CLICKED( IDC_BUTTON_MODIFY, OnModifyData)
	ON_BN_CLICKED( IDC_BUTTON_DELETE, OnDeleteData)
	ON_BN_CLICKED( IDC_BUTTON_CLEAR, OnClearData)
	ON_MESSAGE(WM_UPDATALIST, UpdataList)
END_MESSAGE_MAP()


// CInfoDialog message handlers


BOOL CInfoDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	LoadControl();
	AddToGrid();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CInfoDialog::LoadControl()
{
	// 获取当前屏幕分辨率  -- 但不包括状态栏大小
	int screenwidth=GetSystemMetrics(SM_CXFULLSCREEN);
	int screenheight=GetSystemMetrics(SM_CYFULLSCREEN);

	CRect m_rcPanel;
	//设置当前窗口大小  与 当前屏幕分辨率 一致
	m_rcPanel.SetRect(0,0,screenwidth,screenheight);
	MoveWindow(&m_rcPanel);


	// 根据屏幕分辨率 & 窗口大小设置 List 大小
	CWnd *pwnd;
	CRect rect;

	pwnd=(CWnd *)GetDlgItem(IDC_LIST);
	if(pwnd==NULL)
	{
		pwnd = NULL;
	}
	else
	{
		pwnd->GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect.right= 0.99* screenwidth;
		rect.bottom=300;
		pwnd->MoveWindow(&rect,TRUE);
		pwnd = NULL;
	}

	
	m_modNum.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL, CRect(0.1 * screenwidth, 0.7 * screenheight, 0.2* screenwidth, 0.75 * screenheight), this, IDC_MODNUM);
	m_slotNum.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.35 * screenwidth, 0.7 * screenheight, 0.45* screenwidth, 0.75 * screenheight), this, IDC_BNAME);
	m_boardName.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.6 * screenwidth, 0.7 * screenheight, 0.7* screenwidth, 0.75 * screenheight), this, IDC_BNAME);
	m_portNum.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.85 * screenwidth, 0.7 * screenheight, 0.95* screenwidth, 0.75 * screenheight), this, IDC_PORTNUM);
	m_timeSlot.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.1 * screenwidth, 0.78 * screenheight, 0.2* screenwidth, 0.83 * screenheight), this, IDC_TIMESLOT);
	m_devNum.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(0.35 * screenwidth, 0.78 * screenheight, 0.45* screenwidth, 0.83 * screenheight), this, IDC_DEVICENUM);
	m_portType.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL, CRect(0.6 * screenwidth, 0.78 * screenheight, 0.7* screenwidth, 0.83 * screenheight), this, IDC_PORTTYPE);
	m_info.Create(/*ES_MULTILINE |*/ WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL, CRect(0.85 * screenwidth, 0.78 * screenheight, 0.95* screenwidth, 0.83 * screenheight), this, IDC_INFO);

	// 创建四个按键
	m_addButton.Create( _T("添加"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 0.07 * screenwidth, 0.85 * screenheight, 0.22* screenwidth, 0.95 * screenheight), this, IDC_BUTTON_ADD);
	m_modifyButton.Create(_T("修改"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 0.32 * screenwidth, 0.85 * screenheight, 0.47 * screenwidth, 0.95 * screenheight), this, IDC_BUTTON_MODIFY);
	m_deleteButton.Create(_T("删除"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 0.57 * screenwidth, 0.85 * screenheight, 0.75 * screenwidth, 0.95 * screenheight), this, IDC_BUTTON_DELETE);
	m_clearButton.Create(_T("清除"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect( 0.82 * screenwidth, 0.85 * screenheight, 0.97 * screenwidth, 0.95 * screenheight), this, IDC_BUTTON_CLEAR);

	m_addButton.EnableWindow(TRUE);
	m_deleteButton.EnableWindow(TRUE);
	m_modifyButton.EnableWindow(TRUE);
	m_clearButton.EnableWindow(TRUE);

}

void CInfoDialog::OnInitADOConn()
{
	//if(!AfxOleInit())//这就是初始化COM库
	//{
	//	AfxMessageBox(_T("KE初始化出错!"));
	//}

	//CoInitialize(NULL);
	//HRESULT hr;
	//try                            //连接数据库
	//{
	//	hr = m_pConnection.CreateInstance(__uuidof(Connection)/*"ADODB.Connection"*/);
	//	if(SUCCEEDED(hr))
	//	{
	//		m_pConnection->ConnectionTimeout = 10;	//连接超时
	//		m_pConnection->CursorLocation = adUseClient;//作用于记录集指针，非常重要!!!
	//		m_pConnection->ConnectionString = "File Name=happyXiu.udl";
	//		m_pConnection->Open("","","",-1);
	//	}
	//}
	//catch(_com_error e)
	//{
	//	CString str;
	//	str.Format(_T("连接数据库失败:%s"),e.ErrorMessage());
	//	::MessageBox(NULL,str,_T("提示信息"),NULL);
	//	//return false;
	//}
}

void CInfoDialog::ExitConnect()
{
	//关闭记录集和连接

	/*if(m_pRecordset!=NULL)
		m_pRecordset->Close();

	if(m_pConnection!=NULL)
	m_pConnection->Close();*/
	//CoUninitialize();	//退出com库
}

void CInfoDialog::AddToGrid()
{
	//连接数据库
	/*OnInitADOConn();*/

	// 获取屏幕宽度
	int screenwidth=GetSystemMetrics(SM_CXFULLSCREEN);

	//创建 列表 表头 每列名字 及 按照 屏幕分辨率设置大小
	m_list.InsertColumn(0,_T("编号"),LVCFMT_LEFT,( 0.06 * screenwidth), 0);
	m_list.InsertColumn(1,_T("模块"),LVCFMT_LEFT,( 0.09 * screenwidth),1);
	m_list.InsertColumn(2,_T("槽位"),LVCFMT_LEFT,( 0.06 * screenwidth),2);
	m_list.InsertColumn(3,_T("板名"),LVCFMT_LEFT,( 0.13 * screenwidth),3);
	m_list.InsertColumn(4,_T("端口号"),LVCFMT_LEFT,( 0.06 * screenwidth),4);
	m_list.InsertColumn(5,_T("使用时隙号"),LVCFMT_LEFT,( 0.1 * screenwidth),5);
	m_list.InsertColumn(6,_T("设备号"),LVCFMT_LEFT,( 0.12 * screenwidth),6);
	m_list.InsertColumn(7,_T("端口类型"),LVCFMT_LEFT,( 0.12 * screenwidth),7);
	m_list.InsertColumn(8,_T("描述"),LVCFMT_LEFT,( 0.23 * screenwidth),8);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	CString sql;
	
	m_containValue=0;
	int index = 0;
	int maxDataID = 0;
	try
	{
		//按模块、槽位、端口号和描述信息升序排序
		sql.Format(_T("select * from main order by main.moduleNum,main.slotNum,main.portNum,main.info asc"));
		theApp.m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
		_variant_t var;
		while(!theApp.m_pRecordset->adoEOF)
		{
			dataID.Empty();
			moduleNum.Empty();
			slotNum.Empty();
			boardName.Empty();
			portNum.Empty();
			timeSlot.Empty();
			deviceNum.Empty();			
			portType.Empty();
			info.Empty();			

			var = theApp.m_pRecordset->GetCollect("dataID");
			if(var.vt != VT_NULL)
			{
				dataID = (char*)(_bstr_t)var;
				m_list.InsertItem(index,dataID);

			}
			else
			{
				m_list.InsertItem(index,dataID);
			}


			maxDataID = _ttoi(dataID);
			if (m_containValue < maxDataID)
			{
				m_containValue = maxDataID;
			}

			var = theApp.m_pRecordset->GetCollect("moduleNum");
			if(var.vt != VT_NULL)
			{
				moduleNum = (char*)(_bstr_t)var;
				m_list.SetItemText(index,1,moduleNum);

			}
			else
			{
				m_list.SetItemText(index,1,moduleNum);
			}

			var =theApp. m_pRecordset->GetCollect("slotNum");			
			if(var.vt != VT_NULL)
			{				
				slotNum = (char*)(_bstr_t)var;
				m_list.SetItemText(index,2,slotNum);

			}
			else
			{
				m_list.SetItemText(index,4,portNum);
			}
			
			var = theApp.m_pRecordset->GetCollect("boardName");			
			if(var.vt != VT_NULL)
			{				
				boardName = (char*)(_bstr_t)var;
				m_list.SetItemText(index,3,boardName);

			}
			else
			{
				m_list.SetItemText(index,3,boardName);
			}

			var = theApp.m_pRecordset->GetCollect("portNum");			
			if(var.vt != VT_NULL)
			{				
				portNum = (char*)(_bstr_t)var;
				m_list.SetItemText(index,4,portNum);
				
			}
			else
			{
				m_list.SetItemText(index,4,portNum);
			}

			var= theApp.m_pRecordset->GetCollect("timeSlot");
			if(var.vt != VT_NULL)
			{				
				timeSlot = (char*)(_bstr_t)var;
				m_list.SetItemText(index,5,timeSlot);

			}
			else
			{
				m_list.SetItemText(index,5,timeSlot);
			}

			var= theApp.m_pRecordset->GetCollect("deviceNum");
			if(var.vt != VT_NULL)
			{
				deviceNum = (char*)(_bstr_t)var;
				m_list.SetItemText(index,6,deviceNum);

			}
			else
			{
				m_list.SetItemText(index,6,timeSlot);
			}

			var= theApp.m_pRecordset->GetCollect("portType");
			if(var.vt != VT_NULL)
			{				
				portType = (char*)(_bstr_t)var;
				m_list.SetItemText(index,7,portType);

			}
			else
			{
				m_list.SetItemText(index,7,portType);
			}

			var= theApp.m_pRecordset->GetCollect("info");
			if(var.vt != VT_NULL)
			{				
				info = (char*)(_bstr_t)var;
				m_list.SetItemText(index,8,info);

			}
			else
			{
				m_list.SetItemText(index,8,info);
			}
							
			
			theApp.m_pRecordset->MoveNext();
			index ++;			
		}
	}
	catch(_com_error &e)
	{
		MessageBox(e.Description());
	}
	//断开数据库连接
	/*ExitConnect();
	CoUninitialize();*/	//退出com库

}

void CInfoDialog::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnCancel();
	//断开数据库连接
	ExitConnect();
}

void CInfoDialog::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int mark = m_list.GetSelectionMark();
	if(mark<0) 
		return;
	
	dataID = m_list.GetItemText(mark,0);

	moduleNum = m_list.GetItemText(mark,1);
	m_modNum.SetWindowText(moduleNum);

	slotNum = m_list.GetItemText(mark,2);
	m_slotNum.SetWindowText(slotNum);

	boardName = m_list.GetItemText(mark,3);
	m_boardName.SetWindowText(boardName);

	portNum = m_list.GetItemText(mark,4);
	m_portNum.SetWindowText(portNum);

	timeSlot = m_list.GetItemText(mark,5);
	m_timeSlot.SetWindowText(timeSlot);

	deviceNum = m_list.GetItemText(mark,6);
	m_devNum.SetWindowText(deviceNum);

	portType = m_list.GetItemText(mark,7);
	m_portType.SetWindowText(portType);

	info = m_list.GetItemText(mark,8);
	m_info.SetWindowText(info);

	//将数据在屏幕中对应控件中显示出来
	UpdateData(false);


	*pResult = 0;
}

void CInfoDialog::OnAddData()
{	
	//用于将屏幕上控件中的数据交换到变量中
	UpdateData(TRUE);


	getEditText();
	if(moduleNum.IsEmpty() || slotNum.IsEmpty() || boardName.IsEmpty() || info.IsEmpty())
	{
		AfxMessageBox(_T("请把确认填写信息整!"),MB_ICONEXCLAMATION);
		return;
	}	


	dataID.Format(_T("%d"), m_containValue + 1);

	CString sql,number;	
	try
	{
		//sql.Format("insert into students(stuID,stuName,stuSex,teaID,comeFrom,comeYear,comeMonth,stuYear,stuMonth) \
		//	values(%s,'%s','%s',%s,%s,%s,%s,%s,%s)",m_strNumber,m_strName,m_strSex,m_strTeacher,m_comeYear,m_comeMonth,\
		//	m_stuYear,m_stuMonth);
		/*sql.Format(_T("insert into main(dataID,moduleNum,slotNum,boardName,portNum,timeSlot,deviceNum,portType,info)values(%s,%s,%s,%s,%s,%s,%s,%s,%s)"),+ m_containValue +",'"+moduleNum+"','"+slotNum+"',"+boardName+",'"+portNum+"',"+timeSlot+",\
																																																												  "+deviceNum+","+portType+","+info+"')");*/
		sql.Format(_T("insert into main(dataID,moduleNum,slotNum,boardName,portNum,timeSlot,deviceNum,portType,info)values('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')"), dataID, moduleNum, slotNum, boardName, portNum, timeSlot, deviceNum, portType, info);
		theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
		MessageBox(_T("录入成功."),_T("提示"));

		//按模块、槽位、端口号和描述信息升序排序
		sql.Format(_T("select * from main order by main.moduleNum,main.slotNum,main.portNum,main.info asc"));
		theApp.m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
		DisplayInfo();
	}
	catch(_com_error &e)
	{
		MessageBox(e.Description());
	}
}

void CInfoDialog::OnModifyData()
{	
	//用于将屏幕上控件中的数据交换到变量中
	UpdateData(TRUE);


	getEditText();
	if(moduleNum.IsEmpty() || slotNum.IsEmpty() || boardName.IsEmpty() || info.IsEmpty())
	{
		AfxMessageBox(_T("请把确认填写信息整!"),MB_ICONEXCLAMATION);
		return;
	}	

	CString sql;
	sql.Format(_T("select * from main where dataID = %s"),dataID);
	theApp.m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
	if(theApp.m_pRecordset->adoEOF)
	{
		AfxMessageBox(_T("数据库没有你要修改的信息!"),MB_ICONEXCLAMATION);
		return;
	}


	if(AfxMessageBox(_T("确定修改?"),MB_YESNO)==IDYES)
	{
		sql.Format(_T("update main set moduleNum = '%s',slotNum = '%s',boardName = '%s',portNum = '%s',timeSlot = '%s',deviceNum = '%s',portType = '%s',info = '%s' where dataID = '%s'"), moduleNum, slotNum, boardName, portNum, timeSlot, deviceNum, portType, info, dataID);
		try
		{
			theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
			MessageBox(_T("修改成功."),_T("提示"));

		}
		catch(_com_error &e)
		{
			MessageBox(e.Description());
		}
	}
	UpdataList(0,0);
}

void CInfoDialog::OnDeleteData()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(dataID == "")
	{
		AfxMessageBox(_T("要删除的信息不能为空!"),MB_ICONEXCLAMATION);
		return;
	}
	try
	{
		CString sql;
		sql.Format(_T("select * from main where dataID = '%s'"),dataID);
		theApp.m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
		if(theApp.m_pRecordset->adoEOF)
		{
			AfxMessageBox(_T("数据库没有你要删除的信息!"),MB_ICONEXCLAMATION);
			return;
		}
		if(AfxMessageBox(_T("确定要删除此条数据?"),MB_YESNO)==IDYES)
		{
			sql.Format(_T("delete from main where dataID = '%s'"),dataID);
			theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
			MessageBox(_T("删除信息成功."));
		}
		sql.Format(_T("select * from main"));
		theApp.m_pRecordset=theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
		DisplayInfo();
	}
	catch(_com_error &e)
	{
		MessageBox(e.Description());
	}
}

void CInfoDialog::OnClearData()
{
	dataID.Empty();
	moduleNum.Empty();
	slotNum.Empty();
	boardName.Empty();
	portNum.Empty();
	timeSlot.Empty();
	deviceNum.Empty();			
	portType.Empty();
	info.Empty();

	m_modNum.SetWindowText(moduleNum);
	m_slotNum.SetWindowText(slotNum);
	m_boardName.SetWindowText(boardName);
	m_portNum.SetWindowText(portNum);
	m_timeSlot.SetWindowText(timeSlot);
	m_devNum.SetWindowText(deviceNum);
	m_portType.SetWindowText(portType);
	m_info.SetWindowText(info);
	UpdateData(FALSE);
}

void CInfoDialog::DisplayInfo()
{
	m_list.DeleteAllItems();
	
	m_containValue = 0;
	int index = 0;
	int maxDataID;
	_variant_t var;
	while(!theApp.m_pRecordset->adoEOF)
	{
		dataID.Empty();
		moduleNum.Empty();
		slotNum.Empty();
		boardName.Empty();
		portNum.Empty();
		timeSlot.Empty();
		deviceNum.Empty();			
		portType.Empty();
		info.Empty();

		var = theApp.m_pRecordset->GetCollect("dataID");
		if(var.vt != VT_NULL)
		{
			dataID = (char*)(_bstr_t)var;
			m_list.InsertItem(index,dataID);

		}
		else
		{
			m_list.InsertItem(index,dataID);
		}

		maxDataID = _ttoi(dataID);
		if (m_containValue < maxDataID)
		{
			m_containValue = maxDataID;
		}

		var = theApp.m_pRecordset->GetCollect("moduleNum");
		if(var.vt != VT_NULL)
		{
			moduleNum = (char*)(_bstr_t)var;
			m_list.SetItemText(index,1,moduleNum);

		}
		else
		{
			m_list.SetItemText(index,1,moduleNum);
		}

		var =theApp. m_pRecordset->GetCollect("slotNum");			
		if(var.vt != VT_NULL)
		{				
			slotNum = (char*)(_bstr_t)var;
			m_list.SetItemText(index,2,slotNum);

		}
		else
		{
			m_list.SetItemText(index,4,portNum);
		}

		var = theApp.m_pRecordset->GetCollect("boardName");			
		if(var.vt != VT_NULL)
		{				
			boardName = (char*)(_bstr_t)var;
			m_list.SetItemText(index,3,boardName);

		}
		else
		{
			m_list.SetItemText(index,3,boardName);
		}

		var = theApp.m_pRecordset->GetCollect("portNum");			
		if(var.vt != VT_NULL)
		{				
			portNum = (char*)(_bstr_t)var;
			m_list.SetItemText(index,4,portNum);

		}
		else
		{
			m_list.SetItemText(index,4,portNum);
		}

		var= theApp.m_pRecordset->GetCollect("timeSlot");
		if(var.vt != VT_NULL)
		{				
			timeSlot = (char*)(_bstr_t)var;
			m_list.SetItemText(index,5,timeSlot);

		}
		else
		{
			m_list.SetItemText(index,5,timeSlot);
		}

		var= theApp.m_pRecordset->GetCollect("deviceNum");
		if(var.vt != VT_NULL)
		{
			deviceNum = (char*)(_bstr_t)var;
			m_list.SetItemText(index,6,deviceNum);

		}
		else
		{
			m_list.SetItemText(index,6,timeSlot);
		}

		var= theApp.m_pRecordset->GetCollect("portType");
		if(var.vt != VT_NULL)
		{				
			portType = (char*)(_bstr_t)var;
			m_list.SetItemText(index,7,portType);

		}
		else
		{
			m_list.SetItemText(index,7,portType);
		}

		var= theApp.m_pRecordset->GetCollect("info");
		if(var.vt != VT_NULL)
		{				
			info = (char*)(_bstr_t)var;
			m_list.SetItemText(index,8,info);

		}
		else
		{
			m_list.SetItemText(index,8,info);
		}


		theApp.m_pRecordset->MoveNext();
		index ++;			
	}
}

void CInfoDialog::getEditText()
{
	m_modNum.GetWindowText(moduleNum);
	m_slotNum.GetWindowText(slotNum);
	m_boardName.GetWindowText(boardName);
	m_portNum.GetWindowText(portNum);
	m_timeSlot.GetWindowText(timeSlot);
	m_devNum.GetWindowText(deviceNum);
	m_portType.GetWindowText(portType);
	m_info.GetWindowText(info);		
}

LRESULT CInfoDialog::UpdataList(WPARAM wParam,LPARAM lParam)
{
	//按模块、槽位、端口号和描述信息升序排序
	CString sql;
	sql.Format(_T("select * from main order by main.moduleNum,main.slotNum,main.portNum,main.info asc"));
	theApp.m_pRecordset = theApp.m_pConnection->Execute((_bstr_t)sql,NULL,adCmdText);
	DisplayInfo();
	return 1L;
}