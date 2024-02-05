#pragma once

#include <vector>

std::vector<double> ComputeNewtonCoefficients( const std::vector<double>& x, const std::vector<double>& y );

double NewtonInterpolation( const std::vector<double>& x, const std::vector<double>& coefficients, double xInterpolate );