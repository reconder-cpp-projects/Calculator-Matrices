// CalculatorDlg.h : header file
//

#pragma once
#include "Matrix.h"
#include <memory>
// CMatrixDlg dialog
class CMatrixDlg : public CDialogEx
{
	// Construction
public:
	CMatrixDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MATRIX_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	void ColorButton(CMFCButton&, COLORREF);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//Контрольная переменная для ввода первой матрицы
	CEdit FirstMatrixCtrl;
	//Контрольная переменная для ввода второй матрицы
	CEdit SecondMatrixCtrl;
	//Контрольная переменная для вывода результата перемножения матриц
	CEdit ResultMatrixCtrl;

	//Функция создания диалога, сгенерированная Visual Studio
	void Create();

	//Функция, вызываемая при нажатии на кнопку "Calculate". Выводит на экран результат перемножения двух матриц
	afx_msg void OnBnClickedButtonCalculate();

	/*Читает матрицы из полей FirstMatrixCtrl и SecondMatrixCtrl, проверяет их на полноту (кол-во столбцов в каждой строке 
	одинаково) и кладет в соответсвующие инпуты. Используется в OnBnClickedButtonCalculate(). 
	Выводит true, если какая-то из матриц не является полной. Выводит false, если обе матрицы полные. */
	bool CheckIfMatricesAreFull(Matrix<double>&, Matrix<double>&);

	/*Проверяет, перемножилась ли матрица успешно(подходят ли размеры для умножения матриц). Используется в OnBnClickedButtonCalculate().
	Выводит получившуюся матрицу в поле ResultMatrixCtrl, если матрица успешно перемножилась. 
	Выводит сообщение об ошибке, если в результате перемножения было обнаружено несовпадение размеров.*/
	void PrintResultIfMultiplied(Matrix<double>&);

	/*Читает матрицу из поля CEdit& и помещает ее в Matrix<double>&. Используется в CheckIfMatricesAreFull().
	Возвращает true, если матрица успешно считалась.
	Возвращает false, если матрица была недозаполнена.*/
	bool ReadMatrix(Matrix<double>&, CEdit&);

	//Печатает матрицу Matrix<double>& в поле CEdit&
	void PrintMatrix(CEdit&, Matrix<double>&);

	//Ввод

	/*Функция, вызываемая при вводе в поле первой матрицы. Не позволяет вводить никакие
	символы, кроме цифр, точки, пробела и перехода на следующую строку*/
	void OnEnChangeEditFirst();
	/*Функция, вызываемая при вводе в поле второй матрицы. Не позволяет вводить никакие
    символы, кроме цифр, точки, пробела и перехода на следующую строку*/
	afx_msg void OnEnChangeEditSecond();
	/*Функция, вызываемая OnEnChangeEditFirst() и OnEnChangeEditSecond(). Не позволяет вводить никакие символы,
	кроме цифр, точки, пробела и \r\n, в поле которое получает. matrixText используется как буфер и необходим для работы функции. 
	Принимаемый функцией int - это порядковый номер буфера для поля. Для FirstMatrixCtrl int = 0, для SecondMatrixCtrl int = 1*/
	void CheckDouble(CEdit&, int);
	//Проверяет строку на наличие в ней только цифр, точек, пробелов и переходов на другую строку(\r\n). Используется в CheckDouble().
	bool ValidateDoubleString(CString);
	//Буфер для CheckDouble
	std::vector<CString> matrixText;
	
	
	
	//Misc
	
	//Осуществляет переход на новую строку в выделенном поле ввода при нажатии Enter.
	BOOL PreTranslateMessage(MSG*);
	//Функция, используемая PreTranslateMessage(MSG*), что бы совершать переходы на новую строку.
	void BreakLine(CEdit&);
};