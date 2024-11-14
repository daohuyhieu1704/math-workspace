#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

#define OD_T(x) ( (const unsigned short*)__OD_T(x))
#define __OD_T(x) L ## x

typedef unsigned long OdUInt32;

inline bool OdPositive(double x, double tol = 1.e-10)
{
	return (x > tol);
}

inline bool OdNegative(double x, double tol = 1.e-10)
{
	return (x < -tol);
}

inline bool OdNonZero(double x, double tol = 1.e-10)
{
	return OdPositive(x, tol) || OdNegative(x, tol);
}