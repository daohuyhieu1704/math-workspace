#include "OdGeMatrix2d.h"
#include "OdGeScale3d.h"
#include <cmath>

namespace Geometry
{
	class OdGeScale2d
	{
	public:
		/** \details
		  Default constructor for the OdGeScale2d class.

		  \remarks
		  Constructs the uniform unit scale transformation.
		*/
		OdGeScale2d() : sx(1.0), sy(1.0) {}

		/** \details
		  Constructor for the OdGeScale2d class.

		  \param factor [in]  Uniform scale factor.

		  \remarks
		  The constructor constructs a unified scale factor with the specified double value.
		*/
		OdGeScale2d(double factor) : sx(factor), sy(factor) {}

		/** \details
		  Constructor for the OdGeScale2d class.

		  \param xFactor [in]  The X scale factor.
		  \param yFactor [in]  The Y scale factor.

		  \remarks
		  The constructor constructs scale transformation with the specified factors for X and Y axes.
		*/
		OdGeScale2d(double xFactor, double yFactor) : sx(xFactor), sy(yFactor) {}

		// Multiplicative identity vector.
		static const OdGeScale2d kIdentity;

		OdGeScale2d operator *(const OdGeScale2d& scaleVec) const
		{
			return OdGeScale2d(sx * scaleVec.sx, sy * scaleVec.sy);
		}

		friend OdGeScale2d operator *(double factor, const OdGeScale2d& scaleVec)
		{
			return OdGeScale2d(factor * scaleVec.sx, factor * scaleVec.sy);
		}

		OdGeScale2d& operator *=(const OdGeScale2d& scaleVec)
		{
			sx *= scaleVec.sx;
			sy *= scaleVec.sy;
			return *this;
		}

		OdGeScale2d& preMultBy(const OdGeScale2d& leftSide)
		{
			return operator *=(leftSide);
		}

		OdGeScale2d& postMultBy(const OdGeScale2d& rightSide)
		{
			return operator *=(rightSide);
		}

		OdGeScale2d& setToProduct(const OdGeScale2d& scaleVec, double factor)
		{
			sx = scaleVec.sx * factor;
			sy = scaleVec.sy * factor;
			return *this;
		}

		OdGeScale2d& setToProduct(const OdGeScale2d& scaleVec1, const OdGeScale2d& scaleVec2)
		{
			sx = scaleVec1.sx * scaleVec2.sx;
			sy = scaleVec1.sy * scaleVec2.sy;
			return *this;
		}

		OdGeScale2d operator *(double factor) const
		{
			return OdGeScale2d(sx * factor, sy * factor);
		}

		OdGeScale2d& operator *=(double factor)
		{
			sx *= factor;
			sy *= factor;
			return *this;
		}

		OdGeScale2d inverse() const
		{
			return OdGeScale2d(1.0 / sx, 1.0 / sy);
		}

		OdGeScale2d& invert()
		{
			sx = 1.0 / sx;
			sy = 1.0 / sy;
			return *this;
		}

		bool isProportional() const
		{
			return (sx == sy);
		}

		bool operator ==(const OdGeScale2d& scaleVec) const
		{
			return (sx == scaleVec.sx && sy == scaleVec.sy);
		}

		bool operator !=(const OdGeScale2d& scaleVec) const
		{
			return !(*this == scaleVec);
		}

		bool isEqualTo(const OdGeScale2d& scaleVec, double tol = 1e-9) const
		{
			return (std::abs(sx - scaleVec.sx) <= tol && std::abs(sy - scaleVec.sy) <= tol);
		}

		double& operator [](unsigned int i)
		{
			return (i == 0) ? sx : sy;
		}

		double operator [](unsigned int i) const
		{
			return (i == 0) ? sx : sy;
		}

		OdGeScale2d& set(double xFactor, double yFactor)
		{
			sx = xFactor;
			sy = yFactor;
			return *this;
		}

		/// <summary>
		/// Set the matrix as a scaling matrix with sx and sy
		/// </summary>
		/// <param name="xfm"></param>
		void getMatrix(OdGeMatrix2d& xfm) const
		{
			xfm.setToIdentity();
			xfm(0, 0) = sx;
			xfm(1, 1) = sy;
		}

		/// <summary>
		/// Extract the scaling factors from the matrix
		/// </summary>
		/// <param name="xfm"></param>
		/// <returns></returns>
		OdGeScale2d& extractScale(const OdGeMatrix2d& xfm)
		{
			sx = xfm(0, 0);
			sy = xfm(1, 1);
			return *this;
		}

		/// <summary>
		/// Remove scaling from the matrix and set it to identity scale factors
		/// </summary>
		/// <param name="xfm"></param>
		/// <returns></returns>
		OdGeScale2d& removeScale(OdGeMatrix2d& xfm)
		{
			sx = xfm(0, 0);
			sy = xfm(1, 1);
			xfm(0, 0) = 1.0;
			xfm(1, 1) = 1.0;
			return *this;
		}

		operator OdGeMatrix2d() const
		{
			OdGeMatrix2d xfm;
			getMatrix(xfm);
			return xfm;
		}

		operator OdGeScale3d() const
		{
			return OdGeScale3d(sx, sy, 1.0);
		}

	private:
		double sx; // X scale factor.
		double sy; // Y scale factor.
	};

	// Define the identity scale vector
	const OdGeScale2d OdGeScale2d::kIdentity = OdGeScale2d(1.0, 1.0);
}
