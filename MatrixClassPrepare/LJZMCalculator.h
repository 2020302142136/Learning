#include"LJZMatrix.h"

#ifndef CALCULATOR
#define CALCULATOR


template<class T>
bool LJZMatrix<T>::Inverse()
{
	if (!IsSquare())
	{
		throw std::invalid_argument("Cannot compute the inverse of a matrix that is not square.");
	}

	LJZMatrix<T> identityMatrix(m_nRows, m_nCols);
	identityMatrix.SetToIdentity();

	int originalNumCols = m_nCols;
	CombineOtherMatrix(identityMatrix);

	// 开始主要流程
	int cRow, cCol;
	int maxCount = 100;
	int count = 0;
	bool completeFlag = false;
	while ((!completeFlag) && (count < maxCount))
	{
		for (int diagIndex = 0; diagIndex < m_nRows; ++diagIndex)
		{
			cRow = diagIndex;
			cCol = diagIndex;

			int maxIndex = FindRowWithMaxElement(cCol, cRow);

			if (maxIndex != cRow)
			{
				SwapRow(cRow, maxIndex);
			}
			if (m_LinearData[TwoDIndex2LinearIndex(cRow, cCol)] != 1.0)
			{
				T multFactor = 1.0 / m_LinearData[TwoDIndex2LinearIndex(cRow, cCol)];
				MultRow(cRow, multFactor);
			}

			for (int rowIndex = cRow + 1; rowIndex < m_nRows; ++rowIndex)
			{
				if (!CloseEnough(m_LinearData[TwoDIndex2LinearIndex(rowIndex, cCol)], 0.0))
				{
					int rowOneIndex = cCol;

					T currentElementValue = m_LinearData[TwoDIndex2LinearIndex(rowIndex, cCol)];

					T rowOneValue = m_LinearData[TwoDIndex2LinearIndex(rowOneIndex, cCol)];

					if (!CloseEnough(rowOneValue, 0.0))
					{
						T correctionFactor = -(currentElementValue / rowOneValue);

						MultAdd(rowIndex, rowOneIndex, correctionFactor);

					}
				}
			}

			for (int colIndex = cCol + 1; colIndex < originalNumCols; ++colIndex)
			{
				if (!CloseEnough(m_LinearData[TwoDIndex2LinearIndex(cRow, colIndex)], 0.0))
				{
					int rowOneIndex = colIndex;

					T currentElementValue = m_LinearData[TwoDIndex2LinearIndex(cRow, colIndex)];

					T rowOneValue = m_LinearData[TwoDIndex2LinearIndex(rowOneIndex, colIndex)];

					if (!CloseEnough(rowOneValue, 0.0))
					{
						T correctionFactor = -(currentElementValue / rowOneValue);
						MultAdd(cRow, rowOneIndex, correctionFactor);
					}
				}
			}
		}

		LJZMatrix<T> leftHalf;
		LJZMatrix<T> rightHalf;
		this->Seperate(leftHalf, rightHalf, originalNumCols);

		if (leftHalf == identityMatrix)
		{
			completeFlag = true;

			m_nCols = originalNumCols;
			m_ElementsCount = m_nRows * m_nCols;
			delete[] m_LinearData;
			m_LinearData = new T[m_ElementsCount];
			for (int i = 0; i < m_ElementsCount; ++i)
				m_LinearData[i] = rightHalf.m_LinearData[i];
		}

		count++;
	}

	return completeFlag;
	
}

template<class T>
LJZMatrix<T> LJZMatrix<T>::Transpose() const
{
	int nRows = this->m_nCols;
	int nCols = this->m_nRows;
	int nElements = nRows * nCols;

	T* templeResult = new T[nElements];
	for (int row = 0; row < m_nRows; row++)
	{
		for (int col = 0; col < m_nCols; col++)
		{
			int newMatrixLinearIndex = col * nCols + row;
			templeResult[newMatrixLinearIndex] = this->GetElementAt(row,col);
		}
	}

	LJZMatrix<T> result(nRows, nCols, templeResult);
	delete[] templeResult;
	return result;
}

#endif // !CALCULATOR