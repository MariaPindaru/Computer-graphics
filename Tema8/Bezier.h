#pragma once

#include "pch.h"

#include <vector>

unsigned long long Factorial( int n );

double Combination( int n, int k );

CPoint Bezier( double t, const std::vector<CPoint>& controlPoints );