#pragma once
#ifndef LJZVECTOR
#define LJZVECTOR

#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

template <class T>
class LJZVector
{
public:
	//构造函数
	LJZVector();
	LJZVector(int length);
	LJZVector(std::vector<T> vectorData);

	//析构函数
	~LJZVector();

	//运算符重载
	template <class U> friend LJZVector<U> operator+(const LJZVector<U>& lhs,const LJZVector<U>& rhs);
	template <class U> friend LJZVector<U> operator+(const U& lhs, const LJZVector<U>& rhs);
	template <class U> friend LJZVector<U> operator+(const LJZVector<U>& lhs, const U& rhs);

	template <class U> friend LJZVector<U> operator-(const LJZVector<U>& lhs, const LJZVector<U>& rhs);
	template <class U> friend LJZVector<U> operator-(const U& lhs, const LJZVector<U>& rhs);
	template <class U> friend LJZVector<U> operator-(const LJZVector<U>& lhs, const U& rhs);
	
	//template <class U> friend LJZVector<U> operator*(const LJZVector<U>& lhs, const LJZVector<U>& rhs);
	template <class U> friend LJZVector<U> operator*(const U& lhs, const LJZVector<U>& rhs);
	template <class U> friend LJZVector<U> operator*(const LJZVector<U>& lhs, const U& rhs);

	LJZVector<T> operator=(const LJZVector<T>& rhs);
	
	//点乘和叉积
	static T dot(const LJZVector<T>& a, const LJZVector<T>& b);
	static LJZVector<T> cross(const LJZVector<T>& a, const LJZVector<T>& b);



	//工具函数
	T GetElement(int index) const;
	void SetElement(int index, T value);
	T GetMold();

	LJZVector<T> Normalized();//有返回值版，不改变原本的对象
	void Normalize();//无返回值版，原地直接标准化

	void PrintVector();

private:
	std::vector<T> m_vectorData;
	int m_length;
};




#endif // !LJZVECTOR
