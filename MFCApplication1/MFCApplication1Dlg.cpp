
// MFCApplication1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFCApplication1Dlg �Ի���



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


// CMFCApplication1Dlg ��Ϣ�������

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_ctrlComm.put_CommPort(2); m_ctrlComm1.put_CommPort(1);
	//ѡ�񴮿ں�5(�ʼǱ�û�д��ڣ��õ����⴮�ڣ�����ʹ�����vspd����)
	m_ctrlComm.put_PortOpen(TRUE); m_ctrlComm1.put_PortOpen(TRUE);
	//�򿪴���
	m_ctrlComm.put_RThreshold(2); m_ctrlComm1.put_RThreshold(2);
	//�յ������ֽ�����OnComm�¼�
	m_ctrlComm.put_InputMode(1); m_ctrlComm1.put_InputMode(1);
	//����ģʽѡΪ������
	m_ctrlComm.put_Settings(_T("9600,n,8,1")); m_ctrlComm1.put_Settings(_T("9600,n,8,1"));
	//���ô��ڲ����������ʣ�����żУ�飬λֹͣλ��λ����λ
	m_ctrlComm.put_InputMode(1); m_ctrlComm1.put_InputMode(1); // �Զ����Ʒ�ʽ��ȡ���� 
	m_ctrlComm.put_RThreshold(1); m_ctrlComm1.put_RThreshold(1); //����1��ʾÿ�����ڽ��ջ��������ж��ڻ����1���ַ�ʱ������һ���������ݵ�OnComm�¼� 
	m_ctrlComm.put_InputLen(0); m_ctrlComm1.put_InputLen(0);//���õ�ǰ���������ݳ���Ϊ0 
	m_ctrlComm.get_Input(); m_ctrlComm1.get_Input();//��Ԥ��������������������� 

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
//	// TODO: �ڴ˴������Ϣ����������
//}


void CMFCApplication1Dlg::OnComm()
{
	
		// TODO: �ڴ˴������Ϣ����������
		VARIANT variant_inp;
		COleSafeArray safearray_inp;
		LONG len, k;
		BYTE rxdata[2048]; //����BYTE���� An 8-bit integerthat is not signed.     
		CString strtemp;
		if (m_ctrlComm.get_CommEvent() == 2) //�¼�ֵΪ2��ʾ���ջ����������ַ�     
		{
			////////��������Ը����Լ���ͨ��Э����봦����� 
			variant_inp = m_ctrlComm.get_Input(); //��������  
			safearray_inp = variant_inp; //VARIANT�ͱ���ת��ΪColeSafeArray�ͱ���
			len = safearray_inp.GetOneDimSize(); //�õ���Ч���ݳ���        
			for (k = 0; k<len; k++)
				safearray_inp.GetElement(&k, rxdata + k);//ת��ΪBYTE������         
			for (k = 0; k<len; k++)                    //������ת��ΪCstring�ͱ���    
			{
				BYTE bt = *(char*)(rxdata + k);//�ַ���      
				strtemp.Format("%c", bt); //���ַ�������ʱ����strtemp���   
										  ////�˴������д��󣬿�����Ŀ����->��������->�����ｫ���ַ�������Ϊʹ�ö��ֽ��ַ�������
				m_strRXData += strtemp; //������ձ༭���Ӧ�ַ���      
			}
		}
		UpdateData(FALSE); //���±༭������ 
	
}


void CMFCApplication1Dlg::OnBnClickedButtonManualsend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);  //��ȡ�༭������
	m_ctrlComm.put_Output(COleVariant(m_strTXData)); //��������
}


void CMFCApplication1Dlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_strTXData = "";
	UpdateData(FALSE);
}


void CMFCApplication1Dlg::OnComm1()
{
	// TODO: �ڴ˴������Ϣ����������
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len, k;
	BYTE rxdata1[2048]; //����BYTE���� An 8-bit integerthat is not signed.     
	CString strtemp;
	if (m_ctrlComm1.get_CommEvent() == 2) //�¼�ֵΪ2��ʾ���ջ����������ַ�     
	{
		////////��������Ը����Լ���ͨ��Э����봦����� 
		variant_inp = m_ctrlComm1.get_Input(); //��������  
		safearray_inp = variant_inp; //VARIANT�ͱ���ת��ΪColeSafeArray�ͱ���
		len = safearray_inp.GetOneDimSize(); //�õ���Ч���ݳ���        
		for (k = 0; k<len; k++)
			safearray_inp.GetElement(&k, rxdata1 + k);//ת��ΪBYTE������         
		for (k = 0; k<len; k++)                    //������ת��ΪCstring�ͱ���    
		{
			BYTE bt = *(char*)(rxdata1 + k);//�ַ���      
			strtemp.Format("%c", bt); //���ַ�������ʱ����strtemp���   
									  ////�˴������д��󣬿�����Ŀ����->��������->�����ｫ���ַ�������Ϊʹ�ö��ֽ��ַ�������
			m_strRXData1 += strtemp; //������ձ༭���Ӧ�ַ���      
		}
	}
	UpdateData(FALSE); //���±༭������ 
}


void CMFCApplication1Dlg::OnBnClickedButtonManualsend1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);  //��ȡ�༭������
	m_ctrlComm1.put_Output(COleVariant(m_strTXData1)); //��������
}


void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
		// TODO: �ڴ���ӿؼ�֪ͨ����������
		m_strRXData1 = "";
		UpdateData(FALSE);
}
