#pragma once
#ifndef VTOOLKITS
#define VTOOLKITS
#include"LJZVector.h"
template<class T>
T LJZVector<T>::GetElement(int index) const
{
	return m_vectorData[index];
}

template<class T>
void LJZVector<T>::SetElement(int index, T value)
{
	m_vectorData[index] = value;
}

template<class T>
T LJZVector<T>::GetMold()
{
	T mold = 0.0;
	for (int i = 0; i < m_length; i++)
	{
		mold += m_vectorData[i] * m_vectorData[i];
	}
	return sqrt(mold);

}

template<class T>
LJZVector<T> LJZVector<T>::Normalized()
{
	T normFactor = this->GetMold();
	
	LJZVector<T> result(m_vectorData);
	return result * (1.0 / normFactor);
}

template<class T>
void LJZVector<T>::Normalize()
{
	T normFactor = this->GetMold();

	for (int i = 0; i < m_length; i++)
	{
		T temp = m_vectorData[i] * (1.0 / normFactor);
		m_vectorData[i] = temp;
	}
}


template<class T>
void LJZVector<T>::PrintVector()
{
	for (int i = 0; i < m_length; i++)
	{
		std::cout << std::fixed << std::setprecision(3) << this->GetElement(i) << std::endl;
	}
	std::cout << std::endl;
}

#endif // !VTOOLKITS
