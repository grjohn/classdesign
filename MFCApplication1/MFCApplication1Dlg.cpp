
// MFCApplication1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
	, m_strRXData(_T(""))
	, m_strTXData(_T(""))
	, m_strRXData1(_T(""))
	, m_strTXData1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
	DDX_Text(pDX, IDC_EDIT_RXDATA, m_strRXData);
	DDX_Text(pDX, IDC_EDIT_TXDATA, m_strTXData);
	DDX_Control(pDX, IDC_MSCOMM2, m_ctrlComm1);
	DDX_Text(pDX, IDC_EDIT_RXDATA1, m_strRXData1);
	DDX_Text(pDX, IDC_EDIT_TXDATA1, m_strTXData1);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_MANUALSEND, &CMFCApplication1Dlg::OnBnClickedButtonManualsend)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_MANUALSEND1, &CMFCApplication1Dlg::OnBnClickedButtonManualsend1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_ctrlComm.put_CommPort(2); m_ctrlComm1.put_CommPort(1);
	//选择串口号5(笔记本没有串口，用的虚拟串口，可以使用软件vspd创建)
	m_ctrlComm.put_PortOpen(TRUE); m_ctrlComm1.put_PortOpen(TRUE);
	//打开串口
	m_ctrlComm.put_RThreshold(2); m_ctrlComm1.put_RThreshold(2);
	//收到两个字节引发OnComm事件
	m_ctrlComm.put_InputMode(1); m_ctrlComm1.put_InputMode(1);
	//输入模式选为二进制
	m_ctrlComm.put_Settings(_T("9600,n,8,1")); m_ctrlComm1.put_Settings(_T("9600,n,8,1"));
	//设置串口参数，波特率，无奇偶校验，位停止位，位数据位
	m_ctrlComm.put_InputMode(1); m_ctrlComm1.put_InputMode(1); // 以二进制方式检取数据 
	m_ctrlComm.put_RThreshold(1); m_ctrlComm1.put_RThreshold(1); //参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件 
	m_ctrlComm.put_InputLen(0); m_ctrlComm1.put_InputLen(0);//设置当前接收区数据长度为0 
	m_ctrlComm.get_Input(); m_ctrlComm1.get_Input();//先预读缓冲区以清除残留数据 

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_EVENTSINK_MAP(CMFCApplication1Dlg, CDialogEx)
//	ON_EVENT(CMFCApplication1Dlg, IDC_MSCOMM1, 1, CMFCApplication1Dlg::OnCommMscomm1, VTS_NONE)
ON_EVENT(CMFCApplication1Dlg, IDC_MSCOMM1, 1, CMFCApplication1Dlg::OnComm, VTS_NONE)
ON_EVENT(CMFCApplication1Dlg, IDC_MSCOMM2, 1, CMFCApplication1Dlg::OnComm1, VTS_NONE)
END_EVENTSINK_MAP()


//void CMFCApplication1Dlg::OnCommMscomm1()
//{
//	// TODO: 在此处添加消息处理程序代码
//}


void CMFCApplication1Dlg::OnComm()
{
	
		// TODO: 在此处添加消息处理程序代码
		VARIANT variant_inp;
		COleSafeArray safearray_inp;
		LONG len, k;
		BYTE rxdata[2048]; //设置BYTE数组 An 8-bit integerthat is not signed.     
		CString strtemp;
		if (m_ctrlComm.get_CommEvent() == 2) //事件值为2表示接收缓冲区内有字符     
		{
			////////以下你可以根据自己的通信协议加入处理代码 
			variant_inp = m_ctrlComm.get_Input(); //读缓冲区  
			safearray_inp = variant_inp; //VARIANT型变量转换为ColeSafeArray型变量
			len = safearray_inp.GetOneDimSize(); //得到有效数据长度        
			for (k = 0; k<len; k++)
				safearray_inp.GetElement(&k, rxdata + k);//转换为BYTE型数组         
			for (k = 0; k<len; k++)                    //将数组转换为Cstring型变量    
			{
				BYTE bt = *(char*)(rxdata + k);//字符型      
				strtemp.Format("%c", bt); //将字符送入临时变量strtemp存放   
										  ////此处编译有错误，可在项目属性->配置属性->常规里将“字符集”改为使用多字节字符集即可
				m_strRXData += strtemp; //加入接收编辑框对应字符串      
			}
		}
		UpdateData(FALSE); //更新编辑框内容 
	
}


void CMFCApplication1Dlg::OnBnClickedButtonManualsend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);  //读取编辑框内容
	m_ctrlComm.put_Output(COleVariant(m_strTXData)); //发送数据
}


void CMFCApplication1Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strTXData = "";
	UpdateData(FALSE);
}


void CMFCApplication1Dlg::OnComm1()
{
	// TODO: 在此处添加消息处理程序代码
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len, k;
	BYTE rxdata1[2048]; //设置BYTE数组 An 8-bit integerthat is not signed.     
	CString strtemp;
	if (m_ctrlComm1.get_CommEvent() == 2) //事件值为2表示接收缓冲区内有字符     
	{
		////////以下你可以根据自己的通信协议加入处理代码 
		variant_inp = m_ctrlComm1.get_Input(); //读缓冲区  
		safearray_inp = variant_inp; //VARIANT型变量转换为ColeSafeArray型变量
		len = safearray_inp.GetOneDimSize(); //得到有效数据长度        
		for (k = 0; k<len; k++)
			safearray_inp.GetElement(&k, rxdata1 + k);//转换为BYTE型数组         
		for (k = 0; k<len; k++)                    //将数组转换为Cstring型变量    
		{
			BYTE bt = *(char*)(rxdata1 + k);//字符型      
			strtemp.Format("%c", bt); //将字符送入临时变量strtemp存放   
									  ////此处编译有错误，可在项目属性->配置属性->常规里将“字符集”改为使用多字节字符集即可
			m_strRXData1 += strtemp; //加入接收编辑框对应字符串      
		}
	}
	UpdateData(FALSE); //更新编辑框内容 
}


void CMFCApplication1Dlg::OnBnClickedButtonManualsend1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);  //读取编辑框内容
	m_ctrlComm1.put_Output(COleVariant(m_strTXData1)); //发送数据
}


void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	
		// TODO: 在此添加控件通知处理程序代码
		m_strRXData1 = "";
		UpdateData(FALSE);
}
