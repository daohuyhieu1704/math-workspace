#pragma once

#include <cmath> // for std::abs and other math operations
#include <stdexcept>
#include "OdGePoint3d.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GeometryNative
{
	class OdGeScale3d;
	class OdGePlane;
	class OdGeMatrix2d;
	class OdGeLine3d;
	class OdGeVector3d;
	class OdGeMatrix3d
	{
	public:
        // Default constructor
        OdGeMatrix3d();

        // Multiplicative identity matrix
        static const OdGeMatrix3d kIdentity;

        // Set matrix to identity
        OdGeMatrix3d& setToIdentity();

        // Validate zeros within a tolerance
        void validateZero(const double tol = 1e-6);

        // Operator overloads
        OdGeMatrix3d operator *(const OdGeMatrix3d& matrix) const;
        OdGeMatrix3d& operator *=(const OdGeMatrix3d& matrix);
        OdGeMatrix3d& preMultBy(const OdGeMatrix3d& leftSide);
        OdGeMatrix3d& postMultBy(const OdGeMatrix3d& rightSide);
        OdGeMatrix3d& setToProduct(const OdGeMatrix3d& matrix1, const OdGeMatrix3d& matrix2);

        // Invert matrix
        OdGeMatrix3d& invert();
        OdGeMatrix3d inverse() const;
        OdGeMatrix3d inverse(const double tol) const;
        bool inverse(OdGeMatrix3d& inverseMatrix, double tol) const;
        bool isSingular(const double tol = 1e-6) const;

        // Transpose matrix
        OdGeMatrix3d& transposeIt();
        OdGeMatrix3d transpose() const;

        // Comparison operators
        bool operator ==(const OdGeMatrix3d& matrix) const;
        bool operator !=(const OdGeMatrix3d& matrix) const;
        bool isEqualTo(const OdGeMatrix3d& matrix, const double tol = 1e-6) const;
        bool isUniScaledOrtho(const double tol = 1e-6) const;
        bool isScaledOrtho(const double tol = 1e-6) const;
        bool isPerspective(const double tol = 1e-6) const;

        // Determinant
        double det() const;

        // Set and get coordinate systems
        OdGeMatrix3d& setTranslation(const OdGeVector3d& vect);
        OdGeMatrix3d& setCoordSystem(const OdGePoint3d& origin,
            const OdGeVector3d& xAxis,
            const OdGeVector3d& yAxis,
            const OdGeVector3d& zAxis);
        void getCoordSystem(OdGePoint3d& origin,
            OdGeVector3d& xAxis,
            OdGeVector3d& yAxis,
            OdGeVector3d& zAxis) const;
        OdGePoint3d getCsOrigin() const;
        OdGeVector3d getCsXAxis() const;
        OdGeVector3d getCsYAxis() const;
        OdGeVector3d getCsZAxis() const;

        // Set to specific transformations
        OdGeMatrix3d& setToTranslation(const OdGeVector3d& vect);
        OdGeMatrix3d& setToRotation(double angle,
            const OdGeVector3d& axis,
            const OdGePoint3d& center = OdGePoint3d::kOrigin);
        OdGeMatrix3d& setToScaling(double scale,
            const OdGePoint3d& center = OdGePoint3d::kOrigin);
        OdGeMatrix3d& setToScaling(const OdGeScale3d& scale,
            const OdGePoint3d& center = OdGePoint3d::kOrigin);
        OdGeMatrix3d& setToMirroring(const OdGePlane& mirrorPlane);
        OdGeMatrix3d& setToMirroring(const OdGePoint3d& mirrorPoint);
        OdGeMatrix3d& setToMirroring(const OdGeLine3d& mirrorLine);
        OdGeMatrix3d& setToProjection(const OdGePlane& projectionPlane,
            const OdGeVector3d& projectDir);
        OdGeMatrix3d& setToAlignCoordSys(const OdGePoint3d& fromOrigin,
            const OdGeVector3d& fromXAxis,
            const OdGeVector3d& fromYAxis,
            const OdGeVector3d& fromZAxis,
            const OdGePoint3d& toOrigin,
            const OdGeVector3d& toXAxis,
            const OdGeVector3d& toYAxis,
            const OdGeVector3d& toZAxis);
        OdGeMatrix3d& setToWorldToPlane(const OdGeVector3d& normal);
        OdGeMatrix3d& setToWorldToPlane(const OdGePlane& plane);
        OdGeMatrix3d& setToPlaneToWorld(const OdGeVector3d& normal);
        OdGeMatrix3d& setToPlaneToWorld(const OdGePlane& plane);

        // Static methods for creating matrices
        static OdGeMatrix3d translation(const OdGeVector3d& vect);
        static OdGeMatrix3d rotation(const Quaternion3d& quad);
        static OdGeMatrix3d rotation(double angle,
            const OdGeVector3d& axis,
            const OdGePoint3d& center = OdGePoint3d::kOrigin);
        static OdGeMatrix3d scaling(double scale,
            const OdGePoint3d& center = OdGePoint3d::kOrigin);
        static OdGeMatrix3d scaling(const OdGeScale3d& scale,
            const OdGePoint3d& center = OdGePoint3d::kOrigin);
        static OdGeMatrix3d mirroring(const OdGePlane& mirrorPlane);
        static OdGeMatrix3d mirroring(const OdGePoint3d& mirrorPoint);
        static OdGeMatrix3d mirroring(const OdGeLine3d& mirrorLine);
        static OdGeMatrix3d projection(const OdGePlane& projectionPlane,
            const OdGeVector3d& projectDir);
        static OdGeMatrix3d alignCoordSys(const OdGePoint3d& fromOrigin,
            const OdGeVector3d& fromXAxis,
            const OdGeVector3d& fromYAxis,
            const OdGeVector3d& fromZAxis,
            const OdGePoint3d& toOrigin,
            const OdGeVector3d& toXAxis,
            const OdGeVector3d& toYAxis,
            const OdGeVector3d& toZAxis);
        static OdGeMatrix3d worldToPlane(const OdGeVector3d& normal);
        static OdGeMatrix3d worldToPlane(const OdGePlane& plane);
        static OdGeMatrix3d planeToWorld(const OdGeVector3d& normal);
        static OdGeMatrix3d planeToWorld(const OdGePlane& plane);

        double scale() const;
        double norm() const;
        OdGeMatrix2d convertToLocal(OdGeVector3d& normal, double& elevation) const;

        inline const double* operator [](int row) const { return entry[row]; }
        inline double* operator [](int row) { return entry[row]; }
        inline double operator ()(int row, int column) const { return entry[row][column]; }
        inline double& operator ()(int row, int column) { return entry[row][column]; }

        void setFromGLM(const glm::mat4& glmMatrix);
        double entry[4][4];
	};
}
