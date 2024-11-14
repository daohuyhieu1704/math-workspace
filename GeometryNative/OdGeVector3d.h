#pragma once
namespace GeometryNative
{
	class OdGeVector3d
	{
	public:
		static const OdGeVector3d kXAxis;
		static const OdGeVector3d kYAxis;
		static const OdGeVector3d kZAxis;

		OdGeVector3d();
		OdGeVector3d(double x, double y, double z);
		~OdGeVector3d();

		double Length() const;
		OdGeVector3d Normalize() const;
		OdGeVector3d CrossProduct(const OdGeVector3d& other) const;
		double DotProduct(const OdGeVector3d& other) const;

		OdGeVector3d operator-() const;
		void operator+=(const OdGeVector3d& other);
		void operator-=(const OdGeVector3d& other);
		OdGeVector3d operator+(const OdGeVector3d& other) const;
		OdGeVector3d operator-(const OdGeVector3d& other) const;
		OdGeVector3d operator*(double scalar) const;
		OdGeVector3d operator/=(const double scale);

		bool IsEqual(const OdGeVector3d& other) const;

		double x;
		double y;
		double z;
	};
}
