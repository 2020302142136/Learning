#include "LJZMatrix.h"
#ifndef CONSTRUCTOR
#define CONSTRUCTOR
/*构造函数定义*/
template <class T>
LJZMatrix<T>::LJZMatrix()
{
	m_nRows = 1;
	m_nCols = 1;
	m_ElementsCount = 1;
	m_LinearData = nullptr;
}

template <class T>
LJZMatrix<T>::LJZMatrix(int nRows, int nCols)
{
	m_nRows = nRows;
	m_nCols = nCols;
	m_ElementsCount = m_nRows * m_nCols;
	
	m_LinearData = new T[m_ElementsCount];

	for (int i = 0; i < m_ElementsCount; i++)
	{
		m_LinearData[i] = 0.0;
	}
	
}

template <class T>
LJZMatrix<T>::LJZMatrix(int nRows, int nCols, const T* linearData)
{
	m_nRows = nRows;
	m_nCols = nCols;
	m_ElementsCount = m_nRows * m_nCols;

	m_LinearData = new T[m_ElementsCount];
	for (int i = 0; i < m_ElementsCount; i++)
	{
		m_LinearData[i] = linearData[i];
	}

}

template <class T>
LJZMatrix<T>::LJZMatrix(const LJZMatrix<T>& matrix)
{
	m_nRows = matrix.m_nRows;
	m_nCols = matrix.m_nCols;
	m_ElementsCount = m_nRows * m_nCols;

	m_LinearData = new T[m_ElementsCount];
	for (int i = 0; i < m_ElementsCount; i++)
	{
		m_LinearData[i] = matrix.m_LinearData[i];
	}
}


/*析构函数定义*/
template <class T>
LJZMatrix<T>::~LJZMatrix()
{
	if (m_LinearData)
	{
		delete[] m_LinearData;
	}
	
	m_LinearData = nullptr;
}

#endif // !CONSTRUCTOR