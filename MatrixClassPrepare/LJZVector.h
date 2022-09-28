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
	//���캯��
	LJZVector();
	LJZVector(int length);
	LJZVector(std::vector<T> vectorData);

	//��������
	~LJZVector();

	//���������
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
	
	//��˺Ͳ��
	static T dot(const LJZVector<T>& a, const LJZVector<T>& b);
	static LJZVector<T> cross(const LJZVector<T>& a, const LJZVector<T>& b);



	//���ߺ���
	T GetElement(int index) const;
	void SetElement(int index, T value);
	T GetMold();

	LJZVector<T> Normalized();//�з���ֵ�棬���ı�ԭ���Ķ���
	void Normalize();//�޷���ֵ�棬ԭ��ֱ�ӱ�׼��

	void PrintVector();

private:
	std::vector<T> m_vectorData;
	int m_length;
};




#endif // !LJZVECTOR
