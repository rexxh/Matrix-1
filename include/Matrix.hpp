#ifndef Matrix_hpp
#define Matrix_hpp

#pragma once
#include <fstream>
#include <iostream>

using namespace std;

ofstream fout;
ifstream fin;

template <typename T>
class Matrix;

template <typename T>
std::ostream & operator<<(std::ostream & output, const Matrix <T> & matrix)
{
	for (unsigned int i = 0; i < matrix.stroki; ++i) {
		output << std::endl;
		for (unsigned int j = 0; j < matrix.stolbs; ++j) {
			output << matrix.e[i][j] << "\t";
		}
	}

	return output;
}

template <typename T>
std::istream & operator>>(std::istream & input, Matrix <T> & matrix)
{
	for (unsigned int i = 0; i < matrix.stroki; ++i) {
		for (unsigned int j = 0; j < matrix.stolbs; ++j) {
			if (!(input >> matrix.e[i][j])) {
				throw "exception in fill matrix";
			}
		}
	}

	return input;
}



template <typename T>
class Matrix
{
	int stroki;
	int stolbs;
	T **e;
	
public:

	auto operator==(const Matrix &matrix) const -> bool;
	friend std::ostream & operator<< <>(std::ostream & output, const Matrix &);
	friend std::istream & operator>> <>(std::istream & input, Matrix &);

	Matrix() : stroki(0), stolbs(0), e(nullptr) {};
	Matrix(int n, int m) : stroki(n), stolbs(m)
	{
		e = new T*[n];
		for (int i = 0; i < n; i++)
			e[i] = new T[m];
	};
	Matrix(const Matrix &M) : stroki(M.stroki), stolbs(M.stolbs)
	{ //Конструктор копирования
		e = new T*[stroki];
		for (int i = 0; i < stroki; i++)
		{
			e[i] = new T[stolbs];
		}
		for (int i = 0; i < stroki; i++)
		{
			for (int j = 0; j < stolbs; j++)
			{
				e[i][j] = M.e[i][j];
			}
		}

	};
	~Matrix(){
		{
			if (e != nullptr)
			{
				for (int i = 0; i < stroki; i++)
				{
					delete[] e[i];
				}
				delete[] e;
			}
		}
	};
	void Set(char *path)
	{ //Запись в файл
		fout.open(path);
		for (int i = 0; i < stroki; i++)
		{
			for (int j = 0; j < stolbs; j++)
			{
				cin >> e[i][j];
				fout << " " << e[i][j];
			}
			fout << "\n";
		}
		fout.close();
	};
	int STR() {  return stroki; };
	int STOLB(){ return stolbs; };
	T**  print()
	{ //Вывод на экран
       
		for (int i = 0; i < stroki; i++)
		{
			for (int j = 0; j < stolbs; j++)
			{
				cout << e[i][j] << " ";
			}
			cout << "\n";
		}
		return e;
	};

	Matrix operator + ( const Matrix &M2)
	{ //Оператор сложения 2ух матриц
		Matrix M3(M2.stroki, M2.stolbs);
		for (int i = 0; i < M2.stroki; i++)
		for (int j = 0; j < M2.stolbs; j++)
			M3.e[i][j] = e[i][j] + M2.e[i][j];
		cout << "Матрица 1 + Матрица 2=\n"; M3.print();
		return M3;
	};
	
	Matrix operator *(const Matrix &M2) const{
		if (stroki != M2.stolbs){ throw "razmery matric..."; }
		Matrix M_res(stroki, M2.stroki);
		for (int i = 0; i < stroki; i++)
		for (int j = 0; j < M2.stolbs; j++)
		{
			M_res.e[i][j] = 0;
			for (int k = 0; k < M2.stolbs; k++)
				M_res.e[i][j] += (e[i][k] * M2.e[k][j]);
		}
		cout << "M1*M2:\n";  M_res.print();
		return M_res;
	}
	
	T * operator [] (int k)
	{
		T* stroka = new T[stolbs];
		for (int j = 0; j < stolbs; j++)
		{
			stroka[j] = e[k - 1][j];
		}
		return stroka;
	};

	void swap(Matrix & M2)
	{
		// обмен всех членов с M2
		std::swap(stroki, M2.stroki);
		std::swap(stolbs, M2.stolbs);
		std::swap(e, M2.e);
	};

	Matrix & operator = (Matrix M2)
	{
		// обмен this с M2
		swap(M2);
		return *this;
		//M2 уничтожается, освобождая память
	}
	
	T** getE() {
		return e;
	}
};

template <typename T>
auto Matrix<T>::operator==(const Matrix & matrix) const -> bool
{
	if (stroki != matrix.stroki || stolbs != matrix.stolbs) {
		return false;
	}
	for (unsigned int i = 0; i < stroki; ++i) {
		for (unsigned int j = 0; j < stolbs; ++j) {
			if (e[i][j] != matrix.e[i][j]) {
				return false;
			}
		}
	}
	return true;
}

#endif;
