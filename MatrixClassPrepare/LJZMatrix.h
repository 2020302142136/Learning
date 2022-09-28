#pragma once
#ifndef LJZMATRIX
#define LJZMATRIX
#include<iostream>
#include<iomanip>
using namespace std;


/// 泛型，当用作类型名的时候要在类名后面加上<T>
///
template <class T>
class LJZMatrix
{
public:
	//构造函数
	LJZMatrix();
	LJZMatrix(int nRows, int nCols);
	LJZMatrix(int nRows, int nCols, const T* linearData);
	LJZMatrix(const LJZMatrix<T>& matrix);

	//析构函数
	~LJZMatrix();

	//工具函数
	T GetElementAt(int row, int col) const;//带const：函数不修改成员变量的值
	void SetElementAt(int row, int col, T value);
	void Seperate(LJZMatrix<T>& matrix1, LJZMatrix<T>& matrix2, int nCol);
	void CombineOtherMatrix(const LJZMatrix<T>& otherMatrix);
	bool IsSquare();
	bool IsSameSize(const LJZMatrix<T>& mat);
	//bool IsSameSize(const LJZMatrix<T>& mat1, const LJZMatrix<T>& mat2);
	void PrintMatrix();
	void SetToIdentity();
	bool Resize(int nRows, int nCols);
	void MultRow(int i, T multFactor);
	void MultAdd(int i, int j, T multFactor);
	int FindRowWithMaxElement(int colNumber, int startingRow);
	int TwoDIndex2LinearIndex(int row, int col) const;

	//算法函数
	bool Inverse();
	LJZMatrix<T> Transpose() const;

	//运算符重载
	bool operator==(const LJZMatrix<T>& rhs);

	template <class U> friend LJZMatrix<U> operator+(const LJZMatrix<U>& lhs, const LJZMatrix<U>& rhs);
	template <class U> friend LJZMatrix<U> operator+(const LJZMatrix<U>& lhs, const U& addValue);
	template <class U> friend LJZMatrix<U> operator+(const U& addValue, const LJZMatrix<U>& rhs);

	template <class U> friend LJZMatrix<U> operator-(const LJZMatrix<U>& lhs, const LJZMatrix<U>& rhs);
	template <class U> friend LJZMatrix<U> operator-(const LJZMatrix<U>& lhs, const U& subValue);
	template <class U> friend LJZMatrix<U> operator-(const U& subValue, const LJZMatrix<U>& rhs);

	template <class U> friend LJZMatrix<U> operator*(const LJZMatrix<U>& lhs, const LJZMatrix<U>& rhs);
	template <class U> friend LJZMatrix<U> operator*(const LJZMatrix<U>& lhs, const U& multValue);
	template <class U> friend LJZMatrix<U> operator*(const U& multValue, const LJZMatrix<U>& rhs);

	/// <summary>
	/// 此处再加上一个矩阵和向量类相乘的运算符重载
	/// </summary>
	
	/// <summary>
	/// 此处重载“=”号说明：有两种重载方法
	/// 1.以等号的右值rhs作为参数，将右值与自身相加之后返回一个新的值
	/// 2.可以以同时以左右值作为参数，相加后返回一个新的值
	/// </summary>
	/// <param name="rhs"></param>
	/// <returns></returns>
	LJZMatrix<T> operator=(const LJZMatrix<T>& rhs);

private:

	bool CloseEnough(T data1, T data2);
	void SwapRow(int i, int j);



private:
	//存放一维数据
	T* m_LinearData;
	int m_ElementsCount;
	int m_nRows;
	int m_nCols;
};



#endif // !LJZMATRIX







