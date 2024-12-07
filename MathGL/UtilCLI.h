#pragma once
#include <string>
#include <msclr/marshal_cppstd.h>
#include <vcclr.h>

namespace MathGL
{
    public ref class UtilCLI
    {
    protected public:
        static std::string convertToStdString(System::String^ managedString) {
            if (managedString == nullptr) return "";
            const char* chars =
                (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(managedString)).ToPointer();
            std::string result(chars);
            System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr((void*)chars));
            return result;
        }
    };
}

