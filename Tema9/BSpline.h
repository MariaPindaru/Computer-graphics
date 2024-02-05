#pragma once

#include "pch.h"
#include "vector"

double N( int i, int p, double t, const std::vector<double>& knots );

CPoint BSpline( double t, int degree, const std::vector<CPoint>& points );

// using De Boor algorithm
CPoint BSplineDeBoor( double t, int degree, const std::vector<CPoint>& points );