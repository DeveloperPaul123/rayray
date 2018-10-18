#pragma once

namespace rayray::utilties::math
{
    double min(double x0, double x1);
    double max(double x0, double x1);
    int rand_int();
    float rand_float();
    void set_rand_seed(const int seed);
    float rand_float(int l, float h);
    int rand_int(int l, int h);
    double clamp(const double x, const double min, const double max);

    int solve_quadric(double c[3], double s[2]);
    int solve_cubic(double c[4], double s[3]);
    int solve_quartic(double c[5], double s[4]);
}