#include "pch.h"
#include "Scale3d.h"

namespace Geometry
{
    // Constructors
    Scale3d::Scale3d(double xFactor, double yFactor, double zFactor)
        : sx(xFactor), sy(yFactor), sz(zFactor) {
    }

    Scale3d::Scale3d(double uniformFactor)
        : sx(uniformFactor), sy(uniformFactor), sz(uniformFactor) {
    }

    // Properties
    double Scale3d::XFactor::get() { return sx; }
    void Scale3d::XFactor::set(double value) { sx = value; }

    double Scale3d::YFactor::get() { return sy; }
    void Scale3d::YFactor::set(double value) { sy = value; }

    double Scale3d::ZFactor::get() { return sz; }
    void Scale3d::ZFactor::set(double value) { sz = value; }

    // Convert to native
    OdGeScale3d Scale3d::ToNative()
    {
        return OdGeScale3d(sx, sy, sz);
    }

    // Convert from native
    Scale3d Scale3d::FromNative(OdGeScale3d nativeScale)
    {
        return Scale3d(nativeScale[0], nativeScale[1], nativeScale[2]);
    }

    // Operators
    Scale3d Scale3d::operator*(Scale3d other)
    {
        OdGeScale3d result = this->ToNative() * other.ToNative();
        return FromNative(result);
    }

    Scale3d Scale3d::operator*(double factor)
    {
        OdGeScale3d result = this->ToNative() * factor;
        return FromNative(result);
    }

    Scale3d Scale3d::operator*(double factor, Scale3d scale)
    {
        return scale * factor;
    }

    bool Scale3d::operator==(Scale3d other)
    {
        return this->ToNative() == other.ToNative();
    }

    bool Scale3d::operator!=(Scale3d other)
    {
        return !(this->operator==(other));
    }

    // Proportionality
    bool Scale3d::IsProportional(double tolerance)
    {
        return ToNative().isProportional(tolerance);
    }

    // Inverse scale
    Scale3d Scale3d::Inverse()
    {
        OdGeScale3d result = this->ToNative().inverse();
        return FromNative(result);
    }

    // Set values
    void Scale3d::Set(double xFactor, double yFactor, double zFactor)
    {
        sx = xFactor;
        sy = yFactor;
        sz = zFactor;
    }

    // Matrix representation
    void Scale3d::GetMatrix([System::Runtime::InteropServices::Out] array<double>^% matrix)
    {
        matrix = gcnew array<double>(9);
        matrix[0] = sx; // (0,0)
        matrix[1] = 0.0; // (0,1)
        matrix[2] = 0.0; // (0,2)
        matrix[3] = 0.0; // (1,0)
        matrix[4] = sy; // (1,1)
        matrix[5] = 0.0; // (1,2)
        matrix[6] = 0.0; // (2,0)
        matrix[7] = 0.0; // (2,1)
        matrix[8] = sz; // (2,2)
    }

    // Equality checks
    bool Scale3d::IsEqualTo(Scale3d other)
    {
        return IsEqualTo(other, 1e-9); // Default tolerance
    }

    bool Scale3d::IsEqualTo(Scale3d other, double tolerance)
    {
        OdGeScale3d native = this->ToNative();
        OdGeScale3d otherNative = other.ToNative();
        return native.isEqualTo(otherNative, tolerance);
    }

    // Validity check
    bool Scale3d::IsValid()
    {
        return ToNative().isValid();
    }
}
