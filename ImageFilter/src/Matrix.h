#pragma once
#include <iostream>


class Matrix3f
{
public:
	Matrix3f() = default;
	Matrix3f(float x1, float y1, float z1,
		float x2, float y2, float z2,
		float x3, float y3, float z3)
	{
		m_Data[0][0] = x1;	m_Data[0][1] = y1;	m_Data[0][2] = z1;
		m_Data[1][0] = x2;	m_Data[1][1] = y2;	m_Data[1][2] = z2;
		m_Data[2][0] = x3;	m_Data[2][1] = y3;	m_Data[2][2] = z3;
	}

	inline float &operator()(std::size_t row, std::size_t col)
	{
		return m_Data[row][col];
	}
	inline const float &operator()(std::size_t row, std::size_t col) const
	{
		return m_Data[row][col];
	}

	inline float GetTotalElementsCount() const
	{
		float sum = 0.0f;

		for (std::size_t i = 0; i < 3; i++)
			for (std::size_t j = 0; j < 3; j++)
				sum += this->operator()(i, j);

		if (sum > 255.0f)
			sum = 255.0f;
		if (sum < 0.0f)
			sum = 0.0f;

		return sum;
	}

private:
	float m_Data[3][3];
};

std::ostream &operator <<(std::ostream &stream, const Matrix3f &matrix)
{
	for (std::size_t i = 0; i < 3; i++)
	{
		for (std::size_t j = 0; j < 3; j++)
			stream << matrix(i, j) << ", ";
		stream << std::endl;
	}

	return stream;
}


namespace Matrix
{
	static Matrix3f ComponentWiseMultiplication(const Matrix3f &mat1, const Matrix3f &mat2)
	{
		return Matrix3f {
			mat1(0, 0) * mat2(0, 0),	mat1(0, 1) * mat2(0, 1),	mat1(0, 2) * mat2(0, 2),
			mat1(1, 0) * mat2(1, 0),	mat1(1, 1) * mat2(1, 1),	mat1(1, 2) * mat2(2, 2),
			mat1(2, 0) * mat2(2, 0),	mat1(2, 1) * mat2(2, 1),	mat1(2, 2) * mat2(2, 2)
		};
	}
}