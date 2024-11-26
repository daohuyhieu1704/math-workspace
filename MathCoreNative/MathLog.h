#pragma once
#include "pch.h"
#include <fstream>
#include <filesystem>
#include<windows.h>
#include <chrono>
#include <string>
#include "OdGePoint3d.h"
#include "OdGePoint2d.h"
#include "OdGePlane.h"
#include "OdGeVector3d.h"

#define COMMA_SPACE ", "
#define OP_SHARP_BRACKET "{"
#define ED_SHARP_BRACKET "}"
#define OP_PARENTHESE "("
#define ED_PARENTHESE ")"

using namespace GeometryNative;

class MathLog
{
private:
    ////log/
    static std::string CreateIndent(int IndentLevel)
    {
        std::string Indent = "";
        for (int i = 0; i < IndentLevel; i++)
        {
            Indent += "\t";
        }
        return Indent;
    }
    static std::string GetParamString()
    {
        return "";
    }
    static std::string GetStringValue(const OdGePoint3d point3d, int IndentLevel)
    {
        std::string IndentStr = CreateIndent(IndentLevel);
        IndentLevel++;

        std::string ret = IndentStr + "OdGePoint3d: { " + std::to_string(point3d.x) + COMMA_SPACE + std::to_string(point3d.y) + COMMA_SPACE + std::to_string(point3d.z) + " }";
        return ret;
    }
    static std::string GetStringValue(const OdGePoint2d point2d, int IndentLevel)
    {
        std::string IndentStr = CreateIndent(IndentLevel);
        IndentLevel++;

        std::string ret = IndentStr + "OdGePoint2d: { " + std::to_string(point2d.x) + COMMA_SPACE + std::to_string(point2d.y) + " }";
        return ret;
    }

    static std::string GetStringValue(const OdGePlane& plane, int IndentLevel)
    {
        std::string IndentStr = CreateIndent(IndentLevel);
        IndentLevel++;

        // Format the string with the plane's origin and normal
        std::string ret = IndentStr + "OdGePlane: \n" + OP_SHARP_BRACKET + "\n";
        ret += IndentStr + "\tOrigin: " + GetStringValue(plane.m_origin, IndentLevel) + "\n";
        ret += IndentStr + "\tNormal: " + GetStringValue(plane.m_normal, IndentLevel) + "\n";
        ret += IndentStr + ED_SHARP_BRACKET;
        return ret;
    }

    static std::string GetStringValue(const OdGeVector3d& vector3d, int IndentLevel)
    {
        std::string IndentStr = CreateIndent(IndentLevel);
        std::string ret = IndentStr + "OdGeVector3d: { " +
            std::to_string(vector3d.x) + COMMA_SPACE +
            std::to_string(vector3d.y) + COMMA_SPACE +
            std::to_string(vector3d.z) + " }";
        return ret;
    }

    static std::string GetStringValue(const double num, int IndentLevel)
    {
        std::string IndentStr = CreateIndent(IndentLevel);
        return IndentStr + "double: " + std::to_string(num);
    }
    static std::string GetStringValue(const int num, int IndentLevel)
    {
        std::string IndentStr = CreateIndent(IndentLevel);
        return IndentStr + "int: " + std::to_string(num);
    }
    static std::string GetStringValue(const bool isTrue, int IndentLevel)
    {
        std::string IndentStr = CreateIndent(IndentLevel);
        return IndentStr + "bool: " + (isTrue ? "true" : "false");
    }

    static std::string GetStringValue(const void* pnt, int IndentLevel)
    {
        std::string IndentStr = CreateIndent(IndentLevel);
        return IndentStr + "void*: " + std::to_string((int)pnt);
    }

    template<typename T, typename... Args>
    static std::string GetParamString(T printvalue, Args... rest)
    {
        std::string ret = "";
        ret += "\n";
        ret += GetStringValue(printvalue, 1);
        ret += GetParamString(rest...);
        return ret;
    }
public:
    template<typename... Args>
    static void LogFunction(std::string functionname, Args... args)
    {

        std::string content;
        content += functionname + "\n{";
        content += GetParamString(args...);
        content += "\n}\n";

        std::time_t t = std::time(0);
        std::tm now;
        localtime_s(&now, &t);
        std::string datestr = std::to_string(now.tm_year + 1900) + "-" + std::to_string(now.tm_mon + 1) + "-" + std::to_string(now.tm_mday);
        std::string timestr = "[" + std::to_string(now.tm_hour) + ":" + std::to_string(now.tm_min) + ":" + std::to_string(now.tm_sec) + "]\n";


        char* PathChr;
        size_t PathSize;
        _dupenv_s(&PathChr, &PathSize, "localappdata");
        if (PathChr == nullptr)
        {
            return;
        }
        std::string PathStr(PathChr);
        PathStr += "\\MathLog";

        std::wstring stemp = std::wstring(PathStr.begin(), PathStr.end());
        LPCWSTR sw = stemp.c_str();
        CreateDirectoryW(sw, NULL);

        content = timestr + content;

        PathStr += "\\" + datestr + ".log";
        std::ofstream fout;
        fout.open(PathStr, std::ios::out | std::ios::app);
        fout << content;
        fout.close();
    }
};
