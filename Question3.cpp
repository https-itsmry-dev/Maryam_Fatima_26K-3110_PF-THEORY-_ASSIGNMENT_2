#include <stdio.h>
void inputReadings(int temp[][50], int sensors, int readings)
{
	int i, j;
	for (i=0; i<sensors; i++)
	{
		for (j=0; j<readings; j++)
		{
			printf("\nEnter the temperature readings of each sensor respectively: ");
			scanf("%d", &temp[i][j]);
		}
	}
}
float analyzeSensor(int sensor[], int numreadings, int sensornumber)
{
	int i, total = 0, highest, lowest, critical = 0, warning = 0, streak = 0, longest = 0;
	float average;
	highest = sensor[0];
	lowest = sensor[0];
	for (i=0; i<numreadings; i++)
	{
		total = total + sensor[i];
		if (sensor[i] > highest)
		{
			highest = sensor[i];
		}
		if (sensor[i] < lowest)
		{
			lowest = sensor[i];
		}
		if (sensor[i] >= 40)
		{
			critical = critical + 1;
		}
		if (sensor[i] >= 35 && sensor[i] <= 39)
		{
			warning = warning + 1;
		}
		if (sensor[i] >= 35)
		{
			streak = streak + 1;
			if (streak > longest)
			{
				longest = streak;
			}
		}
		else
		{
			streak = 0;
		}
	}
	average = (float)total / numreadings;
	printf("\nSensor %d: Total=%d Avg=%.2f Max=%d Min=%d", sensornumber, total, average, highest, lowest);
	printf("\n          Critical=%d Warning=%d Longest hot streak=%d", critical, warning, longest);
	return average;
}
int highestAverage(float avg[], int sensors)
{
	int i, best = 0;
	for (i=1; i<sensors; i++)
	{
		if (avg[i] > avg[best])
		{
			best = i;
		}
	}
	return best + 1;
}
int main()
{
	int temp[20][50], sensors, readings, i, best;
	float avg[20];
	printf("This is a program written in C to make The Greenhouse Temperature Monitoring System");
	printf("\nEnter the number of sensors (1 to 20): ");
	scanf("%d", &sensors);
	printf("\nEnter the number of hourly readings (1 to 50): ");
	scanf("%d", &readings);
	inputReadings(temp, sensors, readings);
	printf("\n\n===========Sensor Reports===========");
	for (i=0; i<sensors; i++)
	{
		avg[i] = analyzeSensor(temp[i], readings, i+1);
	}
	best = highestAverage(avg, sensors);
	printf("\n\nHighest average: Sensor %d (%.2f)", best, avg[best-1]);
	return 0;
}
