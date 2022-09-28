#include"LJZMatrix.h"
#ifndef TOOLKITS
#define TOOLKITS
template<class T>
T LJZMatrix<T>::GetElementAt(int row, int col) const
{
	int linearIndex = this->TwoDIndex2LinearIndex(row, col);

	if (linearIndex >= 0 && m_LinearData)
	{
		return m_LinearData[linearIndex];
	}
	else
	{
		return 0.0;
	}
}

template<class T>
int LJZMatrix<T>::TwoDIndex2LinearIndex(int row, int col)const
{
	if ((row >= 0) && (row < m_nRows) && (col >= 0) && (col < m_nCols))
	{
		return (row * m_nCols) + col;
	}
	else
	{
		return -1;
	}
}

template<class T>
void LJZMatrix<T>::SetElementAt(int row, int col, T value)
{
	int linearIndex = TwoDIndex2LinearIndex(row, col);

	if (linearIndex >= 0 && linearIndex < m_ElementsCount)
	{
		m_LinearData[linearIndex] = value;
	}
}

template<class T>
bool LJZMatrix<T>::IsSquare()
{
	if (m_nRows == m_nCols)
	{
		return true;
	}
	else
	{
		return false;
	}

}

template<class T>
void LJZMatrix<T>::PrintMatrix()
{
	for (int row = 0; row < m_nRows; row++)
	{
		for (int col = 0; col < m_nCols; col++)
		{
			std::cout << std::fixed << std::setprecision(3) << this->GetElementAt(row, col) << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

template<class T>
void LJZMatrix<T>::Seperate(LJZMatrix<T>& matrix1, LJZMatrix<T>& matrix2, int nCol)
{
	int mat1nCols = nCol;
	int mat2nCols = m_nCols - nCol;
	int mat1nRows = m_nRows;

	matrix1.Resize(mat1nRows, mat1nCols);
	matrix2.Resize(mat1nRows, mat2nCols);

	/*matrix1.PrintMatrix();
	matrix2.PrintMatrix();*/
	
	for (int row = 0; row < m_nRows; row++)
	{
		for (int col = 0; col < m_nCols; col++)
		{
			if (col < nCol)
			{
				matrix1.SetElementAt(row, col, this->GetElementAt(row, col));

			}
			else if(col>=nCol)
			{
				matrix2.SetElementAt(row, col - nCol, this->GetElementAt(row, col));
			}

		}
	}

	/*matrix1.PrintMatrix();
	matrix2.PrintMatrix();*/
	
}

template<class T>
void LJZMatrix<T>::CombineOtherMatrix(const LJZMatrix<T>& otherMatrix)
{
	int numRows1 = m_nRows;
	int numRows2 = otherMatrix.m_nRows;
	int numCols1 = m_nCols;
	int numCols2 = otherMatrix.m_nCols;

	if (numRows1 != numRows2)
		throw std::invalid_argument("Attempt to join matrices with different numbers of rows is invalid.");

	T* newMatrixData = new T[numRows1 * (numCols1 + numCols2)];

	int newIndex;
	for (int row = 0; row < m_nRows; row++)
	{
		for (int col = 0; col < numCols1 + numCols2; col++)
		{
			if (col < numCols1)
			{
				newIndex = row * (numCols1 + numCols2) + col;
				newMatrixData[newIndex] = this->GetElementAt(row, col);
			}
			else if (col >= numCols1)
			{
				newIndex = row * (numCols1 + numCols2) + col;
				newMatrixData[newIndex] = otherMatrix.GetElementAt(row, col - numCols1);
			}

		}
	}

	m_nCols = numCols1 + numCols2;
	m_ElementsCount = m_nRows * m_nCols;
	delete[] m_LinearData;
	m_LinearData = new T[m_ElementsCount];
	for (int i = 0; i < m_ElementsCount; ++i)
		m_LinearData[i] = newMatrixData[i];

	delete[] newMatrixData;
	

}

template<class T>
bool LJZMatrix<T>::CloseEnough(T data1, T data2)
{
	if (fabs(data1 - data2) < 1e-9)
	{
		return true;
	}
	return false;
}

template<class T>
int LJZMatrix<T>::FindRowWithMaxElement(int colNumber, int startingRow)
{
	T templeValue = this->GetElementAt(startingRow, colNumber);
	int maxRowIndex = startingRow;
	for (int row = startingRow + 1; row < m_nRows; row++)
	{
		if (fabs(this->GetElementAt(row, colNumber)) > fabs(templeValue))
		{
			maxRowIndex = row;
			templeValue = this->GetElementAt(row, colNumber);
		}
	}
	return maxRowIndex;
}

template<class T>
void LJZMatrix<T>::SwapRow(int i, int j)
{
	T* tempRow = new T[m_nCols];
	for (int rowIndex = 0; rowIndex < m_nCols; rowIndex++)
	{
		tempRow[rowIndex] = this->GetElementAt(i, rowIndex);
	}

	for (int rowIndex = 0; rowIndex < m_nCols; rowIndex++)
	{
		this->m_LinearData[TwoDIndex2LinearIndex(i, rowIndex)]
			=
			this->m_LinearData[TwoDIndex2LinearIndex(j, rowIndex)];
	}

	for (int rowIndex = 0; rowIndex < m_nCols; rowIndex++)
	{
		this->m_LinearData[TwoDIndex2LinearIndex(j, rowIndex)] = tempRow[rowIndex];
	}
	delete[] tempRow;
}

template<class T>
void LJZMatrix<T>::MultRow(int i, T multFactor)
{
	for (int col = 0; col < m_nCols; ++col)
		m_LinearData[TwoDIndex2LinearIndex(i, col)] *= multFactor;
}

template<class T>
void LJZMatrix<T>::MultAdd(int i, int j, T multFactor)
{
	for (int col = 0; col < m_nCols; ++col)
		m_LinearData[TwoDIndex2LinearIndex(i, col)] +=
		(m_LinearData[TwoDIndex2LinearIndex(j, col)] * multFactor);
}

template<class T>
void LJZMatrix<T>::SetToIdentity()
{
	if (!IsSquare())
	{
		throw std::invalid_argument("Cannot form an identity matrix that is not square.");
	}

	for (int row = 0; row < m_nRows; row++)
	{
		for (int col = 0; col < m_nCols; col++)
		{
			if (row == col)
			{
				this->SetElementAt(row, col, 1.0);
			}
			else
			{
				this->SetElementAt(row, col, 0.0);
			}
		}
	}
}

template<class T>
bool LJZMatrix<T>::Resize(int nRows, int nCols)
{
	m_nRows = nRows;
	m_nCols = nCols;
	m_ElementsCount = m_nRows * m_nCols;
	delete[] m_LinearData;
	m_LinearData = new T[m_ElementsCount];
	for (int i = 0; i < m_ElementsCount; i++)
	{
		m_LinearData[i] = 0.0;
	}
	return true;

}

template<class T>
bool LJZMatrix<T>::IsSameSize(const LJZMatrix<T>& mat)
{
	if ((this->m_nRows == mat.m_nRows) && this->m_nCols == mat.m_nCols)
	{
		return true;
	}
	else
	{
		return false;
	}

}

//template<class T>
//bool LJZMatrix<T>::IsSameSize(const LJZMatrix<T>& mat1, const LJZMatrix<T>& mat2)
//{
//	if ((mat1.m_nRows == mat2.m_nRows) && (mat1.m_nCols == mat2.m_nCols))
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
#endif // !TOOLKITS


