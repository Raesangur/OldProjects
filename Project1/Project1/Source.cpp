#include <stdio.h>

void main(void)
{
	int* ptr1;
	int* ptr2;

	ptr1 = (int*)&ptr2;
	ptr2 = (int*)&ptr1;

	*ptr1 = 2;

	printf("%d %d", ptr1, *ptr1, ptr2, *ptr2);

	while (1);
}