#include "pch.h"
#include "Scale2d.h"

namespace Geometry
{
	OdGeScale2d Scale2d::ToNative()
	{
		return OdGeScale2d();
	}
	Scale2d Scale2d::FromNative(OdGeScale2d nativeScale)
	{
		return Scale2d(nativeScale[0], nativeScale[1]);
	}
	Scale2d Scale2d::operator*(Scale2d other)
	{
		OdGeScale2d result = this->ToNative() * other.ToNative();
		return FromNative(result);
	}
	Scale2d Scale2d::operator*(double factor)
	{
		OdGeScale2d result = this->ToNative() * factor;
		return FromNative(result);
	}
	Scale2d Scale2d::operator*(double factor, Scale2d scale)
	{
		return scale * factor;
	}
	bool Scale2d::operator==(Scale2d other)
	{
		return this->ToNative() == other.ToNative();
	}
	bool Scale2d::operator!=(Scale2d other)
	{
		return !(this->operator==(other));
	}
	bool Scale2d::IsProportional()
	{
		return sx == sy;
	}
	Scale2d Scale2d::Inverse()
	{
		OdGeScale2d result = this->ToNative().inverse();
		return FromNative(result);
	}
	void Scale2d::Set(double xFactor, double yFactor)
	{
		sx = xFactor;
		sy = yFactor;
	}
	void Scale2d::GetMatrix(array<double>^% matrix)
	{
		matrix = gcnew array<double>(4);
		matrix[0] = sx; // (0,0)
		matrix[1] = 0.0; // (0,1)
		matrix[2] = 0.0; // (1,0)
		matrix[3] = sy; // (1,1)
	}
	bool Scale2d::IsEqualTo(Scale2d other)
	{
		return IsEqualTo(other, 1e-9);
	}
	bool Scale2d::IsEqualTo(Scale2d other, double tolerance)
	{
		OdGeScale2d native = this->ToNative();
		OdGeScale2d otherNative = other.ToNative();
		return native.isEqualTo(otherNative, tolerance);
	}
}
