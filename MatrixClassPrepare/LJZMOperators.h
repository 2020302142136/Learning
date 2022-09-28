#include"LJZMatrix.h"
#ifndef OPERATOR
#define OPERATOR


template<class T>
bool LJZMatrix<T>::operator==(const LJZMatrix<T>& rhs)
{
	//先判断两个矩阵size是否一致
	if (!this->IsSameSize(rhs))
	{
		return false;		
	}
	//再逐个对比
	for (int i = 0; i < m_ElementsCount; i++)
	{
		if (!CloseEnough(m_LinearData[i],rhs.m_LinearData[i]))
		{
			return false;
		}
	}
	return true;
}

template<class U>
LJZMatrix<U> operator+(const LJZMatrix<U>& lhs, const LJZMatrix<U>& rhs)
{

	if (lhs.m_nRows!=rhs.m_nRows||lhs.m_nCols!=rhs.m_nCols)
	{
		throw std::invalid_argument("Cannot add 2 Matrices with different size.");
	}
	else
	{
		int nRows = lhs.m_nRows;
		int nCols = lhs.m_nCols;
		int nElements = nRows * nCols;
		U* templeResult = new U[nElements];
		for (int i = 0; i < nElements; i++)
		{
			templeResult[i] = lhs.m_LinearData[i] + rhs.m_LinearData[i];
		}

		LJZMatrix<U> result(nRows, nCols, templeResult);
		delete[] templeResult;
		return result;
		/*T* templeResult
		returnValue.m_nRows = lhs.m_nRows;
		returnValue.m_nCols = lhs.m_nCols;
		returnValue.m_ElementsCount = nRows * nCols;
		for (int i = 0; i < returnValue.m_ElementsCount; i++)
		{
			returnValue.m_LinearData[i] = lhs.m_LinearData[i] + rhs.m_LinearData[i];
		}

		return returnValue;*/
	}

}

template<class U>
LJZMatrix<U> operator+(const LJZMatrix<U>& lhs, const U& addValue)
{
	int nRows = lhs.m_nRows;
	int nCols = lhs.m_nCols;
	int nElements = nRows * nCols;
	U* templeResult = new U[nElements];
	for (int i = 0; i < nElements; i++)
	{
		templeResult[i] = lhs.m_LinearData[i] + addValue;
	}

	LJZMatrix<U> result(nRows, nCols, templeResult);
	delete[] templeResult;
	return result;
	
}

template<class U>
LJZMatrix<U> operator+(const U& addValue, const LJZMatrix<U>& rhs)
{
	int nRows = rhs.m_nRows;
	int nCols = rhs.m_nCols;
	int nElements = nRows * nCols;
	U* templeResult = new U[nElements];
	for (int i = 0; i < nElements; i++)
	{
		templeResult[i] = rhs.m_LinearData[i] + addValue;
	}

	LJZMatrix<U> result(nRows, nCols, templeResult);
	delete[] templeResult;
	return result;
	
}

template<class U>
LJZMatrix<U> operator-(const LJZMatrix<U>& lhs, const LJZMatrix<U>& rhs)
{
	if (lhs.m_nRows != rhs.m_nRows || lhs.m_nCols != rhs.m_nCols)
	{
		throw std::invalid_argument("Cannot substract 2 Matrices with different size.");
	}
	else
	{
		int nRows = lhs.m_nRows;
		int nCols = lhs.m_nCols;
		int nElements = nRows * nCols;
		U* templeResult = new U[nElements];
		for (int i = 0; i < nElements; i++)
		{
			templeResult[i] = lhs.m_LinearData[i] - rhs.m_LinearData[i];
		}

		LJZMatrix<U> result(nRows, nCols, templeResult);
		delete[] templeResult;
		return result;
		
	}
}

template<class U>
LJZMatrix<U> operator-(const LJZMatrix<U>& lhs, const U& subValue)
{
	int nRows = lhs.m_nRows;
	int nCols = lhs.m_nCols;
	int nElements = nRows * nCols;
	U* templeResult = new U[nElements];
	for (int i = 0; i < nElements; i++)
	{
		templeResult[i] = lhs.m_LinearData[i] - subValue;
	}

	LJZMatrix<U> result(nRows, nCols, templeResult);
	delete[] templeResult;
	return result;
	
}

template<class U>
LJZMatrix<U> operator-(const U& subValue, const LJZMatrix<U>& rhs)
{
	int nRows = rhs.m_nRows;
	int nCols = rhs.m_nCols;
	int nElements = nRows * nCols;
	U* templeResult = new U[nElements];
	for (int i = 0; i < nElements; i++)
	{
		templeResult[i] = subValue - rhs.m_LinearData[i];
	}

	LJZMatrix<U> result(nRows, nCols, templeResult);
	delete[] templeResult;
	return result;
}

template<class U>
LJZMatrix<U> operator*(const LJZMatrix<U>& lhs, const LJZMatrix<U>& rhs)
{
	if (lhs.m_nCols!=rhs.m_nRows)
	{
		throw std::invalid_argument("Cannot add 2 Matrices with different size.");
	}
	else
	{
		int nRows = lhs.m_nRows;
		int nCols = rhs.m_nCols;
		int nElements = nRows * nCols;
		U* templeResult = new U[nElements];

		for (int row = 0; row < nRows; row++)
		{
			for (int col = 0; col < nCols; col++)
			{
				U elementValue = static_cast<U>(0.0);
				for (int i = 0; i < lhs.m_nCols; i++)
				{
					U lhsElement = lhs.GetElementAt(row, i);
					U rhsElement = rhs.GetElementAt(i, col);
					elementValue += lhsElement * rhsElement;
				}
				int resultLinearIndex = row * nCols + col;
				templeResult[resultLinearIndex] = elementValue;
			}
		}
		LJZMatrix<U> result(nRows, nCols, templeResult);
		delete[] templeResult;
		return result;
	}
	
}

template<class U>
LJZMatrix<U> operator*(const LJZMatrix<U>& lhs, const U& multValue)
{
	int nRows = lhs.m_nRows;
	int nCols = lhs.m_nCols;
	int nElements = nRows * nCols;
	U* templeResult = new U[nElements];

	for (int i = 0; i < nElements; i++)
	{
		templeResult[i] = lhs.m_LinearData[i] * multValue;
	}

	LJZMatrix<U> result(nRows, nCols, templeResult);
	delete[] templeResult;
	return result;
}

template<class U>
LJZMatrix<U> operator*(const U& multValue, const LJZMatrix<U>& rhs)
{
	int nRows = rhs.m_nRows;
	int nCols = rhs.m_nCols;
	int nElements = nRows * nCols;
	U* templeResult = new U[nElements];

	for (int i = 0; i < nElements; i++)
	{
		templeResult[i] = rhs.m_LinearData[i] * multValue;
	}

	LJZMatrix<U> result(nRows, nCols, templeResult);
	delete[] templeResult;
	return result;
}

template<class T>
LJZMatrix<T> LJZMatrix<T>::operator=(const LJZMatrix<T>& rhs)
{
	if (this != &rhs)
	{
		m_nRows = rhs.m_nRows;
		m_nCols = rhs.m_nCols;
		m_ElementsCount = rhs.m_ElementsCount;

		if (m_LinearData)
		{
			delete[] m_LinearData;
		}

		m_LinearData = new T[m_ElementsCount];
		for (int i = 0; i < m_ElementsCount; i++)
		{
			m_LinearData[i] = rhs.m_LinearData[i];
		}

		return *this;
	}
	else
	{
		throw std::invalid_argument("Cannot assign a same matrix to this value ");
	}
	
}

#endif // !OPERATOR
