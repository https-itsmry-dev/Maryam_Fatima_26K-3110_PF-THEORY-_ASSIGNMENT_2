#include <stdio.h>
#include <string.h>
void displayMenu()
{
	printf("\n\n===========University Library Menu===========");
	printf("\n1. Register Member");
	printf("\n2. Display Available Books");
	printf("\n3. Borrow a Book");
	printf("\n4. Return a Book");
	printf("\n5. Display Member Record");
	printf("\n6. Exit");
}
void registerMember(char name[], int *studentID, int *memberType)
{
	printf("\nEnter the name of the member (without spaces): ");
	scanf("%s", name);
	printf("\nEnter the student ID: ");
	scanf("%d", studentID);
	printf("\nFor membership type, Enter 1-->Student OR 2-->Faculty");
	printf("\nEnter the membership type: ");
	scanf("%d", memberType);
	while (*memberType != 1 && *memberType != 2)
	{
		printf("\nInvalid membership type, enter the membership type again (1-->Student OR 2-->Faculty): ");
		scanf("%d", memberType);
	}
	if (*memberType == 1)
	{
		printf("\nMember registered successfully. A student can keep books for 14 days");
	}
	else
	{
		printf("\nMember registered successfully. A faculty member can keep books for 30 days");
	}
}
void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks)
{
	int i;
	printf("\n\nID\tTitle\t\t\tCopies");
	for (i=0; i<totalBooks; i++)
	{
		printf("\n%d\t%-20s\t%d", bookIDs[i], bookTitles[i], availableCopies[i]);
	}
}
void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType)
{
	int id, days, i, pos = -1, allowed;
	printf("\nEnter the book ID: ");
	scanf("%d", &id);
	printf("\nEnter the number of days you want to keep the book: ");
	scanf("%d", &days);
	while (days <= 0)
	{
		printf("\nInvalid number of days, enter the number of days again: ");
		scanf("%d", &days);
	}
	for (i=0; i<totalBooks; i++)
	{
		if (bookIDs[i] == id)
		{
			pos = i;
		}
	}
	if (pos == -1)
	{
		printf("\nInvalid book ID");
	}
	else
	{
		if (availableCopies[pos] == 0)
		{
			printf("\nSorry, no copies of %s are available", bookTitles[pos]);
		}
		else
		{
			if (*borrowedCount >= 3)
			{
				printf("\nYou can not borrow more than 3 books at a time");
			}
			else
			{
				borrowedBookIDs[*borrowedCount] = id;
				*borrowedCount = *borrowedCount + 1;
				availableCopies[pos] = availableCopies[pos] - 1;
				printf("\nYou have borrowed the book: %s", bookTitles[pos]);
				if (memberType == 1)
				{
					allowed = 14;
				}
				else
				{
					allowed = 30;
				}
				if (days > allowed)
				{
					printf("\nNote: You are allowed to keep a book for %d days only, a fine will be charged for the extra days", allowed);
				}
			}
		}
	}
}
float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine)
{
	int id, days, i, pos = -1, bookpos = -1, allowed, extra;
	float fine = 0, finalfine = 0;
	char code[20];
	printf("\nEnter the book ID to return: ");
	scanf("%d", &id);
	for (i=0; i<*borrowedCount; i++)
	{
		if (borrowedBookIDs[i] == id && pos == -1)
		{
			pos = i;
		}
	}
	if (pos == -1)
	{
		printf("\nYou have not borrowed this book");
		return 0;
	}
	printf("\nEnter the number of days the book was kept: ");
	scanf("%d", &days);
	while (days <= 0)
	{
		printf("\nInvalid number of days, enter the number of days again: ");
		scanf("%d", &days);
	}
	for (i=0; i<totalBooks; i++)
	{
		if (bookIDs[i] == id)
		{
			bookpos = i;
		}
	}
	availableCopies[bookpos] = availableCopies[bookpos] + 1;
	if (memberType == 1)
	{
		allowed = 14;
	}
	else
	{
		allowed = 30;
	}
	if (days > allowed)
	{
		extra = days - allowed;
		if (memberType == 1)
		{
			fine = extra * 20;
		}
		else
		{
			fine = extra * 10;
		}
	}
	*totalFine = *totalFine + fine;
	finalfine = fine;
	if (fine > 0)
	{
		printf("\nThe book was returned late. The late fine is: Rs. %.2f", fine);
		printf("\nEnter the membership code to get the waiver: ");
		scanf("%s", code);
		if (strcmp(code, "LIB2026") == 0)
		{
			finalfine = fine / 2;
			printf("\nCorrect code, a 50 percent waiver is applied");
		}
		else
		{
			printf("\nWrong code, no waiver is applied");
		}
	}
	for (i=pos; i<(*borrowedCount)-1; i++)
	{
		borrowedBookIDs[i] = borrowedBookIDs[i+1];
	}
	*borrowedCount = *borrowedCount - 1;
	printf("\nThe book is returned successfully");
	printf("\nThe fine payable for this return is: Rs. %.2f", finalfine);
	return finalfine;
}
void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[], int borrowedCount, float totalFine, float fineAfterWaiver)
{
	int i;
	printf("\n\n===========Member Record===========");
	printf("\nName: %s", name);
	printf("\nStudent ID: %d", studentID);
	if (memberType == 1)
	{
		printf("\nMembership type: Student");
	}
	else
	{
		printf("\nMembership type: Faculty");
	}
	printf("\nCurrently borrowed books: ");
	if (borrowedCount == 0)
	{
		printf("None");
	}
	for (i=0; i<borrowedCount; i++)
	{
		printf("%d ", borrowedBookIDs[i]);
	}
	printf("\nTotal fine before waiver: Rs. %.2f", totalFine);
	printf("\nFinal fine payable after waiver: Rs. %.2f", fineAfterWaiver);
}
int main()
{
	int bookIDs[4] = {101, 102, 103, 104};
	char bookTitles[4][50] = {"Programming in C", "Data Structures", "Database Systems", "Computer Networks"};
	int availableCopies[4] = {5, 3, 0, 4};
	int totalBooks = 4;
	char name[50];
	int studentID = 0, memberType = 0, borrowedBookIDs[3], borrowedCount = 0, choice, registered = 0;
	float totalFine = 0, fineAfterWaiver = 0;
	printf("This is a program written in C to make The University Library Management System");
	do
	{
		displayMenu();
		printf("\nEnter your choice: ");
		scanf("%d", &choice);
		switch (choice)
		{
			case 1:
				if (registered == 1)
				{
					printf("\nThe member is already registered");
				}
				else
				{
					registerMember(name, &studentID, &memberType);
					registered = 1;
				}
				break;
			case 2:
				displayBooks(bookIDs, bookTitles, availableCopies, totalBooks);
				break;
			case 3:
				if (registered == 0)
				{
					printf("\nPlease register the member first");
				}
				else
				{
					borrowBook(bookIDs, bookTitles, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType);
				}
				break;
			case 4:
				if (registered == 0)
				{
					printf("\nPlease register the member first");
				}
				else
				{
					fineAfterWaiver = fineAfterWaiver + returnBook(bookIDs, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType, &totalFine);
				}
				break;
			case 5:
				if (registered == 0)
				{
					printf("\nPlease register the member first");
				}
				else
				{
					displayMemberRecord(name, studentID, memberType, borrowedBookIDs, borrowedCount, totalFine, fineAfterWaiver);
				}
				break;
			case 6:
				printf("\nThank you, exiting the program");
				break;
			default:
				printf("\nInvalid choice, please try again");
		}
	} while (choice != 6);
	return 0;
}
