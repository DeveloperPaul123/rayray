#include "raytracer/utilities/math.h"
#include "raytracer/utilities/constants.h"
#include <cstdlib>
#include <cmath>

#ifndef M_PI
#define M_PI PI
#endif

// You may have to experiment with EQN_EPS
// The original was 1e-9, but I use 1e-90  KS Dec 3, 2007

//#define     EQN_EPS     1e-9  
//#define     EQN_EPS     1e-30
//#define     EQN_EPS     1e-60
#define     EQN_EPS     1e-90

#define	IsZero(x)	((x) > -EQN_EPS && (x) < EQN_EPS)

#ifndef CBRT
#define     cbrt(x)  ((x) > 0.0 ? pow((double)(x), 1.0/3.0) : \
			  		 ((x) < 0.0 ? -pow((double)-(x), 1.0/3.0) : 0.0))
#endif

namespace rayray::utilties::math
{
    double min(double x0, double x1)
    {
        return ((x0 < x1) ? x0 : x1);
    }

    double max(double x0, double x1) {
        return ((x0 > x1) ? x0 : x1);
    }

    int rand_int(void) {
        return(rand());
    }

    float rand_float(void) {
        return((float)rand_int() * INVERSE_RAND_MAX);
    }

    void set_rand_seed(const int seed) {
        srand(seed);
    }

    float rand_float(int l, float h) {
        return (rand_float() * (h - l) + l);
    }

    int
        rand_int(int l, int h) {
        return ((int)(rand_float(0, h - l + 1) + l));
    }

    double clamp(const double x, const double min, const double max) {
        return (x < min ? min : (x > max ? max : x));
    }

    int solve_quadric(double c[3], double s[2]) {
        double p, q, D;

        /* normal form: x^2 + px + q = 0 */

        p = c[1] / (2 * c[2]);
        q = c[0] / c[2];

        D = p * p - q;

        if (IsZero(D)) {
            s[0] = -p;
            return 1;
        }
        else if (D > 0) {
            double sqrt_D = sqrt(D);

            s[0] = sqrt_D - p;
            s[1] = -sqrt_D - p;
            return 2;
        }
        else /* if (D < 0) */
            return 0;
    }

    int solve_cubic(double c[4], double s[3]) {
        int     i, num;
        double  sub;
        double  A, B, C;
        double  sq_A, p, q;
        double  cb_p, D;

        /* normal form: x^3 + Ax^2 + Bx + C = 0 */

        A = c[2] / c[3];
        B = c[1] / c[3];
        C = c[0] / c[3];

        /*  substitute x = y - A/3 to eliminate quadric term:
        x^3 +px + q = 0 */

        sq_A = A * A;
        p = 1.0 / 3 * (-1.0 / 3 * sq_A + B);
        q = 1.0 / 2 * (2.0 / 27 * A * sq_A - 1.0 / 3 * A * B + C);

        /* use Cardano's formula */

        cb_p = p * p * p;
        D = q * q + cb_p;

        if (IsZero(D)) {
            if (IsZero(q)) { /* one triple solution */
                s[0] = 0;
                num = 1;
            }
            else { /* one single and one double solution */
                double u = cbrt(-q);
                s[0] = 2 * u;
                s[1] = -u;
                num = 2;
            }
        }
        else if (D < 0) { /* Casus irreducibilis: three real solutions */
            double phi = 1.0 / 3 * acos(-q / sqrt(-cb_p));
            double t = 2 * sqrt(-p);

            s[0] = t * cos(phi);
            s[1] = -t * cos(phi + M_PI / 3);
            s[2] = -t * cos(phi - M_PI / 3);
            num = 3;
        }
        else { /* one real solution */
            double sqrt_D = sqrt(D);
            double u = cbrt(sqrt_D - q);
            double v = -cbrt(sqrt_D + q);

            s[0] = u + v;
            num = 1;
        }

        /* resubstitute */

        sub = 1.0 / 3 * A;

        for (i = 0; i < num; ++i)
            s[i] -= sub;

        return num;
    }

    int solve_quartic(double c[5], double s[4]) {
        double  coeffs[4];
        double  z, u, v, sub;
        double  A, B, C, D;
        double  sq_A, p, q, r;
        int     i, num;

        /* normal form: x^4 + Ax^3 + Bx^2 + Cx + D = 0 */

        A = c[3] / c[4];
        B = c[2] / c[4];
        C = c[1] / c[4];
        D = c[0] / c[4];

        /*  substitute x = y - A/4 to eliminate cubic term:
        x^4 + px^2 + qx + r = 0 */

        sq_A = A * A;
        p = -3.0 / 8 * sq_A + B;
        q = 1.0 / 8 * sq_A * A - 1.0 / 2 * A * B + C;
        r = -3.0 / 256 * sq_A*sq_A + 1.0 / 16 * sq_A*B - 1.0 / 4 * A*C + D;

        if (IsZero(r)) {
            /* no absolute term: y(y^3 + py + q) = 0 */

            coeffs[0] = q;
            coeffs[1] = p;
            coeffs[2] = 0;
            coeffs[3] = 1;

            num = solve_cubic(coeffs, s);

            s[num++] = 0;
        }
        else {
            /* solve the resolvent cubic ... */

            coeffs[0] = 1.0 / 2 * r * p - 1.0 / 8 * q * q;
            coeffs[1] = -r;
            coeffs[2] = -1.0 / 2 * p;
            coeffs[3] = 1;

            (void)solve_cubic(coeffs, s);

            /* ... and take the one real solution ... */

            z = s[0];

            /* ... to build two quadric equations */

            u = z * z - r;
            v = 2 * z - p;

            if (IsZero(u))
                u = 0;
            else if (u > 0)
                u = sqrt(u);
            else
                return 0;

            if (IsZero(v))
                v = 0;
            else if (v > 0)
                v = std::sqrt(v);
            else
                return 0;

            coeffs[0] = z - u;
            coeffs[1] = q < 0 ? -v : v;
            coeffs[2] = 1;

            num = solve_quadric(coeffs, s);

            coeffs[0] = z + u;
            coeffs[1] = q < 0 ? v : -v;
            coeffs[2] = 1;

            num += solve_quadric(coeffs, s + num);
        }

        /* resubstitute */

        sub = 1.0 / 4 * A;

        for (i = 0; i < num; ++i)
            s[i] -= sub;

        return num;
    }
}

