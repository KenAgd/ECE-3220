/*
 *	Kendric Agdaca
 *	kagdaca
 *	ECE 3220 Spring
 *	Due 2/25/22
 *	area.c
 *
 *	Purpose: This program is to be ran by the first child created by asg1.c and calculates the area of the 2 int input arguments that were passed into asg1.c
 */

#include <stdio.h>
#include <stdlib.h>


// execl("./area", num1, argv[1], num2, argv[2]);??
void main(int argc, char *argv[])
{
	int num1 = atoi(argv[1]);
	int num2 = atoi(argv[2]);
	int area = num1 * num2;
	printf("area is %d\n\n", area);
}
