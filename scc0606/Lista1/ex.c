#include <stdio.h>
#include <time.h>

int function(int n)
{
	if(n==0)
		return 1;
	else
		return (n * function(n-1));
}



int main()
{
	double timeSpent = 0.0;

	clock_t beginTime = clock();
	function(0);
	function(1);
	function(5);
	clock_t endTime = clock();

	timeSpent += (double)(endTime - beginTime) / CLOCKS_PER_SEC;

	printf("The elapsed time is %f seconds\n", timeSpent);

	return 0;
}
