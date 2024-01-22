#ifndef MATH_UTILS_
#define MATH_UTILS_

#include <math.h>

#define PR_PI 3.14159265358979323846

#define PR_DEG_TO_RAD(degrees) ((degrees) * (PR_PI / 180.0))
#define PR_RAD_TO_DEG(rad) ((rad) * (180.0 / PR_PI))
#define PR_ACOT(x) ((PR_PI / 2.0) - atanf(x))

#endif // MATH_UTILS_
