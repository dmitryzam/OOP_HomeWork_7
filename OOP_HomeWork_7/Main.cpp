#include<iostream>
#include"Matrix.hpp"


int main() {
	setlocale(LC_ALL, "RU");
	srand(time(NULL));

	try {
		Matrix<int> mx(3, 3);
		mx.fill_array();
		//mx.manual_fill_array();
		std::cout << "mx:\n";
		mx.print();
		std::cout << "***********************\n";
		std::cout << "Максимальное значение в матрице mx - " << mx.find_max() << std::endl;
		std::cout << "Минимальное значение в матрице mx - " << mx.find_min() << std::endl;
		std::cout << "***********************\n";
		// Заменим значение элемента [0][0] в массиве mx:
		//std::cout << "Enter the number -> ";
		//std::cin >> mx.Array()[0][0];
		//std::cout << "mx:\n";
		//mx.print();
		std::cout << "***********************\n";
		Matrix<int> mx1(3, 3);
		//mx1.fill_array();
		mx1.manual_fill_array();
		std::cout << "mx1:\n";
		mx1.print();
		std::cout << "***********************\n";
		Matrix<int> mx2(3, 3);
		mx2.fill_array();
		std::cout << "mx2:\n";
		mx2.print();
		std::cout << "***********************\n";
		std::cout << "Сложим матрицы mx1 и mx2\n";
		mx = mx1 + mx2;
		std::cout << "mx:\n";
		mx.print();
	}
	catch (const std::exception& ex) {
		std::cout << "Ошибка! " << ex.what() << std::endl;
	}
	return 0;
}