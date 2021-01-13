#pragma once


#include <functional>;

//Функторы математических операций калькулятора

auto Plus = [](double& a, double& b) {return a + b; };
auto Minus = [](double& a, double& b) {return a - b; };
auto Times = [](double& a, double& b) {return a * b; };
auto Division = [](double& a, double& b) {
	if (b == 0) 
	{ return 0.0; }; 
	return a / b; };


/*Класс-калькулятор, также занимается интерпритацией ввода*/
struct Number {
	//Буфер вводимого числа. Конструируется из вводимых цифр
	double value = 0;

	//Первое введеное число
	double number1 = 0;

	//Второе введеное число
	double number2 = 0;

	//Показывает является ли вводимое число первым. Используется в FinishNumber()
	bool first = true;

	//Контейнер для операций калькулятора
	std::function<double(double&, double&)> action;

	//Была ли нажата точка в калькуляторе. Используется при вводе числа
	bool dot = false;

	//Добавляет новую цифру в вводимое число value. Использует dot, что бы определить была ли поставлена точка.
	void digitAdded(int digit)
	{
		value = value * 10 + digit;
		if (dot) {
			value /= 10;
		}
	}

	//Очищает вводимое число value. Используется в FinishNumber()
	void ResetValue()
	{
		value = 0;
		dot = false;
	}

	//Завершает ввод числа value и кладет его в number1 или number 2 в зависимости от first. 
	void FinishNumber()
	{
		if (first) { number1 = value; }
		else { number2 = value; }
		first = !first;

		ResetValue();
	}

	//Производит вычисление с данными числами и операцией. Операция может быть произвольной бинарной.
	double Calc()
	{
		if (action == nullptr) { return 0; }
		return action(number1, number2);
	}

	//Перезапускает калькулятор
	void Reset()
	{
		number1 = 0;
		number2 = 0;
		first = true;
		action = nullptr;
		ResetValue();
	}
};