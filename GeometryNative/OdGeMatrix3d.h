#pragma once

#include <cmath> // for std::abs and other math operations
#include <stdexcept>
#include "OdGePoint3d.h"

namespace GeometryNative
{
	class OdGeVector3d;
	class OdGeMatrix3d
	{
	public:
		OdGeMatrix3d();
		static const OdGeMatrix3d kIdentity;

		OdGeMatrix3d& setToIdentity();
		void validateZero();

		OdGeMatrix3d operator*(const OdGeMatrix3d& matrix) const;
		OdGeMatrix3d& operator*=(const OdGeMatrix3d& matrix);
		OdGeMatrix3d& preMultBy(const OdGeMatrix3d& leftSide);
		OdGeMatrix3d& postMultBy(const OdGeMatrix3d& rightSide);
		OdGeMatrix3d& setToProduct(const OdGeMatrix3d& matrix1, const OdGeMatrix3d& matrix2);

		double det3x3(double m[3][3]) const;
		void getMinor(int r, int c, double minor[3][3]) const;
		OdGeMatrix3d adjugate() const;

		OdGeMatrix3d& invert();
		OdGeMatrix3d inverse() const;
		bool isSingular() const;

		OdGeMatrix3d& transposeIt();
		OdGeMatrix3d transpose() const;

		bool operator==(const OdGeMatrix3d& matrix) const;
		bool operator!=(const OdGeMatrix3d& matrix) const;
		bool isEqualTo(const OdGeMatrix3d& matrix, double gTol = 1e-9) const;

		double det() const;
		OdGeMatrix3d& setTranslation(OdGeVector3d vect);
		OdGeVector3d translation() const;
		OdGeMatrix3d& setToTranslation(OdGeVector3d& vect);
		OdGeMatrix3d& setToRotation(double angle, OdGeVector3d& axis, const OdGePoint3d& center = OdGePoint3d::kOrigin);
		OdGeMatrix3d& setToScaling(double scale, OdGePoint3d& center);
		static OdGeMatrix3d scaling(double scale, const OdGePoint3d& center = OdGePoint3d::kOrigin);

		const double* operator[](int row) const;
		double* operator[](int row);
		double operator()(int row, int column) const;
		double& operator()(int row, int column);

		OdGeMatrix3d& operator*(double scalar);

	private:
		double entry[4][4];
	};
}
