#include "pch.h"
#include "OdGeMatrix3d.h"

namespace Geometry
{
	const OdGeMatrix3d OdGeMatrix3d::kIdentity = OdGeMatrix3d().setToIdentity();

	OdGeMatrix3d::OdGeMatrix3d()
	{
		setToIdentity();
	}

	OdGeMatrix3d& OdGeMatrix3d::setToIdentity()
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				entry[i][j] = (i == j) ? 1.0 : 0.0;
			}
		}
		return *this;
	}

	void OdGeMatrix3d::validateZero()
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (std::abs(entry[i][j]) < 1e-6)
				{
					entry[i][j] = 0.0;
				}
			}
		}
	}

	OdGeMatrix3d OdGeMatrix3d::operator*(const OdGeMatrix3d& matrix) const
	{
		OdGeMatrix3d result;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				result.entry[i][j] = 0.0;
				for (int k = 0; k < 4; ++k)
				{
					result.entry[i][j] += entry[i][k] * matrix.entry[k][j];
				}
			}
		}
		return result;
	}

	OdGeMatrix3d& OdGeMatrix3d::operator*=(const OdGeMatrix3d& matrix)
	{
		*this = *this * matrix;
		return *this;
	}

	OdGeMatrix3d& OdGeMatrix3d::preMultBy(const OdGeMatrix3d& leftSide)
	{
		*this = leftSide * (*this);
		return *this;
	}

	OdGeMatrix3d& OdGeMatrix3d::postMultBy(const OdGeMatrix3d& rightSide)
	{
		*this = *this * rightSide;
		return *this;
	}

	OdGeMatrix3d& OdGeMatrix3d::setToProduct(const OdGeMatrix3d& matrix1, const OdGeMatrix3d& matrix2)
	{
		*this = matrix1 * matrix2;
		return *this;
	}

	double OdGeMatrix3d::det3x3(double m[3][3]) const
	{
		return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
			- m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
			+ m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
	}

	void OdGeMatrix3d::getMinor(int r, int c, double minor[3][3]) const
	{
		int row = 0, col = 0;
		for (int i = 0; i < 4; ++i)
		{
			if (i == r) continue;

			col = 0;
			for (int j = 0; j < 4; ++j)
			{
				if (j == c) continue;

				minor[row][col] = entry[i][j];
				++col;
			}
			++row;
		}
	}

	OdGeMatrix3d OdGeMatrix3d::adjugate() const
	{
		OdGeMatrix3d adj;
		double minor[3][3];

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				getMinor(i, j, minor);

				double cofactor = det3x3(minor);
				if ((i + j) % 2 != 0)
					cofactor = -cofactor;

				adj.entry[j][i] = cofactor;
			}
		}

		return adj;
	}

	OdGeMatrix3d& OdGeMatrix3d::invert()
	{
		double determinant = det();
		if (std::abs(determinant) < 1e-9)
		{
			throw std::runtime_error("eInvalidInput: Matrix determinant is zero.");
		}

		*this = adjugate() * (1.0 / determinant);
		return *this;
	}

	OdGeMatrix3d OdGeMatrix3d::inverse() const
	{
		OdGeMatrix3d result = *this;
		return result.invert();
	}

	bool OdGeMatrix3d::isSingular() const
	{
		return std::abs(det()) < 1e-6;
	}

	OdGeMatrix3d& OdGeMatrix3d::transposeIt()
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = i + 1; j < 4; ++j)
			{
				std::swap(entry[i][j], entry[j][i]);
			}
		}
		return *this;
	}

	OdGeMatrix3d OdGeMatrix3d::transpose() const
	{
		OdGeMatrix3d result = *this;
		return result.transposeIt();
	}

	bool OdGeMatrix3d::operator==(const OdGeMatrix3d& matrix) const
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (entry[i][j] != matrix.entry[i][j])
					return false;
			}
		}
		return true;
	}

	bool OdGeMatrix3d::operator!=(const OdGeMatrix3d& matrix) const
	{
		return !(*this == matrix);
	}

	bool OdGeMatrix3d::isEqualTo(const OdGeMatrix3d& matrix, double gTol) const
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (std::abs(entry[i][j] - matrix.entry[i][j]) > gTol)
					return false;
			}
		}
		return true;
	}

	double OdGeMatrix3d::det() const
	{
		double determinant = 0.0;
		double minor[3][3];

		for (int col = 0; col < 4; ++col)
		{
			getMinor(0, col, minor);
			double cofactor = det3x3(minor);
			if (col % 2 != 0) cofactor = -cofactor;
			determinant += entry[0][col] * cofactor;
		}

		return determinant;
	}

	OdGeMatrix3d& OdGeMatrix3d::setTranslation(OdGeVector3d vect)
	{
		entry[0][3] = vect.x;
		entry[1][3] = vect.y;
		entry[2][3] = vect.z;
		return *this;
	}

	OdGeVector3d OdGeMatrix3d::translation() const
	{
		return OdGeVector3d(entry[0][3], entry[1][3], entry[2][3]);
	}

	OdGeMatrix3d& OdGeMatrix3d::setToTranslation(OdGeVector3d& vect)
	{
		setToIdentity();
		setTranslation(vect);
		return *this;
	}

	OdGeMatrix3d& OdGeMatrix3d::setToRotation(double angle, OdGeVector3d& axis, const OdGePoint3d& center)
	{
		// Implement rotation matrix based on angle, axis, and center
		return *this;
	}

	OdGeMatrix3d& OdGeMatrix3d::setToScaling(double scale, OdGePoint3d& center)
	{
		setToIdentity();
		entry[0][0] = scale;
		entry[1][1] = scale;
		entry[2][2] = scale;
		setTranslation(OdGeVector3d(center.x * (1 - scale), center.y * (1 - scale), center.z * (1 - scale)));
		return *this;
	}

	OdGeMatrix3d OdGeMatrix3d::scaling(double scale, const OdGePoint3d& center)
	{
		OdGeMatrix3d result;
		OdGePoint3d nonConstCenter = center;
		result.setToScaling(scale, nonConstCenter);
		return result;
	}

	const double* OdGeMatrix3d::operator[](int row) const
	{
		return entry[row];
	}

	double* OdGeMatrix3d::operator[](int row)
	{
		return entry[row];
	}

	double OdGeMatrix3d::operator()(int row, int column) const
	{
		return entry[row][column];
	}

	double& OdGeMatrix3d::operator()(int row, int column)
	{
		return entry[row][column];
	}

	OdGeMatrix3d& OdGeMatrix3d::operator*(double scalar)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				entry[i][j] *= scalar;
			}
		}
		return *this;
	}
}

