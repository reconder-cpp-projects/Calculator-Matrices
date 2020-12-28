
// CalculatorDlg.h : header file
//

#pragma once
#include "CalculatorOperations.h"

// CCalculatorDlg dialog
class CCalculatorDlg : public CDialogEx
{
// Construction
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();

	//Раскраска кнопки  CMFCButton& в цвет  COLORREF
	void ColorButton(CMFCButton&, COLORREF);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//Создание диалога
	void Create();
	//Переменные текстового поля калькулятора
	CEdit CalculatorTextField;
	CString CalcTextFieldEdit;

	//Буфер для текстового поля
	CString textbox;
	
	/*Флаг для очистки калькулятора. Становится true при завершении операции в OnBnClickedButtonEquals(), что влечет за собой
	выполнение CheckReset() при нажатии любой кнопки.*/
	bool nextReset;

	//Контейнер, конструирующий числа из вводимых цифр, хранящий вводимые числа, а также операции. Struct для удобства.
	Number number;

	//Переменные кнопок для назначения им цветов.
	CMFCButton buttonClear;
	CMFCButton buttonPlus;
	CMFCButton buttonMinus;
	CMFCButton buttonTimes;
	CMFCButton buttonDivision;
	CMFCButton buttonEquals;

	/*Функции вызываемые при нажатии на числовые кнопки. Каждая вызывает NumberButtonClicked с соответствующей цифрой 
	в качестве аргумента.*/
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton0();


	/*Печатает принятую цифру в текстовое поле калькулятора. Добавляет соответсвующую цифру в ввод number.*/
	void NumberButtonClicked(int);


	//Добавляет точку в текстовое поле и вводимое число в number.
	afx_msg void OnBnClickedButtonDot();

	/*Функции выбора операции для калькулятора. Выводит соответстующую операцию в текстовое поле, 
	а также передает соответствующую операцию в number. Также сообщает number о конце ввода числа через number.FinishNumber()*/
	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg void OnBnClickedButtonTimes();
	afx_msg void OnBnClickedButtonDivision();

	/*Выводит соответстующую операцию и результат в текстовое поле ( " = результат"). Сообщает number о конце 
	ввода числа через number.FinishNumber(). Подсчет результата идет через number.Calc()*/
	afx_msg void OnBnClickedButtonEquals();
	//Очищает текстовое поле и обнуляет number через number.Reset()
	afx_msg void OnBnClickedButtonClear();

	//Добавляет к textbox свой аргумент и выводит textbox в текстовое поле. Вызывается при нажитии всех кнопок, кроме Clear
	void UpdateText(CString&);

	/*Очищает текстовое поле калькулятора. Происходит при вызове OnBnClickedButtonClear() или любой другой кнопки, 
	если nextReset = true.*/
	void ResetText();

	//При nextReset = true вызывает OnBnClickedButtonClear(). При nextReset = false не делает ничего.
	void CheckReset();
};
