#pragma once
#include "OdGeMatrix3d.h"
#include <cmath> 

namespace Geometry
{
	class OdGeScale3d
	{
	public:
		/** \details
		  Default constructor for the OdGeScale3d class.

		  \remarks
		  Constructs the scale object with 1.0 for scale factor for each axis.
		*/
		OdGeScale3d() : sx(1.0), sy(1.0), sz(1.0) {}

		/** \details
		  Constructor for the OdGeScale3d class.

		  \param factor [in]  Uniform scale factor.

		  \remarks
		  The constructor constructs a unified scale factor with the specified double value.
		*/
		OdGeScale3d(double factor) : sx(factor), sy(factor), sz(factor) {}

		/** \details
		  Constructor for the OdGeScale3d class.

		  \param xFactor [in]  The X scale factor.
		  \param yFactor [in]  The Y scale factor.
		  \param zFactor [in]  The Z scale factor.

		  \remarks
		  The constructor constructs scale transformation with the specified factors for X, Y, Z axes.
		*/
		OdGeScale3d(double xFactor, double yFactor, double zFactor)
			: sx(xFactor), sy(yFactor), sz(zFactor) {}

		// Multiplicative identity vector.
		static const OdGeScale3d kIdentity;

		/// <summary>
		/// X scale factor.
		/// </summary>
		/// <param name="scaleVec"></param>
		/// <returns></returns>
		OdGeScale3d operator *(const OdGeScale3d& scaleVec) const;

		/// <summary>
		/// Multiply the scale vector by a factor.
		/// </summary>
		/// <param name="factor"></param>
		/// <returns></returns>
		OdGeScale3d operator *(double factor) const;

		/// <summary>
		/// Multiply the scale vector by a factor.
		/// </summary>
		/// <param name="factor"></param>
		/// <param name="scaleVec"></param>
		/// <returns></returns>
		friend OdGeScale3d operator *(double factor, const OdGeScale3d& scaleVec);

		/// <summary>
		/// Multiply the scale vector by another scale vector.
		/// </summary>
		/// <param name="scaleVec"></param>
		/// <returns></returns>
		OdGeScale3d& operator *=(const OdGeScale3d& scaleVec);

		/// <summary>
		/// Multiply the scale vector by a factor.
		/// </summary>
		/// <param name="factor"></param>
		/// <returns></returns>
		OdGeScale3d& operator *=(double factor);

		/// <summary>
		/// Set the scale vector to the product of two scale vectors.
		/// </summary>
		/// <param name="scaleVec1"></param>
		/// <param name="scaleVec2"></param>
		/// <returns></returns>
		OdGeScale3d& setToProduct(const OdGeScale3d& scaleVec1, const OdGeScale3d& scaleVec2);

		/// <summary>
		/// Set the scale vector to the product of the scale vector and a factor.
		/// </summary>
		/// <param name="scaleVec"></param>
		/// <param name="factor"></param>
		/// <returns></returns>
		OdGeScale3d& setToProduct(const OdGeScale3d& scaleVec, double factor);

		/// <summary>
		/// Get the inverse of the scale vector.
		/// </summary>
		/// <returns></returns>
		OdGeScale3d inverse() const;

		/// <summary>
		/// Invert the scale vector.
		/// </summary>
		/// <returns></returns>
		OdGeScale3d& invert();

		/// <summary>
		/// Check if the scale vector is proportional.
		/// </summary>
		/// <returns></returns>
		bool isProportional(double tolerance = 1e-9) const;

		/// <summary>
		/// Check if the scale vector is uniform.
		/// </summary>
		/// <param name="scaleVec"></param>
		/// <returns></returns>
		bool operator ==(const OdGeScale3d& scaleVec) const;

		/// <summary>
		/// Check if the scale vector is not uniform.
		/// </summary>
		/// <param name="scaleVec"></param>
		/// <returns></returns>
		bool operator !=(const OdGeScale3d& scaleVec) const;

		/// <summary>
		/// Check if the scale vector is equal to another scale vector.
		/// </summary>
		/// <param name="scaleVec"></param>
		/// <param name="tol"></param>
		/// <returns></returns>
		bool isEqualTo(const OdGeScale3d& scaleVec, double tol = 1e-9) const;

		/// <summary>
		/// Get the scale factor for the specified axis.
		/// </summary>
		/// <param name="i"></param>
		/// <returns></returns>
		double& operator [](unsigned int i);

		/// <summary>
		/// Get the scale factor for the specified axis.
		/// </summary>
		/// <param name="i"></param>
		/// <returns></returns>
		double operator [](unsigned int i) const;

		/// <summary>
		/// Set the scale factors for the X, Y, and Z axes.
		/// </summary>
		/// <param name="xFactor"></param>
		/// <param name="yFactor"></param>
		/// <param name="zFactor"></param>
		/// <returns></returns>
		OdGeScale3d& set(double xFactor, double yFactor, double zFactor);

		/// <summary>
		/// Get the scale factors for the X, Y, and Z axes.
		/// </summary>
		/// <param name="xfm"></param>
		void getMatrix(OdGeMatrix3d& xfm) const;

		/// <summary>
		/// Extract the scale factors from the matrix.
		/// </summary>
		/// <param name="xfm"></param>
		/// <returns></returns>
		OdGeScale3d& extractScale(const OdGeMatrix3d& xfm);

		/// <summary>
		/// Remove scaling from the matrix.
		/// </summary>
		/// <param name="xfm"></param>
		/// <param name="negateX"></param>
		/// <returns></returns>
		OdGeScale3d& removeScale(OdGeMatrix3d& xfm, bool negateX = false);

		/// <summary>
		/// Convert the scale vector to a matrix.
		/// </summary>
		operator OdGeMatrix3d() const;

		/// <summary>
		/// Check if the scale vector is valid.
		/// </summary>
		/// <returns></returns>
		bool isValid() const;

	private:
		double sx; // X scale factor.
		double sy; // Y scale factor.
		double sz; // Z scale factor.
	};
}