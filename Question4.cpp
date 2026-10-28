#include <stdio.h>
int getValidDays()
{
	int days;
	printf("\nEnter the number of festival days (1 to 7): ");
	scanf("%d", &days);
	while (days < 1 || days > 7)
	{
		printf("\nInvalid number of days, enter the number of festival days again (1 to 7): ");
		scanf("%d", &days);
	}
	return days;
}
float calculateDailySales(int dayNumber)
{
	int orders, i;
	float amount, total = 0, average, highest = 0;
	printf("\nDay %d - Enter the number of orders: ", dayNumber);
	scanf("%d", &orders);
	for (i=1; i<=orders; i++)
	{
		printf("\nEnter the amount of each order respectively: ");
		scanf("%f", &amount);
		while (amount <= 0)
		{
			printf("\nInvalid amount, enter the amount of the same order again: ");
			scanf("%f", &amount);
		}
		total = total + amount;
		if (amount > highest)
		{
			highest = amount;
		}
	}
	average = total / orders;
	printf("\nTotal sales: Rs. %.2f", total);
	printf("\nAverage order: Rs. %.2f", average);
	printf("\nHighest order: Rs. %.2f", highest);
	return total;
}
int findHighestSalesDay(float dailySales[], int numberOfDays)
{
	int i, bestday = 1;
	for (i=1; i<numberOfDays; i++)
	{
		if (dailySales[i] > dailySales[bestday-1])
		{
			bestday = i + 1;
		}
	}
	return bestday;
}
void displayBarChart(float dailySales[], int numberOfDays)
{
	int i, j, stars;
	printf("\n\n===== DAILY SALES BAR CHART =====");
	for (i=0; i<numberOfDays; i++)
	{
		stars = (int)(dailySales[i] / 100);
		printf("\nDay %d: ", i+1);
		for (j=1; j<=stars; j++)
		{
			printf("*");
		}
		printf(" (Rs. %.2f)", dailySales[i]);
	}
}
int main()
{
	int days, i, bestday;
	float dailySales[7], festival_total = 0;
	printf("This is a program written in C to make The Bakery Festival Sales Management System");
	days = getValidDays();
	for (i=0; i<days; i++)
	{
		dailySales[i] = calculateDailySales(i+1);
		festival_total = festival_total + dailySales[i];
		printf("\n");
	}
	bestday = findHighestSalesDay(dailySales, days);
	printf("\n===== FESTIVAL SUMMARY =====");
	printf("\nTotal festival sales: Rs. %.2f", festival_total);
	printf("\nDay with highest sales: Day %d", bestday);
	printf("\nHighest daily sales: Rs. %.2f", dailySales[bestday-1]);
	displayBarChart(dailySales, days);
	return 0;
}
