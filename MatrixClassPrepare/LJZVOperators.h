#pragma once
#ifndef VOPERATORS
#define VOPERATORS
#include"LJZVector.h"

template<class U>
LJZVector<U> operator+(const LJZVector<U>& lhs, const LJZVector<U>& rhs)
{
	if (lhs.m_length!=rhs.m_length)
	{
		throw std::invalid_argument("Vector dimensions do not match.");
	}

	std::vector<U> resultVector;
	for (int i = 0; i < lhs.m_length; i++)
	{
		resultVector.push_back(lhs.m_vectorData[i] + rhs.m_vectorData[i]);
	}

	LJZVector<U> result( resultVector);
	return result;
}

template<class U>
LJZVector<U> operator+(const U& lhs, const LJZVector<U>& rhs)
{
	
	std::vector<U> resultVector;
	for (int i = 0; i < rhs.m_length; i++)
	{
		resultVector.push_back(rhs.m_vectorData[i] + lhs);
	}

	LJZVector<U> result(resultVector);
	return result;
}

template<class U>
LJZVector<U> operator+(const LJZVector<U>& lhs, const U& rhs)
{
	std::vector<U> resultVector;
	for (int i = 0; i < lhs.m_length; i++)
	{
		resultVector.push_back(lhs.m_vectorData[i] + rhs);
	}

	LJZVector<U> result(resultVector);
	return result;
}

template<class U>
LJZVector<U> operator-(const LJZVector<U>& lhs, const LJZVector<U>& rhs)
{
	if (lhs.m_length != rhs.m_length)
	{
		throw std::invalid_argument("Vector dimensions do not match.");
	}

	std::vector<U> resultVector;
	for (int i = 0; i < lhs.m_length; i++)
	{
		resultVector.push_back(lhs.m_vectorData[i] - rhs.m_vectorData[i]);
	}

	LJZVector<U> result(resultVector);
	return result;
}

template<class U>
LJZVector<U> operator-(const U& lhs, const LJZVector<U>& rhs)
{

	std::vector<U> resultVector;
	for (int i = 0; i < rhs.m_length; i++)
	{
		resultVector.push_back(rhs.m_vectorData[i] - lhs);
	}

	LJZVector<U> result(resultVector);
	return result;
}

template<class U>
LJZVector<U> operator-(const LJZVector<U>& lhs, const U& rhs)
{
	std::vector<U> resultVector;
	for (int i = 0; i < lhs.m_length; i++)
	{
		resultVector.push_back(lhs.m_vectorData[i] - rhs);
	}

	LJZVector<U> result(resultVector);
	return result;
}

//template<class U>
//LJZVector<U> operator*(const LJZVector<U>& lhs, const LJZVector<U>& rhs)
//{
//	if (lhs.m_length != rhs.m_length)
//	{
//		throw std::invalid_argument("Vector dimensions do not match.");
//	}
//
//	std::vector<U> resultVector;
//	for (int i = 0; i < lhs.m_length; i++)
//	{
//		resultVector.push_back(lhs.m_vectorData[i] - rhs.m_vectorData[i]);
//	}
//
//	LJZVector<U> result(resultVector);
//	return result;
//}

template<class U>
LJZVector<U> operator*(const U& lhs, const LJZVector<U>& rhs)
{

	std::vector<U> resultVector;
	for (int i = 0; i < rhs.m_length; ++i)
		resultVector.push_back(rhs.m_vectorData[i] * lhs);

	LJZVector<U> result(resultVector);
	return result;
}

template<class U>
LJZVector<U> operator*(const LJZVector<U>& lhs, const U& rhs)
{
	std::vector<U> resultVector;
	for (int i = 0; i < lhs.m_length; ++i)
		resultVector.push_back(lhs.m_vectorData[i] * rhs);

	LJZVector<U> result(resultVector);
	return result;
}

template<class T>
LJZVector<T> LJZVector<T>::operator=(const LJZVector<T>& rhs)
{
	
	this->m_length = rhs.m_length;
	this->m_vectorData.clear();
	for (int i = 0; i < m_length; i++)
	{	
		this->m_vectorData.push_back(rhs.GetElement(i));
	}
	
	return *this;
}

template<class T>
T LJZVector<T>::dot(const LJZVector<T>& a, const LJZVector<T>& b)
{
	if (a.m_length != b.m_length)
	{
		throw std::invalid_argument("Vector dimensions do not match.");
	}

	T returnValue = 0.0f;
	for (int i = 0; i < a.m_length; i++)
	{
		returnValue += a.m_vectorData[i] * b.m_vectorData[i];
	}

	return returnValue;
}

template<class T>
LJZVector<T> LJZVector<T>::cross(const LJZVector<T>& a, const LJZVector<T>& b)
{
	if (a.m_length != b.m_length)
		throw std::invalid_argument("Vector dimensions must match for the cross-product to be computed.");

	if (a.m_length != 3)
		throw std::invalid_argument("The cross-product can only be computed for three-dimensional vectors.");

	std::vector<T> resultVector;
	resultVector.push_back((a.m_vectorData.at(1) * b.m_vectorData.at(2)) - (a.m_vectorData.at(2) * b.m_vectorData.at(1)));
	resultVector.push_back(-((a.m_vectorData.at(0) * b.m_vectorData.at(2)) - (a.m_vectorData.at(2) * b.m_vectorData.at(0))));
	resultVector.push_back((a.m_vectorData.at(0) * b.m_vectorData.at(1)) - (a.m_vectorData.at(1) * b.m_vectorData.at(0)));

	LJZVector<T> result(resultVector);
	return result;
}


#endif // !VOPERATORS
