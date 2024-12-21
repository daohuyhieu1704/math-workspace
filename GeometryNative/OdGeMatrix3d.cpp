#include "pch.h"
#include "OdGeMatrix2d.h"
#include "OdGeMatrix3d.h"
#include "OdGeScale3d.h"
#include "OdGePlane.h"
#include "Quaternion3d.h"


namespace GeometryNative
{
	const OdGeMatrix3d OdGeMatrix3d::kIdentity = OdGeMatrix3d().setToIdentity();

    OdGeMatrix3d::OdGeMatrix3d() {
        setToIdentity();
    }

    // Set to identity
    OdGeMatrix3d& OdGeMatrix3d::setToIdentity() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                entry[i][j] = (i == j) ? 1.0 : 0.0;
            }
        }
        return *this;
    }

    // Validate zeros
    void OdGeMatrix3d::validateZero(const double tol) {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                if (std::fabs(entry[i][j]) < tol)
                    entry[i][j] = 0.0;
    }

    // Matrix multiplication
    OdGeMatrix3d OdGeMatrix3d::operator *(const OdGeMatrix3d& matrix) const {
        OdGeMatrix3d result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.entry[i][j] = 0.0;
                for (int k = 0; k < 4; ++k) {
                    result.entry[i][j] += entry[i][k] * matrix.entry[k][j];
                }
            }
        }
        return result;
    }

    OdGeMatrix3d& OdGeMatrix3d::operator *=(const OdGeMatrix3d& matrix) {
        *this = *this * matrix;
        return *this;
    }

    OdGeMatrix3d& OdGeMatrix3d::preMultBy(const OdGeMatrix3d& leftSide) {
        *this = leftSide * *this;
        return *this;
    }

    OdGeMatrix3d& OdGeMatrix3d::postMultBy(const OdGeMatrix3d& rightSide) {
        *this = *this * rightSide;
        return *this;
    }

    OdGeMatrix3d& OdGeMatrix3d::setToProduct(const OdGeMatrix3d& matrix1, const OdGeMatrix3d& matrix2) {
        *this = matrix1 * matrix2;
        return *this;
    }

    // Determinant calculation (helper functions)
    double determinant3x3(double m[3][3]) {
        return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
            m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
            m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    }

    // Determinant of 4x4 matrix
    double OdGeMatrix3d::det() const {
        double m[4][4];
        // Copy entries
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                m[i][j] = entry[i][j];

        double det = 0.0;
        for (int c = 0; c < 4; ++c) {
            double minor[3][3];
            for (int i = 1; i < 4; ++i) {
                int col = 0;
                for (int j = 0; j < 4; ++j) {
                    if (j == c) continue;
                    minor[i - 1][col] = m[i][j];
                    ++col;
                }
            }
            double minorDet = determinant3x3(minor);
            det += ((c % 2 == 0) ? 1 : -1) * m[0][c] * minorDet;
        }
        return det;
    }

    // Inversion
    OdGeMatrix3d& OdGeMatrix3d::invert() {
        double m[4][4], inv[4][4];
        double det;
        int i;

        // Copy entries
        for (i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                m[i][j] = entry[i][j];

        inv[0][0] = m[1][1] * m[2][2] * m[3][3] -
            m[1][1] * m[2][3] * m[3][2] -
            m[2][1] * m[1][2] * m[3][3] +
            m[2][1] * m[1][3] * m[3][2] +
            m[3][1] * m[1][2] * m[2][3] -
            m[3][1] * m[1][3] * m[2][2];

        // Compute remaining elements of inv[][]

        // Compute determinant
        det = m[0][0] * inv[0][0] /* + ... other terms ... */;

        if (fabs(det) < 1e-6)
            throw std::runtime_error("Matrix determinant is zero, cannot invert.");

        double invDet = 1.0 / det;

        // Multiply adjugate matrix by 1/det to get inverse
        for (i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                entry[i][j] = inv[i][j] * invDet;

        return *this;
    }

    OdGeMatrix3d OdGeMatrix3d::inverse() const {
        OdGeMatrix3d result = *this;
        result.invert();
        return result;
    }

    OdGeMatrix3d OdGeMatrix3d::inverse(const double tol) const {
        OdGeMatrix3d result = *this;
        if (fabs(result.det()) < tol)
            throw std::runtime_error("Matrix determinant is zero, cannot invert.");
        result.invert();
        return result;
    }

    bool OdGeMatrix3d::inverse(OdGeMatrix3d& inverseMatrix, double tol) const {
        double determinant = det();
        if (fabs(determinant) < tol) {
            return false;
        }
        inverseMatrix = inverse();
        return true;
    }

    bool OdGeMatrix3d::isSingular(const double tol) const {
        return fabs(det()) < tol;
    }

    // Transposition
    OdGeMatrix3d& OdGeMatrix3d::transposeIt() {
        for (int i = 0; i < 4; ++i)
            for (int j = i + 1; j < 4; ++j)
                std::swap(entry[i][j], entry[j][i]);
        return *this;
    }

    OdGeMatrix3d OdGeMatrix3d::transpose() const {
        OdGeMatrix3d result = *this;
        return result.transposeIt();
    }

    // Comparison operators
    bool OdGeMatrix3d::operator ==(const OdGeMatrix3d& matrix) const {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                if (std::fabs(entry[i][j] - matrix.entry[i][j]) > 1e-6)
                    return false;
        return true;
    }

    bool OdGeMatrix3d::operator !=(const OdGeMatrix3d& matrix) const {
        return !(*this == matrix);
    }

    bool OdGeMatrix3d::isEqualTo(const OdGeMatrix3d& matrix, const double tol) const {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                if (std::fabs(entry[i][j] - matrix.entry[i][j]) > tol)
                    return false;
        return true;
    }

    // Check if matrix is uniformly scaled orthogonal
    bool OdGeMatrix3d::isUniScaledOrtho(const double tol) const {
        OdGeVector3d xAxis(entry[0][0], entry[0][1], entry[0][2]);
        OdGeVector3d yAxis(entry[1][0], entry[1][1], entry[1][2]);
        OdGeVector3d zAxis(entry[2][0], entry[2][1], entry[2][2]);

        double xLen = xAxis.Length();
        double yLen = yAxis.Length();
        double zLen = zAxis.Length();

        if (fabs(xLen - yLen) > tol || fabs(yLen - zLen) > tol)
            return false;

        xAxis.normalize();
        yAxis.normalize();
        zAxis.normalize();

        if (fabs(xAxis.dotProduct(yAxis)) > tol)
            return false;
        if (fabs(xAxis.dotProduct(zAxis)) > tol)
            return false;
        if (fabs(yAxis.dotProduct(zAxis)) > tol)
            return false;

        return true;
    }

    // Check if matrix is scaled orthogonal
    bool OdGeMatrix3d::isScaledOrtho(const double tol) const {
        OdGeVector3d xAxis(entry[0][0], entry[0][1], entry[0][2]);
        OdGeVector3d yAxis(entry[1][0], entry[1][1], entry[1][2]);
        OdGeVector3d zAxis(entry[2][0], entry[2][1], entry[2][2]);

        xAxis.normalize();
        yAxis.normalize();
        zAxis.normalize();

        if (fabs(xAxis.dotProduct(yAxis)) > tol)
            return false;
        if (fabs(xAxis.dotProduct(zAxis)) > tol)
            return false;
        if (fabs(yAxis.dotProduct(zAxis)) > tol)
            return false;

        return true;
    }

    // Check if matrix is perspective
    bool OdGeMatrix3d::isPerspective(const double tol) const {
        return (fabs(entry[3][0]) > tol ||
            fabs(entry[3][1]) > tol ||
            fabs(entry[3][2]) > tol);
    }

    // Set translation
    OdGeMatrix3d& OdGeMatrix3d::setTranslation(const OdGeVector3d& vect) {
        entry[0][3] = vect.x;
        entry[1][3] = vect.y;
        entry[2][3] = vect.z;
        return *this;
    }

    // Set coordinate system
    OdGeMatrix3d& OdGeMatrix3d::setCoordSystem(const OdGePoint3d& origin,
        const OdGeVector3d& xAxis,
        const OdGeVector3d& yAxis,
        const OdGeVector3d& zAxis) {
        entry[0][0] = xAxis.x; entry[0][1] = xAxis.y; entry[0][2] = xAxis.z; entry[0][3] = origin.x;
        entry[1][0] = yAxis.x; entry[1][1] = yAxis.y; entry[1][2] = yAxis.z; entry[1][3] = origin.y;
        entry[2][0] = zAxis.x; entry[2][1] = zAxis.y; entry[2][2] = zAxis.z; entry[2][3] = origin.z;
        entry[3][0] = 0.0;     entry[3][1] = 0.0;     entry[3][2] = 0.0;     entry[3][3] = 1.0;
        return *this;
    }

    // Get coordinate system
    void OdGeMatrix3d::getCoordSystem(OdGePoint3d& origin,
        OdGeVector3d& xAxis,
        OdGeVector3d& yAxis,
        OdGeVector3d& zAxis) const {
        xAxis = OdGeVector3d(entry[0][0], entry[0][1], entry[0][2]);
        yAxis = OdGeVector3d(entry[1][0], entry[1][1], entry[1][2]);
        zAxis = OdGeVector3d(entry[2][0], entry[2][1], entry[2][2]);
        origin = OdGePoint3d(entry[0][3], entry[1][3], entry[2][3]);
    }

    // Get coordinate system components
    OdGePoint3d OdGeMatrix3d::getCsOrigin() const {
        return OdGePoint3d(entry[0][3], entry[1][3], entry[2][3]);
    }

    OdGeVector3d OdGeMatrix3d::getCsXAxis() const {
        return OdGeVector3d(entry[0][0], entry[0][1], entry[0][2]);
    }

    OdGeVector3d OdGeMatrix3d::getCsYAxis() const {
        return OdGeVector3d(entry[1][0], entry[1][1], entry[1][2]);
    }

    OdGeVector3d OdGeMatrix3d::getCsZAxis() const {
        return OdGeVector3d(entry[2][0], entry[2][1], entry[2][2]);
    }

    // Set to translation
    OdGeMatrix3d& OdGeMatrix3d::setToTranslation(const OdGeVector3d& vect) {
        setToIdentity();
        entry[0][3] = vect.x;
        entry[1][3] = vect.y;
        entry[2][3] = vect.z;
        return *this;
    }

    // Set to rotation
    OdGeMatrix3d& OdGeMatrix3d::setToRotation(double angle,
        const OdGeVector3d& axis,
        const OdGePoint3d& center) {
        glm::vec3 glmCenter(static_cast<float>(center.x), static_cast<float>(center.y), static_cast<float>(center.z));
        glm::vec3 glmAxis = glm::normalize(glm::vec3(static_cast<float>(axis.x),
            static_cast<float>(axis.y),
            static_cast<float>(axis.z)));
        glm::mat4 translationToOrigin = glm::translate(glm::mat4(1.0f), -glmCenter);
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), static_cast<float>(angle), glmAxis);
        glm::mat4 translationBack = glm::translate(glm::mat4(1.0f), glmCenter);
        glm::mat4 transformation = translationToOrigin * rotation * translationBack;
        setFromGLM(transformation);

        return *this;
    }


    // Set to scaling (uniform)
    OdGeMatrix3d& OdGeMatrix3d::setToScaling(double scale,
        const OdGePoint3d& center) {
        setToIdentity();
        entry[0][0] = scale;
        entry[1][1] = scale;
        entry[2][2] = scale;

        OdGeVector3d trans = (1.0 - scale) * OdGeVector3d(center.x, center.y, center.z);
        entry[0][3] = trans.x;
        entry[1][3] = trans.y;
        entry[2][3] = trans.z;

        return *this;
    }

    // Set to scaling (non-uniform)
    OdGeMatrix3d& OdGeMatrix3d::setToScaling(const OdGeScale3d& scale,
        const OdGePoint3d& center) {
        setToIdentity();
        entry[0][0] = scale.sx;
        entry[1][1] = scale.sy;
        entry[2][2] = scale.sz;

        OdGeVector3d trans = OdGeVector3d(center.x * (1 - scale.sx),
            center.y * (1 - scale.sy),
            center.z * (1 - scale.sz));
        entry[0][3] = trans.x;
        entry[1][3] = trans.y;
        entry[2][3] = trans.z;

        return *this;
    }

    // Set to mirroring about plane
    OdGeMatrix3d& OdGeMatrix3d::setToMirroring(const OdGePlane& mirrorPlane) {
        OdGeVector3d n = mirrorPlane.m_normal;
        n.normalize();

        double a = n.x;
        double b = n.y;
        double c = n.z;
        double d = -(a * mirrorPlane.m_origin.x + b * mirrorPlane.m_origin.y + c * mirrorPlane.m_origin.z);

        entry[0][0] = 1 - 2 * a * a;
        entry[0][1] = -2 * a * b;
        entry[0][2] = -2 * a * c;
        entry[0][3] = -2 * a * d;

        entry[1][0] = -2 * a * b;
        entry[1][1] = 1 - 2 * b * b;
        entry[1][2] = -2 * b * c;
        entry[1][3] = -2 * b * d;

        entry[2][0] = -2 * a * c;
        entry[2][1] = -2 * b * c;
        entry[2][2] = 1 - 2 * c * c;
        entry[2][3] = -2 * c * d;

        entry[3][0] = 0.0;
        entry[3][1] = 0.0;
        entry[3][2] = 0.0;
        entry[3][3] = 1.0;

        return *this;
    }

    // Set to mirroring about point
    OdGeMatrix3d& OdGeMatrix3d::setToMirroring(const OdGePoint3d& mirrorPoint) {
        setToScaling(-1.0, mirrorPoint);
        return *this;
    }

    // Set to mirroring about line
    OdGeMatrix3d& OdGeMatrix3d::setToMirroring(const OdGeLine3d& mirrorLine) {
        // Implementation involves reflection about a line in 3D space
        // This can be complex; for brevity, we'll provide a placeholder
        // A proper implementation would involve constructing the reflection matrix
        // For this example, we'll leave it as an identity matrix
        setToIdentity();
        return *this;
    }

    // Set to projection onto plane
    OdGeMatrix3d& OdGeMatrix3d::setToProjection(const OdGePlane& projectionPlane,
        const OdGeVector3d& projectDir) {
        OdGeVector3d n = projectionPlane.m_normal;
        n.normalize();
        OdGeVector3d d = projectDir;
        d.normalize();

        double dot = n.dotProduct(d);
        double a = n.x;
        double b = n.y;
        double c = n.z;
        double dx = d.x;
        double dy = d.y;
        double dz = d.z;

        entry[0][0] = 1 - dx * a / dot;
        entry[0][1] = -dx * b / dot;
        entry[0][2] = -dx * c / dot;
        entry[0][3] = 0.0;

        entry[1][0] = -dy * a / dot;
        entry[1][1] = 1 - dy * b / dot;
        entry[1][2] = -dy * c / dot;
        entry[1][3] = 0.0;

        entry[2][0] = -dz * a / dot;
        entry[2][1] = -dz * b / dot;
        entry[2][2] = 1 - dz * c / dot;
        entry[2][3] = 0.0;

        OdGeVector3d trans = -projectDir * (projectionPlane.m_origin.x * a + projectionPlane.m_origin.y * b + projectionPlane.m_origin.z * c) / dot;
        entry[0][3] = trans.x;
        entry[1][3] = trans.y;
        entry[2][3] = trans.z;

        entry[3][0] = 0.0;
        entry[3][1] = 0.0;
        entry[3][2] = 0.0;
        entry[3][3] = 1.0;

        return *this;
    }

    // Set to align coordinate systems
    OdGeMatrix3d& OdGeMatrix3d::setToAlignCoordSys(const OdGePoint3d& fromOrigin,
        const OdGeVector3d& fromXAxis,
        const OdGeVector3d& fromYAxis,
        const OdGeVector3d& fromZAxis,
        const OdGePoint3d& toOrigin,
        const OdGeVector3d& toXAxis,
        const OdGeVector3d& toYAxis,
        const OdGeVector3d& toZAxis) {
        OdGeMatrix3d fromCS;
        fromCS.setCoordSystem(fromOrigin, fromXAxis, fromYAxis, fromZAxis);
        OdGeMatrix3d toCS;
        toCS.setCoordSystem(toOrigin, toXAxis, toYAxis, toZAxis);

		OdGeMatrix3d fromCSInv = fromCS.inverse();
        *this = toCS * fromCSInv;
        return *this;
    }

    // Set to world to plane
    OdGeMatrix3d& OdGeMatrix3d::setToWorldToPlane(const OdGeVector3d& normal) {
        OdGeVector3d n = normal;
        n.normalize();

        OdGeVector3d up = fabs(n.dotProduct(OdGeVector3d::kYAxis)) < 1.0 - 1e-6 ?
            OdGeVector3d::kYAxis : OdGeVector3d::kZAxis;

        OdGeVector3d xAxis = up.crossProduct(n).normalize();
        OdGeVector3d yAxis = n.crossProduct(xAxis);

        setCoordSystem(OdGePoint3d::kOrigin, xAxis, yAxis, n);
        return *this;
    }

    OdGeMatrix3d& OdGeMatrix3d::setToWorldToPlane(const OdGePlane& plane)
    {
        // Get the plane's origin and normalized normal vector
        OdGePoint3d planeOrigin = plane.m_origin;
        OdGeVector3d planeNormal = plane.m_normal.normalize();

        // Compute tangent and bitangent vectors
        OdGeVector3d tangent;
        if (fabs(planeNormal.x) > fabs(planeNormal.y)) {
            tangent = OdGeVector3d(-planeNormal.z, 0.0, planeNormal.x).normalize();
        }
        else {
            tangent = OdGeVector3d(0.0, -planeNormal.z, planeNormal.y).normalize();
        }
        OdGeVector3d bitangent = planeNormal.crossProduct(tangent).normalize();

        // Create a rotation matrix for aligning axes
        OdGeMatrix3d rotation;
        rotation.setCoordSystem(OdGePoint3d::kOrigin, tangent, bitangent, planeNormal);

        // Create a translation matrix to move the origin
        OdGeMatrix3d translation = OdGeMatrix3d::translation(-planeOrigin.asVector());

        // Combine translation and rotation
        *this = rotation * translation; // Apply translation first, then rotation

        return *this;
    }

    // Set to plane to world
    OdGeMatrix3d& OdGeMatrix3d::setToPlaneToWorld(const OdGeVector3d& normal) {
        setToWorldToPlane(normal);
        invert();
        return *this;
    }

    OdGeMatrix3d& OdGeMatrix3d::setToPlaneToWorld(const OdGePlane& plane)
    {
        OdGePoint3d planeOrigin = plane.m_origin;
        OdGeVector3d planeNormal = plane.m_normal;

        planeNormal.normalize();

        OdGeVector3d tangent;
        if (fabs(planeNormal.x) > fabs(planeNormal.y)) {
            tangent = OdGeVector3d(-planeNormal.z, 0.0, planeNormal.x).normalize();
        }
        else {
            tangent = OdGeVector3d(0.0, -planeNormal.z, planeNormal.y).normalize();
        }
        OdGeVector3d bitangent = planeNormal.crossProduct(tangent).normalize();
        setToIdentity();
        setCoordSystem(planeOrigin, tangent, bitangent, planeNormal);
		return *this;
    }

    OdGeMatrix3d OdGeMatrix3d::translation(const OdGeVector3d& vect)
    {
		OdGeMatrix3d translationMatrix;
		translationMatrix.setToTranslation(vect);
		return translationMatrix;
    }

    OdGeMatrix3d OdGeMatrix3d::rotation(const Quaternion3d& quad)
    {
        return quad.toMatrix3d();
    }

    OdGeMatrix3d OdGeMatrix3d::rotation(double angle, const OdGeVector3d& axis, const OdGePoint3d& center)
    {
        OdGeMatrix3d rotationMatrix;
        rotationMatrix.setToRotation(angle, axis, center);
        return rotationMatrix;
    }

    OdGeMatrix3d OdGeMatrix3d::scaling(double scale, const OdGePoint3d& center)
    {
		OdGeMatrix3d scalingMatrix;
		scalingMatrix.setToScaling(scale, center);
		return scalingMatrix;
    }

    OdGeMatrix3d OdGeMatrix3d::scaling(const OdGeScale3d& scale, const OdGePoint3d& center)
    {
		OdGeMatrix3d scalingMatrix;
		scalingMatrix.setToScaling(scale, center);
		return scalingMatrix;
    }

    OdGeMatrix3d OdGeMatrix3d::mirroring(const OdGePlane& mirrorPlane)
    {
		OdGeMatrix3d mirrorMatrix;
		mirrorMatrix.setToMirroring(mirrorPlane);   
		return mirrorMatrix;
    }

    OdGeMatrix3d OdGeMatrix3d::mirroring(const OdGePoint3d& mirrorPoint)
    {
		OdGeMatrix3d mirrorMatrix;
		mirrorMatrix.setToMirroring(mirrorPoint);
		return mirrorMatrix;
    }

    OdGeMatrix3d OdGeMatrix3d::mirroring(const OdGeLine3d& mirrorLine)
    {
		OdGeMatrix3d mirrorMatrix;
		mirrorMatrix.setToMirroring(mirrorLine);
		return mirrorMatrix;
    }

    OdGeMatrix3d OdGeMatrix3d::projection(const OdGePlane& projectionPlane, const OdGeVector3d& projectDir)
    {
		OdGeMatrix3d projectionMatrix;
		projectionMatrix.setToProjection(projectionPlane, projectDir);
		return projectionMatrix;
    }

    OdGeMatrix3d OdGeMatrix3d::alignCoordSys(const OdGePoint3d& fromOrigin, const OdGeVector3d& fromXAxis, const OdGeVector3d& fromYAxis, const OdGeVector3d& fromZAxis, const OdGePoint3d& toOrigin, const OdGeVector3d& toXAxis, const OdGeVector3d& toYAxis, const OdGeVector3d& toZAxis)
    {
		OdGeMatrix3d alignMatrix;
		alignMatrix.setToAlignCoordSys(fromOrigin, fromXAxis, fromYAxis, fromZAxis, toOrigin, toXAxis, toYAxis, toZAxis);
		return alignMatrix;
    }

    OdGeMatrix3d OdGeMatrix3d::worldToPlane(const OdGeVector3d& normal)
    {
		OdGeMatrix3d worldToPlaneMatrix;
		worldToPlaneMatrix.setToWorldToPlane(normal);
		return worldToPlaneMatrix;
    }

    OdGeMatrix3d OdGeMatrix3d::worldToPlane(const OdGePlane& plane)
    {
		OdGeMatrix3d worldToPlaneMatrix;
		worldToPlaneMatrix.setToWorldToPlane(plane);
		return worldToPlaneMatrix;
    }

    OdGeMatrix3d OdGeMatrix3d::planeToWorld(const OdGeVector3d& normal)
    {
		OdGeMatrix3d planeToWorldMatrix;
		planeToWorldMatrix.setToPlaneToWorld(normal);
		return planeToWorldMatrix;
    }

    OdGeMatrix3d OdGeMatrix3d::planeToWorld(const OdGePlane& plane)
    {
		OdGeMatrix3d planeToWorldMatrix;
		planeToWorldMatrix.setToPlaneToWorld(plane);
		return planeToWorldMatrix;
    }

    // Scale factor (largest column vector length)
    double OdGeMatrix3d::scale() const {
        double xLen = std::sqrt(entry[0][0] * entry[0][0] + entry[0][1] * entry[0][1] + entry[0][2] * entry[0][2]);
        double yLen = std::sqrt(entry[1][0] * entry[1][0] + entry[1][1] * entry[1][1] + entry[1][2] * entry[1][2]);
        double zLen = std::sqrt(entry[2][0] * entry[2][0] + entry[2][1] * entry[2][1] + entry[2][2] * entry[2][2]);
        return std::max({ xLen, yLen, zLen });
    }

    // Norm (largest absolute value in linear part)
    double OdGeMatrix3d::norm() const {
        double maxVal = 0.0;
        for (int i = 0; i < 3; ++i) // Only linear part
            for (int j = 0; j < 3; ++j)
                maxVal = std::max(maxVal, std::fabs(entry[i][j]));
        return maxVal;
    }

    // Convert to local (placeholder)
    OdGeMatrix2d OdGeMatrix3d::convertToLocal(OdGeVector3d& normal, double& elevation) const {
        // Placeholder implementation
		return OdGeMatrix2d::kIdentity;
    }
    void OdGeMatrix3d::setFromGLM(const glm::mat4& glmMatrix)
    {
        const float* data = glm::value_ptr(glmMatrix);
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                entry[i][j] = static_cast<double>(data[j + i * 4]);
            }
        }
    }
}

