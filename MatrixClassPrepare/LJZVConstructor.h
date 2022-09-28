#pragma once
#ifndef VCONSTRUCTOR
#define VCONSTRUCTOR
#include"LJZVector.h"

template<class T>
LJZVector<T>::LJZVector()
{
	m_length = 0;
	m_vectorData = std::vector<T>();
}

template<class T>
LJZVector<T>::LJZVector(int length)
{
	m_length = length;
	m_vectorData = std::vector<T>(m_length, 0.0);
}

template<class T>
LJZVector<T>::LJZVector(std::vector<T> vectorData)
{
	m_length = vectorData.size();
	m_vectorData = vectorData;
}

template<class T>
LJZVector<T>::~LJZVector()
{
}


#endif // !VCONSTRUCTOR
