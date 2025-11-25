#include "circle.h"
#include <stdio.h>
#define PI 3.14159265359

void calculate_circle_area(double radius) {
    double area = PI * radius * radius;
    printf("Circle Area (Radius 5): %.2f\n", area);
}

