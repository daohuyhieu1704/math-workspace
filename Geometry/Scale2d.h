#pragma once
#include <OdGeMatrix2d.h>
#include <OdGeScale3d.h>
#include <OdGeScale2d.h>

using namespace GeometryNative;

namespace Geometry
{
    public value class Scale2d
    {
    private:
        double sx;
        double sy;

    public:
        // Constructors
        Scale2d(double xFactor, double yFactor) : sx(xFactor), sy(yFactor) {}
        Scale2d(double uniformFactor) : sx(uniformFactor), sy(uniformFactor) {}
        static initonly Scale2d Identity = Scale2d(1.0, 1.0);
        property double XFactor
        {
            double get() { return sx; }
            void set(double value) { sx = value; }
        }

        property double YFactor
        {
            double get() { return sy; }
            void set(double value) { sy = value; }
        }

        OdGeScale2d ToNative();
        static Scale2d FromNative(OdGeScale2d nativeScale);
        Scale2d operator*(Scale2d other);
        Scale2d operator*(double factor);
        static Scale2d operator*(double factor, Scale2d scale);
        bool operator==(Scale2d other);
        bool operator!=(Scale2d other);
        bool IsProportional();
        Scale2d Inverse();
        void Set(double xFactor, double yFactor);
        void GetMatrix([System::Runtime::InteropServices::Out] array<double>^% matrix);
        bool IsEqualTo(Scale2d other);
        bool IsEqualTo(Scale2d other, double tolerance);
    };
}
