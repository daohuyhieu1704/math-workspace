#pragma once

using namespace System;

namespace MathGL
{
    public ref class DisposableWrapper abstract : IDisposable
    {
    private:
        bool autoDelete;
        IntPtr UnmanagedObject;
    public:
        DisposableWrapper(System::IntPtr UnmanagedObject, bool autoDelete)
            : UnmanagedObject(System::IntPtr(UnmanagedObject)), autoDelete(autoDelete) {
        };

        !DisposableWrapper()
        {
            if (autoDelete && UnmanagedObject != IntPtr::Zero)
            {
                delete UnmanagedObject.ToPointer();
                UnmanagedObject = IntPtr::Zero;
            }
        }

        virtual ~DisposableWrapper()
        {
            this->!DisposableWrapper();
        }

        void* GetImpObj()
        {
            return UnmanagedObject.ToPointer();
        };
    };
}

