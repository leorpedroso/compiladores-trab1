#include <stdio.h>

int a[3]={10, 20, 30};
int b = 1;
int c = 100;
int main () {
	// a[2] = b;
	c = a[b];
	printf("%d", c);
}
