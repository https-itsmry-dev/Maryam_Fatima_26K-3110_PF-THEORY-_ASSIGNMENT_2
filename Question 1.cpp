#include <stdio.h>
int main()
{
	int seat[20][20], rows, seats, i, j, k, d, r, middle, count;
	int found = 0, bookrow = 0, startseat = 0, row_free, total_free = 0;
	printf("This is a program written in C to demonstrate the use of 2D array for The Cinema Hall Seat Booking System");
	printf("\nEnter the number of rows (1 to 20): ");
	scanf("%d", &rows);
	while (rows < 1 || rows > 20)
	{
		printf("\nInvalid number of rows, enter the number of rows again (1 to 20): ");
		scanf("%d", &rows);
	}
	printf("\nEnter the number of seats per row (1 to 20): ");
	scanf("%d", &seats);
	while (seats < 1 || seats > 20)
	{
		printf("\nInvalid number of seats, enter the number of seats per row again (1 to 20): ");
		scanf("%d", &seats);
	}
	printf("\nFor the status of seats, Enter 0-->Available OR 1-->Booked");
	for (i=0; i<rows; i++)
	{
		for (j=0; j<seats; j++)
		{
			printf("\nEnter the status of each seat respectively: ");
			scanf("%d", &seat[i][j]);
		}
	}
	
	printf("\n\n===========Seating Plan===========");
	printf("\n    ");
	for (j=0; j<seats; j++)
	{
		printf("%d ", j);
	}
	for (i=0; i<rows; i++)
	{
		printf("\nR%d  ", i);
		for (j=0; j<seats; j++)
		{
			if (seat[i][j] == 0)
			{
				printf("_ ");
			}
			else
			{
				printf("X ");
			}
		}
	}
	
	printf("\n\n===========Seat Availability Report===========");
	printf("\nFree seats per row: ");
	for (i=0; i<rows; i++)
	{
		row_free = 0;
		for (j=0; j<seats; j++)
		{
			if (seat[i][j] == 0)
			{
				row_free = row_free + 1;
			}
		}
		printf("%d ", row_free);
		total_free = total_free + row_free;
	}
	printf("\nTotal free: %d", total_free);
	
	printf("\n\nEnter the number of customers who want to sit together: ");
	scanf("%d", &k);
	while (k <= 0 || k > seats)
	{
		printf("\nInvalid group size, it must be greater than 0 and not more than %d", seats);
		printf("\nEnter the number of customers again: ");
		scanf("%d", &k);
	}
	
	middle = rows / 2;
	d = 0;
	while (d <= rows && found == 0)
	{
		r = middle - d;
		if (r >= 0 && found == 0)
		{
			count = 0;
			for (j=0; j<seats && found == 0; j++)
			{
				if (seat[r][j] == 0)
				{
					count = count + 1;
				}
				else
				{
					count = 0;
				}
				if (count == k)
				{
					found = 1;
					bookrow = r;
					startseat = j - k + 1;
				}
			}
		}
		r = middle + d;
		if (d > 0 && r < rows && found == 0)
		{
			count = 0;
			for (j=0; j<seats && found == 0; j++)
			{
				if (seat[r][j] == 0)
				{
					count = count + 1;
				}
				else
				{
					count = 0;
				}
				if (count == k)
				{
					found = 1;
					bookrow = r;
					startseat = j - k + 1;
				}
			}
		}
		d = d + 1;
	}
	
	if (found == 1)
	{
		for (j=startseat; j<startseat+k; j++)
		{
			seat[bookrow][j] = 1;
		}
		total_free = total_free - k;
		printf("\n\nGroup of %d seated in Row %d, Seats %d to %d", k, bookrow, startseat, startseat+k-1);
		printf("\n\n===========Updated Seating Plan===========");
		printf("\n    ");
		for (j=0; j<seats; j++)
		{
			printf("%d ", j);
		}
		for (i=0; i<rows; i++)
		{
			printf("\nR%d  ", i);
			for (j=0; j<seats; j++)
			{
				if (seat[i][j] == 0)
				{
					printf("_ ");
				}
				else
				{
					printf("X ");
				}
			}
		}
		printf("\n\nThe remaining available seats are: %d", total_free);
	}
	else
	{
		printf("\n\nSorry, no row has %d consecutive available seats", k);
		printf("\nThe seating plan is unchanged");
	}
	return 0;
}
