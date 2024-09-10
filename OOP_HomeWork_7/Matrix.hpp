#pragma once
#include<iostream>
#include<exception>
#include<ctime>
#include<cstdlib>



template<typename ANY>
class Matrix {
private:
	ANY** array;	// указатель на массив указателей
	int row;		// строки
	int col;		// столбцы
public:
	Matrix() : array(nullptr), row(0), col(0){}
	Matrix(int row, int col) : row(row), col(col) {
		ANY** tmp = new ANY * [row];
		for (size_t i{}; i < row; ++i)
			tmp[i] = new ANY[col];
		array = tmp;
		tmp = nullptr;
	}
	~Matrix() {
		if (array == nullptr)
			return;		
		for (size_t i{}; i < row; ++i)
			delete[] array[i];		// сначала удаляем массивы указателей
		delete[] array;				// а потом удаляем массив указателей на массивы указателей))		
	}
	// Геттеры:
	int Row()const { return row; }
	int Col()const { return col; }
	ANY Array()const { return array; }
	// Метод вывода массива в консоль:
	void print()const {
		if (array == nullptr)
			throw std::exception("Передан нулевой массив!");
		for (size_t i_row{}; i_row < row; ++i_row) {
			for (size_t i_col{}; i_col < col; ++i_col)
				std::cout << array[i_row][i_col] << ' ';
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	// Метод заполнения массива случайными числами:
	void fill_array() {
		if (array == nullptr)
			throw std::exception("Передан нулевой массив!");
		
		for (size_t i_row{}; i_row < row; ++i_row)
			for (size_t i_col{}; i_col < col; ++i_col)
				array[i_row][i_col] = rand() % 10;
	}
	// Метод поиска максимального значения в матрице:
	ANY find_max()const {
		if (array == nullptr)
			throw std::exception("Передан нулевой массив!");
		ANY max = array[0][0];
		for (size_t i_row{}; i_row < row; ++i_row)
			for (size_t i_col{}; i_col < col; ++i_col) {
				if (array[i_row][i_col] > max)
					max = array[i_row][i_col];
			}
		return max;			
	}
	// Метод поиска минимального значения в матрице:
	ANY find_min()const {
		if (array == nullptr)
			throw std::exception("Передан нулевой массив!");
		ANY min = array[0][0];
		for (size_t i_row{}; i_row < row; ++i_row)
			for (size_t i_col{}; i_col < col; ++i_col) {
				if (array[i_row][i_col] < min)
					min = array[i_row][i_col];
			}
		return min;
	}
	// Метод заполнения матрицы с клавиатуры:
	void manual_fill_array() {
		if (array == nullptr)
			throw std::exception("Передан нулевой массив!");
		ANY tmp = ANY();
		for (size_t i_row{}; i_row < row; ++i_row)
			for (size_t i_col{}; i_col < col; ++i_col) {
				std::cout << "Введите значение элемента [" << i_row << "][" << i_col << "] -> ";
				std::cin >> tmp;
				array[i_row][i_col] = tmp;				
			}
		std::cout << "Матрица заполнена успешно!\n";
	}
	// Перегрузка оператора индексации для двумерного массива:
	ANY& operator()(int i_row, int i_col) {
		if (array == nullptr)
			throw std::exception("Передан нулевой массив!");
		if(i_row < 0 || i_row > row || i_col < 0 || i_col > col)
			throw std::exception("Введен неправильный индекс!");
		return array[i_row][i_col];
	}
	// Перегрузка оператора сложения двух матриц:		
	Matrix& operator+(Matrix& obj2) {
		if (row != obj2.Row() || col != obj2.Col())
			throw std::exception("Матрицы разных размеров!");

		ANY** tmp = new ANY * [row];
		for (size_t i{}; i < row; ++i)
			tmp[i] = new ANY[col];

		for (size_t i_row{}; i_row < row; ++i_row)
			for (size_t i_col{}; i_col < col; ++i_col) {
				tmp[i_row][i_col] = array[i_row][i_col];
				tmp[i_row][i_col] += obj2(i_row, i_col);
			}
		array = tmp;
		tmp = nullptr;
		return *this;
	}
	// Перегрузка оператора присваивания:
	Matrix& operator=(Matrix& other) {
		if (this == &other)
			return *this;
		// сначала очищаем двумерный массив:
		for (size_t i{}; i < row; ++i)
			delete[] array[i];
		delete[] array;
		
		this->row = other.row;
		this->col = other.col;
		if (other.row == 0 && other.col == 0) {
			array = nullptr;
			return *this;
		}
		
		ANY** tmp = new ANY * [row];
		for (size_t i{}; i < row; ++i)
			tmp[i] = new ANY[col];
		for (size_t i_row{}; i_row < row; ++i_row)
			for (size_t i_col{}; i_col < col; ++i_col)
				tmp[i_row][i_col] = other(i_row, i_col);
		array = tmp;
		tmp = nullptr;
		return *this;
	}
};

