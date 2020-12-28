

#include "pch.h"
#include "framework.h"
#include "Calculator.h"
#include "MatrixDlg.h"
#include "afxdialogex.h"
#include "atlstr.h"
#include "stdlib.h"
#include "Matrix.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif





//Стандартный код диалога, сгенерированный Visual Studio

CMatrixDlg::CMatrixDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MATRIX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMatrixDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_First, FirstMatrixCtrl);
	DDX_Control(pDX, IDC_EDIT_SECOND, SecondMatrixCtrl);
	DDX_Control(pDX, IDC_EDIT_RESULT, ResultMatrixCtrl);
}

BEGIN_MESSAGE_MAP(CMatrixDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CALCULATE, &CMatrixDlg::OnBnClickedButtonCalculate)
	ON_EN_CHANGE(IDC_EDIT_First, &CMatrixDlg::OnEnChangeEditFirst)
	ON_EN_CHANGE(IDC_EDIT_SECOND, &CMatrixDlg::OnEnChangeEditSecond)
END_MESSAGE_MAP()


void CMatrixDlg::Create()
{
	CDialogEx::Create(IDD_MATRIX_DIALOG, nullptr);
	ShowWindow(SW_SHOW);
}

// CCalculatorDlg message handlers

BOOL CMatrixDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	matrixText.resize(2, _T(""));
	/*FirstMatrixX.ModifyStyle(0, ES_NUMBER);
	FirstMatrixY.ModifyStyle(0, ES_NUMBER);
	SecondMatrixX.ModifyStyle(0, ES_NUMBER);
	SecondMatrixY.ModifyStyle(0, ES_NUMBER);*/

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMatrixDlg::ColorButton(CMFCButton& button, COLORREF color)
{
	button.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	button.SetFaceColor(color, true);
}

void CMatrixDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
		CDialogEx::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMatrixDlg::OnPaint()
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
HCURSOR CMatrixDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}







//Функция, вызываемая при нажатии на кнопку "Calculate". Выводит на экран результат перемножения двух матриц
void CMatrixDlg::OnBnClickedButtonCalculate()
{
	Matrix<double> m1, m2, result; 

	

	if (CheckIfMatricesAreFull(m1, m2)) return;


	result = m1 * m2;
	PrintResultIfMultiplied(result);
}


/*Читает матрицы из полей FirstMatrixCtrl и SecondMatrixCtrl, проверяет их на полноту (кол-во столбцов в каждой строке
одинаково = полнота) и кладет в соответсвующие инпуты. Используется в OnBnClickedButtonCalculate().
Выводит true, если какая-то из матриц не является полной. Выводит false, если обе матрицы полные. */
bool CMatrixDlg::CheckIfMatricesAreFull(Matrix<double>& m1, Matrix<double>& m2)
{
	CString text;
	if (!ReadMatrix(m1, FirstMatrixCtrl)) { text += _T("Matrix 1"); }
	if (!ReadMatrix(m2, SecondMatrixCtrl)) { text += _T(" Matrix 2"); }
	if (text != _T(""))
	{
		text += _T(" is not complete. Please make sure it has a complete set of values.");
		ResultMatrixCtrl.SetWindowTextW(text);
		return true;
	}
	return false;
}

/*Проверяет, перемножилась ли матрица успешно(подходят ли размеры для умножения матриц). Используется в OnBnClickedButtonCalculate().
Выводит получившуюся матрицу в поле ResultMatrixCtrl, если матрица успешно перемножилась.
Выводит сообщение об ошибке, если в результате перемножения было обнаружено несовпадение размеров.*/
void CMatrixDlg::PrintResultIfMultiplied(Matrix<double>& result)
{
	if (result.GetSize().first < 0)
	{
		CString text = _T("Numbers of columns of the 1st matrix and rows of the 2nd matrix don't match");
		ResultMatrixCtrl.SetWindowTextW(text);
	}
	else
	{
		PrintMatrix(ResultMatrixCtrl, result);
	}
}
/*Читает матрицу из поля CEdit& и помещает ее в Matrix<double>&. Используется в CheckIfMatricesAreFull().
Возвращает true, если матрица успешно считалась.
Возвращает false, если матрица была недозаполнена.*/
bool CMatrixDlg::ReadMatrix(Matrix<double>& m, CEdit& edit)
{
	//for whatever reason text.Replace returns wierd stuff
	CString text;
	edit.GetWindowText(text);
	text.Replace(_T("\r\n"),_T(" | "));
	text += _T(" |");
	std::vector<double> values;
	values.reserve(100);
	int rows = 0;
	int j = 0;
	int curPos = 0;
	CString token = text.Tokenize(_T(" "), curPos);
	values.push_back(_wtof(token));
	while (token != _T(""))
		{
		token = text.Tokenize(_T(" "), curPos);
		if (token == _T("|"))
		{
			rows++;
		}
		else
		{
			values.push_back(_wtof(token));
		}
		j++;
	}
	values.erase(values.end() - 1);
	int columns = (j - rows) / rows;
	int error = (j - rows) % rows;
	if (error != 0) { return false; }
	m.SetValues(rows, columns, values);
	return true;
}


//Печатает матрицу m в поле edit
void CMatrixDlg::PrintMatrix(CEdit& edit, Matrix<double>& m)
{
	CString test, r;
	std::pair<int, int> size = m.GetSize();
	for (int i = 0; i < size.first; i++)
	{
		for (int k = 0; k < size.second; k++)
		{
			r.Format(_T(" %g"), m[{i, k}]);
			test += r;
		}
		test += _T("\r\n");
	}
	edit.SetWindowTextW(test);
}


//Вывод

/*Функция, вызываемая при вводе в поле первой матрицы. Не позволяет вводить никакие
символы, кроме цифр, точки, пробела и перехода на следующую строку*/
void CMatrixDlg::OnEnChangeEditFirst()
{
	CheckDouble(FirstMatrixCtrl, 0);
}

/*Функция, вызываемая при вводе в поле второй матрицы. Не позволяет вводить никакие
символы, кроме цифр, точки, пробела и перехода на следующую строку*/
void CMatrixDlg::OnEnChangeEditSecond()
{
	CheckDouble(SecondMatrixCtrl, 1);
}


/*Функция, вызываемая OnEnChangeEditFirst() и OnEnChangeEditSecond(). Не позволяет вводить никакие символы,
кроме цифр, точки, пробела и \r\n, в поле которое получает. matrixText используется как буфер и необходим для работы функции.
Принимаемый функцией int - это порядковый номер буфера для поля. Для FirstMatrixCtrl int = 0, для SecondMatrixCtrl int = 1*/
void CMatrixDlg::CheckDouble(CEdit& edit, int n)
{
	CString value;

	edit.GetWindowText(value);   //m_ValueEditBox is a variable for EditControl


										 //Cursor position in Edit Control
	int lastSel = edit.GetSel();

    if (ValidateDoubleString(value))
	{
		matrixText[n] = value;   //m_ValueText  is a variable of type CString to hold old value of EditControl
	}
	else
	{
		
		edit.SetWindowText(matrixText[n]);

		//Setting the cursor position to previous position
		/* This step is very important, because if it is not written then cursor will move to left or right after above step depending whether the text is left or right aligned.*/
		edit.SetSel(lastSel);
		MessageBeep(MB_OK);
	}
}


//Проверяет строку на наличие в ней только цифр, точек, пробелов и переходов на другую строку(\r\n). Используется в CheckDouble().
bool CMatrixDlg::ValidateDoubleString(CString value)
{

	bool noProblem = true;
	for (int i = 0; i < value.GetLength(); i++)
	{
		char nChar = value[i];

		if (((nChar >= '0') && (nChar <= '9')) ||
			(nChar == '.') || (nChar == ' ') || (nChar == '\r') || (nChar == '\n'))
		{
		}
		else
		{
			noProblem = false;
			break;
		}
	}

	return noProblem;
}

//Misc

//Осуществляет переход на новую строку в выделенном поле ввода при нажатии Enter.
BOOL CMatrixDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN &&
		pMsg->wParam == VK_RETURN)
	{
		if (GetFocus() == &FirstMatrixCtrl)
		{
			BreakLine(FirstMatrixCtrl);
			return TRUE;
		}
		if (GetFocus() == &SecondMatrixCtrl)
		{
			BreakLine(SecondMatrixCtrl);
			return TRUE; 
		}
	}
	return FALSE; 
}


//Функция, используемая PreTranslateMessage(MSG*), что бы совершать переходы на новую строку.
void CMatrixDlg::BreakLine(CEdit& edit)
{
	CString value;
	edit.GetWindowText(value);
	value = value + _T("\r\n");
	int start = 0;
	int end = edit.GetWindowTextLength();
	edit.SetSel(start, end);
	edit.ReplaceSel(value);
}


