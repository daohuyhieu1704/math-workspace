#include "pch.h"
#include "OdGeScale3d.h"
#include <vector>

namespace Geometry
{
	const OdGeScale3d OdGeScale3d::kIdentity = OdGeScale3d(1.0, 1.0, 1.0);

	OdGeScale3d OdGeScale3d::operator*(const OdGeScale3d& scaleVec) const
	{
		return OdGeScale3d(sx * scaleVec.sx, sy * scaleVec.sy, sz * scaleVec.sz);
	}

	OdGeScale3d OdGeScale3d::operator*(double factor) const
	{
		return OdGeScale3d(sx * factor, sy * factor, sz * factor);
	}

	OdGeScale3d& OdGeScale3d::operator*=(const OdGeScale3d& scaleVec)
	{
		sx *= scaleVec.sx;
		sy *= scaleVec.sy;
		sz *= scaleVec.sz;
		return *this;
	}

	OdGeScale3d& OdGeScale3d::operator*=(double factor)
	{
		sx *= factor;
		sy *= factor;
		sz *= factor;
		return *this;
	}

	OdGeScale3d& OdGeScale3d::setToProduct(const OdGeScale3d& scaleVec1, const OdGeScale3d& scaleVec2)
	{
		sx = scaleVec1.sx * scaleVec2.sx;
		sy = scaleVec1.sy * scaleVec2.sy;
		sz = scaleVec1.sz * scaleVec2.sz;
		return *this;
	}

	OdGeScale3d& OdGeScale3d::setToProduct(const OdGeScale3d& scaleVec, double factor)
	{
		sx = scaleVec.sx * factor;
		sy = scaleVec.sy * factor;
		sz = scaleVec.sz * factor;
		return *this;
	}

	OdGeScale3d OdGeScale3d::inverse() const
	{
		return OdGeScale3d(1.0 / sx, 1.0 / sy, 1.0 / sz);
	}

	OdGeScale3d& OdGeScale3d::invert()
	{
		sx = 1.0 / sx;
		sy = 1.0 / sy;
		sz = 1.0 / sz;
		return *this;
	}

	bool OdGeScale3d::isProportional(double tolerance) const
	{
		// Collect non-zero scale factors
		std::vector<double> components;
		if (std::fabs(sx) > tolerance)
			components.push_back(sx);
		if (std::fabs(sy) > tolerance)
			components.push_back(sy);
		if (std::fabs(sz) > tolerance)
			components.push_back(sz);

		// If there are zero or one non-zero components, they are proportional
		if (components.size() <= 1)
		{
			return true;
		}

		// Calculate the base ratio using the first two non-zero components
		double baseRatio = components[0] / components[1];

		// Compare the ratios of subsequent components
		for (size_t i = 2; i < components.size(); ++i)
		{
			double currentRatio = components[0] / components[i];
			if (std::fabs(currentRatio - baseRatio) > tolerance)
			{
				return false;
			}
		}

		return true;
	}



	bool OdGeScale3d::operator==(const OdGeScale3d& scaleVec) const
	{
		return (sx == scaleVec.sx && sy == scaleVec.sy && sz == scaleVec.sz);
	}

	bool OdGeScale3d::operator!=(const OdGeScale3d& scaleVec) const
	{
		return !(*this == scaleVec);
	}

	bool OdGeScale3d::isEqualTo(const OdGeScale3d& scaleVec, double tol) const
	{
		return (std::abs(sx - scaleVec.sx) <= tol &&
			std::abs(sy - scaleVec.sy) <= tol &&
			std::abs(sz - scaleVec.sz) <= tol);
	}

	double& OdGeScale3d::operator[](unsigned int i)
	{
		return (i == 0) ? sx : (i == 1) ? sy : sz;
	}

	double OdGeScale3d::operator[](unsigned int i) const
	{
		return (i == 0) ? sx : (i == 1) ? sy : sz;
	}

	OdGeScale3d& OdGeScale3d::set(double xFactor, double yFactor, double zFactor)
	{
		sx = xFactor;
		sy = yFactor;
		sz = zFactor;
		return *this;
	}

	void OdGeScale3d::getMatrix(OdGeMatrix3d& xfm) const
	{
		// Set the matrix as a scaling matrix with sx, sy, and sz
		xfm.setToIdentity();
		xfm(0, 0) = sx;
		xfm(1, 1) = sy;
		xfm(2, 2) = sz;
	}

	OdGeScale3d& OdGeScale3d::extractScale(const OdGeMatrix3d& xfm)
	{
		// Extract the scaling factors from the matrix
		sx = xfm(0, 0);
		sy = xfm(1, 1);
		sz = xfm(2, 2);
		return *this;
	}

	OdGeScale3d& OdGeScale3d::removeScale(OdGeMatrix3d& xfm, bool negateX)
	{
		// Remove scaling from the matrix
		sx = xfm(0, 0);
		sy = xfm(1, 1);
		sz = xfm(2, 2);

		// Reset scale components to 1
		xfm(0, 0) = (negateX ? -1.0 : 1.0);
		xfm(1, 1) = 1.0;
		xfm(2, 2) = 1.0;
		return *this;
	}

	OdGeScale3d::operator OdGeMatrix3d() const
	{
		OdGeMatrix3d xfm;
		getMatrix(xfm);
		return xfm;
	}

	bool OdGeScale3d::isValid() const
	{
		return (sx != 0.0 && sy != 0.0 && sz != 0.0);
	}
	OdGeScale3d operator*(double factor, const OdGeScale3d& scaleVec)
	{
		return OdGeScale3d(factor * scaleVec.sx, factor * scaleVec.sy, factor * scaleVec.sz);
	}
}