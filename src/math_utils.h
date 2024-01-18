#ifndef MATH_UTILS_
#define MATH_UTILS_

#include <math.h>

#define PI 3.14159265358979323846

#define DEG_TO_RAD(degrees) ((degrees) * (PI / 180.0))
#define RAD_TO_DEG(rad) ((rad) * (180.0 / PI))
#define ACOT(x) ((PI / 2.0) - atanf(x))

#endif // MATH_UTILS_
