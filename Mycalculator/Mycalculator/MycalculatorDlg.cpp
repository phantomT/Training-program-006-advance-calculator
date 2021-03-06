
// MycalculatorDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Mycalculator.h"
#include "MycalculatorDlg.h"
#include "afxdialogex.h"
#include "math.h"
#include <stack>
#include <iostream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define m_PI 3.14159265358979323846
stack<double> OPND;
stack<char> OPTR;

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


// CMycalculatorDlg 对话框



CMycalculatorDlg::CMycalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYCALCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_angleType = 0;
	m_result = 0.0;
	m_first = 0.0;
	m_second = 0.0;
	m_operator = _T("+");
	m_coff = 1.0;
	m_display = _T("0");
	flagp = false;
	kuohaocnt = 0;
	int cnt = 0;
}

void CMycalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DISPLAY, m_display);	//绑定编辑框和结果变量，DDX机制
}

BEGIN_MESSAGE_MAP(CMycalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_JIAODU, &CMycalculatorDlg::OnBnClickedJiaodu)
	ON_BN_CLICKED(IDC_HUDU, &CMycalculatorDlg::OnBnClickedHudu)
	ON_BN_CLICKED(IDC_BUTTON1, &CMycalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMycalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CMycalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMycalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMycalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMycalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CMycalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON0, &CMycalculatorDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_SIGN, &CMycalculatorDlg::OnBnClickedButtonSign)
	ON_BN_CLICKED(IDC_BUTTON_POINT, &CMycalculatorDlg::OnBnClickedButtonPoint)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMycalculatorDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON2, &CMycalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CMycalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_MINUS, &CMycalculatorDlg::OnBnClickedButtonMinus)
	ON_BN_CLICKED(IDC_BUTTON_MUTIPLY, &CMycalculatorDlg::OnBnClickedButtonMutiply)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CMycalculatorDlg::OnBnClickedButtonDiv)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CMycalculatorDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_EQUAL, &CMycalculatorDlg::OnBnClickedButtonEqual)
	ON_BN_CLICKED(IDC_BUTTON_SQRT, &CMycalculatorDlg::OnBnClickedButtonSqrt)
	ON_BN_CLICKED(IDC_BUTTON_NJC, &CMycalculatorDlg::OnBnClickedButtonNjc)
	ON_BN_CLICKED(IDC_BUTTON_LB, &CMycalculatorDlg::OnBnClickedButtonLb)
	ON_BN_CLICKED(IDC_BUTTON_RB, &CMycalculatorDlg::OnBnClickedButtonRb)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CMycalculatorDlg::OnBnClickedButtonBack)
END_MESSAGE_MAP()


// CMycalculatorDlg 消息处理程序

BOOL CMycalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMycalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMycalculatorDlg::OnPaint()
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
HCURSOR CMycalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMycalculatorDlg::OnBnClickedJiaodu()
{
	// TODO: 在此添加控件通知处理程序代码
	m_angleType = 1;
}


void CMycalculatorDlg::OnBnClickedHudu()
{
	// TODO: 在此添加控件通知处理程序代码
	m_angleType = 0;
}

void CMycalculatorDlg::UpdateDisplay(double dck)
{
	m_display.Format(_T("%lf"), dck);
	int i = m_display.GetLength();
	while (m_display.GetAt(i - 1) == '0')
	{
		m_display.Delete(i - 1, 1);
		i--;
	}
	if(m_display.GetAt(i - 1) == '.')
	{
		m_display.Delete(i - 1, 1);
	}
	UpdateData(false);
}

void CMycalculatorDlg::Calculate(void)
{
	m_display = m_display + '#';
	m_result = EvaluateExpression(m_display);
	UpdateDisplay(m_result);
}

double CMycalculatorDlg::EvaluateExpression(CString &str)
{
	cnt = 0;
	double a, b,x,final;
	char theta;
	OPTR.push('#');
	CString ch = scan(str);
	while ((transc(ch) != '#' || OPTR.top() != '#')&&transc(ch)!='\0')
	{
		if (!In(ch))
		{
			double num1=transd(ch);
			OPND.push(num1);
			ch = scan(str);
		}
		else
		{
			char op = transc(ch);
			theta = OPTR.top();
			switch (Precede(theta, op))		
			{
			case '<':
				OPTR.push(op);
				ch = scan(str);					//probale mistake
				break;
			case '>':
				theta = OPTR.top();
				OPTR.pop();
				b = OPND.top();
				OPND.pop();
				a = OPND.top();
				OPND.pop();
				final = Operate(a, theta, b);
				OPND.push(final);
				break;
			case '=':
				x = OPTR.top();
				OPTR.pop();
				ch = scan(str);			//probale mistake
				break;
			}
		}
	}
	return OPND.top();
}

char CMycalculatorDlg::Precede(char top, char op)
{
	switch (top)
	{
	case '+':
	case '-':
	{
		if (op == '+' || op == '#'||op == '-'||op == ')')
			return '>';
		else
			return '<';
		break;
	}
	case '×':
	case '÷':
	{
		if (op == '^' ||op == '!'|| op == '(')
			return '<';
		else
			return '>';
		break;
	}
	case '^':
	case '!':
	{
		if (op == '(')
			return '<';
		else
			return '>';
		break;
	}
	case '(':
		if (op == ')')
			return '=';
		else 
			return '<';
		break;
	case ')':
		return '>';
	case '#':
	{
		if (op == '#')
			return '=';
		else
			return '<';
		break;
	}
	}
}

double CMycalculatorDlg::Operate(double a, char theta, double b)
{
	double final = 0;
	switch (theta)
	{
	case '+':
		final = a + b;
		break;
	case '-':
		final = a - b;
		break;
	case '×':
		final = a * b;
		break;
	case '÷':
		final = a / b;
		break;
	case '^':
		final = pow(a, b);
		break;
	}
	return final;
}

CString CMycalculatorDlg::scan(CString &str)
{
	int len = str.GetLength();
	int i = 0;
	CString ch;
	char c = str.GetAt(cnt);
	if (c >= '0'&& c <= '9'|| c=='.')
	{
		for (i = cnt; str.GetAt(i) >= '0'&& str.GetAt(i) <= '9' || str.GetAt(i) == '.'; i++);
		i--;
		ch = str.Mid(cnt, i-cnt+1);
		cnt = i+1;
		return ch;
	}
	else
	{
		ch = c;
		cnt++;
		return ch;
	}
}

double CMycalculatorDlg::transd(CString ch)
{
	int pst = 0;
	int len = 0;
	double num = 0;
	len = ch.GetLength();
	pst = ch.Find('.');
	int i = 0;
	if (pst != -1)
	{
		i = pst;
		for (i = pst; i > 0; i--)
		{
			num = num+(ch[pst - i] - '0')*pow(10, i-1);
		}
		i = len - pst - 1;
		for (i = 1; i <= len - pst - 1; i++)
		{
			num += (ch[pst + i] - '0')*pow(0.1, i);
		}
	}
	else
	{
		i = len;
		for (i = len; i > 0; i--)
		{
			num += (ch[len - i] - '0')*pow(10, i-1);
		}
	}
	return num;
}

char CMycalculatorDlg::transc(CString ch)
{
	char op;
	op = ch[0];
	return op;
}

int CMycalculatorDlg::In(CString ch)
{
	if (ch == '(' || ch == ')' || ch == '+' || ch == '-' || ch == '×' || ch == '÷' || ch == '^'||ch=='!')
	{
		return 1;
	}
	else
		return 0;
}

void CMycalculatorDlg::onButton(int n)
{
	CString temp;
	temp.Format(_T("%d"), n);
	if (m_display == _T("0"))
	{
		m_display = temp;
	}
	else
		m_display = m_display + temp;
	UpdateData(false);
}

void CMycalculatorDlg::OnBnClickedButton1()
{
	onButton(1);
}
void CMycalculatorDlg::OnBnClickedButton2()
{
	onButton(2);
}
void CMycalculatorDlg::OnBnClickedButton3()
{
	onButton(3);
}
void CMycalculatorDlg::OnBnClickedButton4()
{
	onButton(4);
}
void CMycalculatorDlg::OnBnClickedButton5()
{
	onButton(5);
}
void CMycalculatorDlg::OnBnClickedButton6()
{
	onButton(6);
}
void CMycalculatorDlg::OnBnClickedButton7()
{
	onButton(7);
}
void CMycalculatorDlg::OnBnClickedButton8()
{
	onButton(8);
}
void CMycalculatorDlg::OnBnClickedButton9()
{
	onButton(9);
}
void CMycalculatorDlg::OnBnClickedButton0()
{
	onButton(0);
}


void CMycalculatorDlg::OnBnClickedButtonSign()
{
	int i = m_display.GetLength();
	char c = m_display.GetAt(i - 1);
	if (m_display != _T("0"))
	{
		if ((c >= '0' && c <= '9') || c == '.')
		{
			while ((c >= '0' && c <= '9') || c == '.')
			{
				i--;
				if(i>0)
					c = m_display.GetAt(i - 1);
				if (i == 0)
				{
					m_display = (CString)_T("(-") + m_display;
					kuohaocnt++;
					break;
				}
			}
			if (i != 0)
			{
				m_display.Insert(i, '(');
				m_display.Insert(i+1, '-');
				kuohaocnt++;
			}
		}
		else
		{
			m_display = (CString)m_display + _T("(-");
			kuohaocnt++;
		}
	}
	else
	{
		m_display = _T("(-");
		kuohaocnt++;
	}
	UpdateData(false);
}


void CMycalculatorDlg::OnBnClickedButtonPoint()
{
	int i = m_display.GetLength();
	char c = m_display.GetAt(i - 1);
	if (c >= '0' && c <= '9' && !flagp)
	{
		m_display = (CString)m_display + _T(".");
		flagp = true;
	}
	UpdateData(false);
}


void CMycalculatorDlg::OnBnClickedButtonAdd()
{
	int i = m_display.GetLength();
	char c = m_display.GetAt(i - 1);
	if (m_display != _T("0"))
	{
		if ((c >= '0' && c <= '9') || c == ')')
		{
			flagp = false;
			m_display = m_display + _T("+");
			UpdateData(false);
		}
	}
}


void CMycalculatorDlg::OnBnClickedButtonMinus()
{
	int i = m_display.GetLength();
	char c = m_display.GetAt(i - 1);
	if (m_display != _T("0"))
	{
		if ((c >= '0' && c <= '9') || c == ')')
		{
			flagp = false;
			m_display = m_display + _T("-");
			UpdateData(false);
		}
	}
}


void CMycalculatorDlg::OnBnClickedButtonMutiply()
{
	int i = m_display.GetLength();
	char c = m_display.GetAt(i - 1);
	if (m_display != _T("0"))
	{
		if ((c >= '0' && c <= '9') || c == ')')
		{
			flagp = false;
			m_display = m_display + _T("×");
			UpdateData(false);
		}
	}
}


void CMycalculatorDlg::OnBnClickedButtonDiv()
{
	int i = m_display.GetLength();
	char c = m_display.GetAt(i - 1);
	if (m_display != _T("0"))
	{
		if ((c >= '0' && c <= '9') || c == ')')
		{
			flagp = false;
			m_display = m_display + _T("÷");
			UpdateData(false);
		}
	}
}


void CMycalculatorDlg::OnBnClickedButtonClear()
{
	flagp = false;
	m_result = 0.0;
	m_first = 0.0;
	m_second = 0.0;
	m_operator = "+";
	m_coff = 1.0;
	m_display = _T("0");
	kuohaocnt = 0;
	cnt = 0;
	while (! OPND.empty())
		OPND.pop();
	while (! OPTR.empty())
		OPTR.pop();
	UpdateDisplay(0);
}


void CMycalculatorDlg::OnBnClickedButtonEqual()
{
	int i = m_display.GetLength();
	char c = m_display.GetAt(i - 1);
	if (m_display != _T("0"))
	{
		for (int j = i - 1;j>=0; j--)
		{
			int m = m_display.GetLength();
			c = m_display.GetAt(m-1);
			if ( c == '+' || c == '-' || c == '×' || c == '÷')
			{
				m_display.Delete(m-1, 1);
				UpdateData(false);
			}
			else if (c == '(')
			{
				m_display.Delete(j, 1);
				kuohaocnt--;
				UpdateData(false);
			}
		}
		
	}
	if (kuohaocnt > 0)
	{
		for (int i = kuohaocnt - 1; i >= 0; i--)
		{
			m_display = m_display + _T(")");
			kuohaocnt--;
			UpdateData(false);
		}
	}
	Calculate();
	cnt = 0;
}


void CMycalculatorDlg::OnBnClickedButtonSqrt()
{
	int i = m_display.GetLength();
	char c = m_display.GetAt(i - 1);
	if (m_display != _T("0"))
	{
		if ((c >= '0' && c <= '9') || c == '.')
		{
			while ((c >= '0' && c <= '9') || c == '.')
			{
				i--;
				if (i>0)
					c = m_display.GetAt(i - 1);
				if (i == 0)
				{
					m_display = (CString)_T("(") + m_display + _T(")^0.5");
					break;
				}
			}
			if (i != 0)
			{
				m_display.Insert(i, '(');
				m_display = (CString)m_display + _T(")^0.5");
			}
		}
		else if (c == ')')
		{
			m_display = (CString)m_display + _T("^0.5");
		}
	}
	UpdateData(false);
}


void CMycalculatorDlg::sanjiaohanshu(void)
{
	switch (m_angleType)
	{
	case 0: break;
	case 1: m_second = m_second * m_PI / 180; break;
	}
}


void CMycalculatorDlg::OnBnClickedButtonNjc()
{
	if (m_second - (int)m_second > 0)
	{
		m_display = _T("请输入整数");
		UpdateData(false);
		return;
	}
	else if (m_second > 170)
	{
		m_display = _T("我看你就是刁难我胖虎");
		UpdateData(false);
		return;
	}
	else
	{
		m_second = (double)jiecheng(m_second);
		UpdateDisplay(m_second);
	}
}

double CMycalculatorDlg::jiecheng(int n)
{
	int i = 1; double s = 1;
	for (i = 1; i <= n; i++)
		s = s * i;
	return s;
}

void CMycalculatorDlg::OnBnClickedButtonLb()
{
	int i = m_display.GetLength();
	char c = m_display.GetAt(i - 1);
	if (m_display != _T("0"))
	{
		if (c == '(' || c == '+' || c == '-' || c == '×' || c == '÷')
		{
			flagp = false;
			m_display = m_display + _T("(");
			kuohaocnt++;
			UpdateData(false);
		}
		else if ((c >= '0' && c <= '9') || c == ')')
		{
			flagp = false;
			m_display = m_display + _T("×(");
			kuohaocnt++;
			UpdateData(false);
		}
	}
	else
	{
		flagp = false;
		m_display = _T("(");
		kuohaocnt++;
		UpdateData(false);
	}
}


void CMycalculatorDlg::OnBnClickedButtonRb()
{
	int i = m_display.GetLength();
	char c = m_display.GetAt(i - 1);
	if (m_display != _T("0") && kuohaocnt > 0 )
	{
		if ((c >= '0' && c <= '9') && c != '(')
		{
			flagp = false;
			m_display = m_display + _T(")");
			kuohaocnt--;
			UpdateData(false);
		}
	}
}


void CMycalculatorDlg::OnBnClickedButtonBack()
{
	int i = m_display.GetLength();
	if (m_display[i-1] == ')')
		kuohaocnt++;
	else if (m_display[i-1] == '(')
		kuohaocnt--;
	m_display.Delete(i - 1, 1);
	UpdateData(false);
}
