#pragma once
#include "OdGeMatrix3d.h"
#include "OdGeScale3d.h"

using namespace GeometryNative;

namespace Geometry
{
    public value class Scale3d
    {
    private:
        double sx;
        double sy;
        double sz;

    public:
        // Constructors
        Scale3d(double xFactor, double yFactor, double zFactor);
        Scale3d(double uniformFactor);

        static initonly Scale3d Identity = Scale3d(1.0, 1.0, 1.0);

        // Properties
        property double XFactor
        {
            double get();
            void set(double value);
        }

        property double YFactor
        {
            double get();
            void set(double value);
        }

        property double ZFactor
        {
            double get();
            void set(double value);
        }

        // Conversion methods
        OdGeScale3d ToNative();
        static Scale3d FromNative(OdGeScale3d nativeScale);

        // Operations
        Scale3d operator*(Scale3d other);
        Scale3d operator*(double factor);
        static Scale3d operator*(double factor, Scale3d scale);
        bool operator==(Scale3d other);
        bool operator!=(Scale3d other);
        bool IsProportional(double tolerance);
        Scale3d Inverse();
        void Set(double xFactor, double yFactor, double zFactor);

        // Matrix representation
        void GetMatrix([System::Runtime::InteropServices::Out] array<double>^% matrix);

        // Equality checks
        bool IsEqualTo(Scale3d other);
        bool IsEqualTo(Scale3d other, double tolerance);

        // Validity
        bool IsValid();
    };
}
