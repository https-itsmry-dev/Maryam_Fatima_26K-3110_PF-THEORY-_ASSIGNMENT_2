#include <stdio.h>
int sumdivisors(int x)
{
	int i, sum = 0;
	for (i=1; i<=x/2; i++)
	{
		if (x % i == 0)
		{
			sum = sum + i;
		}
	}
	return sum;
}
int main()
{
	int n, a, b, count = 0;
	printf("This is a program written in C to find the amicable pairs using a function");
	printf("\nEnter the number n: ");
	scanf("%d", &n);
	printf("\nAmicable pairs up to %d:", n);
	for (a=1; a<=n; a++)
	{
		b = sumdivisors(a);
		if (b > a && b <= n)
		{
			if (sumdivisors(b) == a)
			{
				printf("\n(%d, %d)", a, b);
				count = count + 1;
			}
		}
	}
	if (count == 0)
	{
		printf("\nNo amicable pairs were found up to %d", n);
	}
	else
	{
		printf("\nTotal pairs: %d", count);
	}
	return 0;
}
