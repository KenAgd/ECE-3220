/*
 *	Kendric Agdaca
 *	kagdaca
 *	ECE 3220 Spring
 *	Due 2/25/22
 *	perimeter.c
 *
 *	Purpose: This program is to be ran by the second child created by asg1.c and calculates the perimeter of the 2 int input arguments that were passed into asg1.c
 */

#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{
	int num1 = atoi(argv[1]);
	int num2 = atoi(argv[2]);
	int perimeter = (2*num1) + (2*num2);
	printf("perimeter is %d\n\n", perimeter);
}
