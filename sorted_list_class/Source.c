#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include<time.h>
#pragma warning(disable:4996)

typedef struct ItemNum
{
	int num;
	struct ItemNum* next;
	struct ItemNum* prev;
}STItemNum;

STItemNum* head;
STItemNum* tail;


void StartLogClean()
{

	FILE* f = fopen("SortLog.log", "w");
	fputs("\n-----------------------------------------------------------------------------", f);
	fclose(f);
}
void Log(char message[100])
{

	FILE* f = fopen("SortLog.log", "a");
	time_t t;
	time(&t);
	struct tm* timeinfo;
	timeinfo = localtime(&t);
	char str[130];
	sprintf(str, "%d.%d.%d-%d:%d:%d - %s", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, message);
	fputs("\n", f);
	fputs(str, f);
	fclose(f);
}

void LogError(char message[100])
{
	char addarr[110];
	sprintf(addarr, "Error - %s", message);
	Log(addarr);

}
void LogEvent(char message[100])
{
	char addarr[110];
	sprintf(addarr, "Event - %s", message);
	Log(addarr);
}
void LogEventVal(char message[100], int val)
{
	char addarr[120];
	sprintf(addarr, "EventVal - Item val %d : %s", val, message);
	Log(addarr);
}
void LogEventTime(char message[100], int val)
{
	char addarr[120];
	sprintf(addarr, "%s %d sec", message, val);
	Log(addarr);
}



void add(int number)
{
	STItemNum* curr = (STItemNum*)malloc(sizeof(STItemNum));
	LogEventVal("Create new Item", number);
	curr->num = number;
	if (head == NULL)
	{
		LogEventVal("List is started now ", number);
		curr->next = NULL;
		curr->prev = NULL;
		head = curr;
		tail = curr;
	}
	else
	{
		curr->next = NULL;
		curr->prev = tail;
		tail->next = curr;
		tail = curr;
	}

}

void PrintList()
{
	STItemNum* curr = head;
	while (curr)
	{
		curr = curr->next;

	}
	printf("\n");

}

void ReplaceItem(STItemNum* item)
{
	if (item == NULL)
	{
		LogEvent("The List is empty");

	}
	else if (item->next == NULL)
	{
		LogEvent("There id ONE item in list");

	}
	else if (item == head && item->next == tail)
	{
		item->next = NULL;
		item->prev = tail;
		tail->prev = NULL;
		tail->next = item;
		tail = item;
		head = item->prev;
	}
	else if (item == head && item->next != NULL)
	{
		item->next = item->next->next;
		item->next->prev->next = item;
		item->next->prev->prev = NULL;
		item->prev = item->next->prev;
		item->next->prev = item;
		head = item->prev;
	}
	else if (item->next == tail)
	{
		item->prev->next = item->next;
		item->next->prev = item->prev;
		item->next->next = item;
		item->prev = item->next;
		item->next = NULL;
		tail = item;
	}
	else {
		item->prev->next = item->next;
		item->next->prev = item->prev;
		item->next->next->prev = item;
		item->prev = item->next;
		item->next = item->next->next;
		item->prev->next = item;
	}
}

void BubleSort()
{
	STItemNum* curr = head;

	if (!curr) {
		LogEvent("The List is empty");
		return;
	}
	char change = 1;

	unsigned long num1 = time(NULL);
	while (change != 0)
	{
		change = 0;
		while (curr != NULL)
		{
			if (curr->next != NULL && curr->num > curr->next->num)
			{
				ReplaceItem(curr);
				change++;
			}
			curr = curr->next;
		}
		curr = head;
	}
	unsigned long num2 = time(NULL);
	int sum = num2 - num1;
	printf("THE TIME IT TOOK TO sort THE LIST: %d sec\n", sum);
	LogEventTime("THE TIME IT TOOK TO sort A LIST", sum);
}

void AddRandomItems(int count)
{
	printf("There is %d item in list\n", count);


	unsigned long num11 = time(NULL);
	for (int i = 0; i < count; i++)
	{
		int a = rand();
		add(a);
	}
	unsigned long num22 = time(NULL);
	int sum1 = num22 - num11;
	printf("THE TIME IT TOOK TO make A LIST: %d sec\n", sum1);
	LogEventTime("THE TIME IT TOOK TO make A LIST", sum1);

	BubleSort();

}


int main()
{
	srand(time(NULL));

	StartLogClean();
	LogEvent("START OF LOG PROJECT");

	AddRandomItems(100000);

	/*
	PrintList();
	BubleSort();
	PrintList();
	*/

	LogEvent("END OF LOG PROJECT");
	return 0;
}