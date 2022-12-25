
#ifndef TROPICAL_TROPICAL_UTILS_H
#define TROPICAL_TROPICAL_UTILS_H



inline bool double_equals(double a, double b) {

    const double epsilon = 0.01;
    return abs(a - b) < epsilon;
}
inline bool approximatelyEqual(float a, float b, float epsilon)
{
    return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}


#endif //TROPICAL_TROPICAL_UTILS_H
