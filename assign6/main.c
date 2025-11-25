#include "circle.h"
#include "square.h"
#include "rectangle.h"
#include <stdio.h>

int main() {
    printf("Starting multi-file C project execution.\n");

    // Call functions from different modules
    calculate_circle_area(5.0);
    calculate_square_area(4.0);
    calculate_rectangle_area(6.0, 3.0);

    printf("Program finished successfully.\n");
    return 0;
}

