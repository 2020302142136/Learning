#pragma once
#ifndef LJZMATRIX
#define LJZMATRIX
#include<iostream>
#include<iomanip>
using namespace std;


/// ���ͣ���������������ʱ��Ҫ�������������<T>
///
template <class T>
class LJZMatrix
{
public:
	//���캯��
	LJZMatrix();
	LJZMatrix(int nRows, int nCols);
	LJZMatrix(int nRows, int nCols, const T* linearData);
	LJZMatrix(const LJZMatrix<T>& matrix);

	//��������
	~LJZMatrix();

	//���ߺ���
	T GetElementAt(int row, int col) const;//��const���������޸ĳ�Ա������ֵ
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

	//�㷨����
	bool Inverse();
	LJZMatrix<T> Transpose() const;

	//���������
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
	/// �˴��ټ���һ���������������˵����������
	/// </summary>
	
	/// <summary>
	/// �˴����ء�=����˵�������������ط���
	/// 1.�ԵȺŵ���ֵrhs��Ϊ����������ֵ���������֮�󷵻�һ���µ�ֵ
	/// 2.������ͬʱ������ֵ��Ϊ��������Ӻ󷵻�һ���µ�ֵ
	/// </summary>
	/// <param name="rhs"></param>
	/// <returns></returns>
	LJZMatrix<T> operator=(const LJZMatrix<T>& rhs);

private:

	bool CloseEnough(T data1, T data2);
	void SwapRow(int i, int j);



private:
	//���һά����
	T* m_LinearData;
	int m_ElementsCount;
	int m_nRows;
	int m_nCols;
};



#endif // !LJZMATRIX







