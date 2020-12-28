
// CalculatorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"
#include "atlstr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support



};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



// CCalculatorDlg dialog



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
	, CalcTextFieldEdit(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, CalculatorTextField);
	DDX_Text(pDX, IDC_EDIT1, CalcTextFieldEdit);
	DDX_Control(pDX, IDC_BUTTON_ADD, buttonPlus);
	DDX_Control(pDX, IDC_BUTTON_CLEAR, buttonClear);
	DDX_Control(pDX, IDC_BUTTON_SUBSTRACT, buttonMinus);
	DDX_Control(pDX, IDC_BUTTON_MULTIPLY, buttonTimes);
	DDX_Control(pDX, IDC_BUTTON_DIVIDE, buttonDivision);
	DDX_Control(pDX, IDC_BUTTON_EQUALS, buttonEquals);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CCalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CCalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CCalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CCalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CCalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON0, &CCalculatorDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_DOT, &CCalculatorDlg::OnBnClickedButtonDot)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CCalculatorDlg::OnBnClickedButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_SUBSTRACT, &CCalculatorDlg::OnBnClickedButtonMinus)
	ON_BN_CLICKED(IDC_BUTTON_MULTIPLY, &CCalculatorDlg::OnBnClickedButtonTimes)
	ON_BN_CLICKED(IDC_BUTTON_DIVIDE, &CCalculatorDlg::OnBnClickedButtonDivision)
	ON_BN_CLICKED(IDC_BUTTON_EQUALS, &CCalculatorDlg::OnBnClickedButtonEquals)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CCalculatorDlg::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CCalculatorDlg message handlers

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	textbox = _T("");  // Делаем textbox пустым при инициализации

	//Раскрашиваем кнопки
	ColorButton(buttonClear, RGB(255, 255, 255));
	ColorButton(buttonPlus, RGB(255, 0, 0));
	ColorButton(buttonMinus, RGB(0, 255, 0));
	ColorButton(buttonTimes, RGB(0, 0, 255));
	ColorButton(buttonDivision, RGB(0, 255, 255));
	ColorButton(buttonEquals, RGB(255, 0, 255));
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalculatorDlg::ColorButton(CMFCButton& button, COLORREF color)
{
	button.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	button.SetFaceColor(color, true);
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCalculatorDlg::Create()
{
	CDialogEx::Create(IDD_CALCULATOR_DIALOG, nullptr);
		ShowWindow(SW_NORMAL);
}






/*Функции вызываемые при нажатии на числовые кнопки. Каждая вызывает NumberButtonClicked с соответствующей цифрой
	в качестве аргумента.*/

void CCalculatorDlg::OnBnClickedButton1()
{
	NumberButtonClicked(1);
}





void CCalculatorDlg::OnBnClickedButton2()
{
	NumberButtonClicked(2);
}


void CCalculatorDlg::OnBnClickedButton3()
{
	NumberButtonClicked(3);
}


void CCalculatorDlg::OnBnClickedButton4()
{
	NumberButtonClicked(4);
}


void CCalculatorDlg::OnBnClickedButton5()
{
	NumberButtonClicked(5);
}


void CCalculatorDlg::OnBnClickedButton6()
{
	NumberButtonClicked(6);
}


void CCalculatorDlg::OnBnClickedButton7()
{
	NumberButtonClicked(7);
}


void CCalculatorDlg::OnBnClickedButton8()
{
	NumberButtonClicked(8);
}


void CCalculatorDlg::OnBnClickedButton9()
{
	NumberButtonClicked(9);
}


void CCalculatorDlg::OnBnClickedButton0()
{
	NumberButtonClicked(9);
}



/*Печатает принятую цифру в текстовое поле калькулятора. Добавляет соответсвующую цифру в ввод number.*/
void CCalculatorDlg::NumberButtonClicked(int n)
{
	CheckReset();
	number.digitAdded(n);
	CString update;
	update.Format(_T("%d"), n);
	UpdateText(update);
}


//Добавляет точку в текстовое поле и вводимое число в number.
void CCalculatorDlg::OnBnClickedButtonDot()
{
	CheckReset();
	number.dot = true;
	CString update(_T("."));
	UpdateText(update);
}


/*Функции выбора операции для калькулятора. Выводит соответстующую операцию в текстовое поле,
	а также передает соответствующую операцию в number. Также сообщает number о конце ввода числа через number.FinishNumber()*/

void CCalculatorDlg::OnBnClickedButtonPlus()
{
	CheckReset();
	number.FinishNumber();
	number.action = Plus;
	CString update(_T(" + "));
	UpdateText(update);

}




void CCalculatorDlg::OnBnClickedButtonMinus()
{
	CheckReset();
	number.FinishNumber();
	number.action = Minus;
	CString update(_T(" - "));
	UpdateText(update);

}


void CCalculatorDlg::OnBnClickedButtonTimes()
{
	CheckReset();
	number.FinishNumber();
	number.action = Times;
	CString update(_T(" x "));
	UpdateText(update);

}

void CCalculatorDlg::OnBnClickedButtonDivision()
{
	CheckReset();
	number.FinishNumber();
	number.action = Division;
	CString update(_T(" / "));
	UpdateText(update);

}


/*Выводит соответстующую операцию и результат в текстовое поле ( " = результат"). Сообщает number о конце
	ввода числа через number.FinishNumber(). Подсчет результата идет через number.Calc()*/
void CCalculatorDlg::OnBnClickedButtonEquals()
{
	CheckReset();
	number.FinishNumber();
	CString r;
	r.Format(_T("%g"), number.Calc());
	CString update(_T(" = ") + r);
	nextReset = true;
	UpdateText(update);
}

//Очищает текстовое поле через ResetText() и обнуляет number через number.Reset()
void CCalculatorDlg::OnBnClickedButtonClear()
{
	number.Reset();
	ResetText();

}

//Добавляет к textbox свой аргумент и выводит textbox в текстовое поле. Вызывается при нажитии всех кнопок, кроме Clear

void CCalculatorDlg::UpdateText(CString& update)
{
	textbox = textbox + update;
	int start = 0;
	int end = CalculatorTextField.GetWindowTextLength();
	CalculatorTextField.SetSel(start, end);
	CalculatorTextField.ReplaceSel(textbox);
}

//При nextReset = true вызывает OnBnClickedButtonClear(). При nextReset = false не делает ничего.
void CCalculatorDlg::CheckReset() {
	if (nextReset) {
		OnBnClickedButtonClear();
		nextReset = !nextReset;
	}
}



/*Очищает текстовое поле калькулятора. Происходит при вызове OnBnClickedButtonClear() или любой другой кнопки,
	если nextReset = true.*/
void CCalculatorDlg::ResetText()
{
	textbox = _T("");
	int start = 0;
	int end = CalculatorTextField.GetWindowTextLength();
	CalculatorTextField.SetSel(start, end);
	CalculatorTextField.ReplaceSel(textbox);
}