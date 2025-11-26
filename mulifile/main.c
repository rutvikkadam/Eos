#include<stdio.h>
#include "circle.h"
#include "square.h"
#include "rectangle.h"

int main()
{
	double radius = 5.0;
	double side =4.0;
	double length = 6.0;
	double width = 3.0;
	
	printf("Area of circle : %2f\n", area_of_circle(radius));
	printf("area of square : %2f\n", area_of_square(side));
	printf("Area of rectangle :%2f\n", area_of_rectangle(length,width));

return 0;

}
