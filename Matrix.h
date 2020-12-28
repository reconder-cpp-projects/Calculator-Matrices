#pragma once

#include <vector>



//Класс матрицы.
template <typename T>
class Matrix
{
private:

	//Количество строк и столбцов матрицы соответственно.
	int rows, columns;

	//Значения матрицы, хранимые в векторе.
	std::vector<T> values;

public:

	//Нулевой конструктор, размер и значения матрицы можно позже выставить при помощи SetValues()
	Matrix() {};

	//Конструктор, создающий нулевую матрицу размером y*x.
	Matrix(int y, int x) : rows(y), columns(x) {
		if (x > 0 && y > 0)
		{
			values.resize(x * y, 0);
		}
		else
		{
			rows = -1;
			columns = -1;
		}
	};

	//Тот же самый конструктор, только принимающий std::pair
	Matrix(std::pair<int, int> size) : rows(size.first), columns(size.second) {
		Matrix(size.first, size.second);
	};

	//Конструктор, принимающий размеры матрицы и её значения. В случае несоответствия размеров значениям, матрица не будет работать.
	Matrix(int y, int x, std::vector<T> source) : rows(y), columns(x), values(source){
		if (x * y != source.size()) {
			rows = -1;
			columns = -1;
			values.empty();
		}
	}

	//Выставляет новые размеры и значения существующей матрице
	void SetValues(int y, int x, std::vector<T> source)
	{
		rows = y;
		columns = x;
		values = source;
	}

	//Возвращает размеры матрицы в виде std::pair {first = rows, second = columns}
	std::pair<int, int> GetSize() { return { rows, columns }; }

	//Предоставляет доступ к элементу на позиции (y, x)
	T& el(int y, int x) {
		return values[columns*y + x];
	}

	//Предоставляет доступ к элементу на позиции (y, x). Элемент матрицы m на позиции (2, 3) это m[{2,3}]
	T& operator[](std::pair<int, int> pos)
	{
		return values[columns * pos.first + pos.second];
	}


	//Умножает матрицы. В случае несоответсвия размеров, возвращает матрицу с размерами (-1, -1) и пустым вектором значений)
	Matrix operator*(Matrix& other) {
		if (columns != other.GetSize().first) 
		{ 
			Matrix result(-1, -1);
			return result; 
		}
		Matrix result(rows, other.GetSize().second);
		for (int i = 0; i < rows; ++i)
			for (int j = 0; j < other.GetSize().second; ++j)
				for (int k = 0; k < columns; ++k)
				{
					result[{i, j}] += values[columns * i + k] * other[{k, j}];
				}
		
		return result;

	}

	bool operator==(Matrix& other) {
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				if (values[columns * i + j] != other[{i, k}]) return false;
		return true;
	}
};