#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable : 4996)

time_t t;

struct item
{
    int val;
	struct item* prev;
    struct item* next;
};

struct tm* timeinfo;
struct item* head=NULL;
struct item* current;
struct item* tail= NULL ;
struct item* find;


void addItem(int val);
void replace(struct item* replaceitem);
void sort();
void Shaker();
void PrintList();
void findItem(int val);
void FreeList();
void fullNumber();

FILE* f;

void Log(char message[100])
{
	f = fopen("data.log", "a");

	t = time(&t);
	timeinfo = localtime(&t);

	char str[100];

	sprintf(str, "%d/%d/%d  %d:%d:%d  %s", timeinfo->tm_wday + 1, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, message);
	fputs(str, f);
	//fputs(message, f);
	fclose(f);
}

void logEventVal(char msg[100], int val)
{
	char str[100];
	sprintf(str, "item val %d %s\n", val, msg);
	Log(str);
}
void logEvent(char msg[100])
{
	Log(msg);
}
void logErorr(char msg[100])
{
	Log(msg);
}


int val, ran, num, startTimeSec, endTimeSec, TimeSec;
char userResponse = '0';


int main()
{
	srand(time(0));
	logEvent("The program started running\n");
	
	while (userResponse != 'e')
	{
		printf("Click 'a' for Add\nClick 'p' for print list\nClick 'r' to make the replace\nClick 's' for sort list\nClick 'h' for shaker-style sorting\nClick 'f' for add full item\nClick 'e' for free all and exit\n");
		userResponse = getch();

		switch (userResponse)
		{
		case 'a':
			ran = (rand() % 100) + 1;
			logEvent("The user requested to add an item to the list\n");
			addItem(ran);
			break;

		case 'p':
			logEvent("The user requested to print all the list\n");
			printf("\nthe list:\n");
			PrintList(); 
			printf("\n");
			logEvent("The list has been printed\n");
			break;

		case 'r':
			logEvent("The user requested to replace the position of the item with the position of the next one after it\n");
			printf("\nwhich list do you want to replace with the next one?\n");
			scanf("%d", &num);
			//LogEventVal("The requested item", num);
			findItem(num);
			replace(find);
			logEvent("The replacement was made\n");
			break;

		case 's':
			logEvent("The user requested to sort the list\n");
			printf("\nsort:\n");
			sort();
			logEvent("Sorting has been done\n");
			break;

		case 'h':
			logEvent("The user requested to sort the list in shaker style\n");
			printf("\nShaker:\n");
			Shaker();
			logEvent("The shaker-style sorting was done\n");
			break;

		case 'f':
			logEvent("The user requested to add 100,000 items and sort them\n");
			printf("\nIf you want sort click 1, if you want a Shaker click 2\n");
			scanf("%d", &num);
			fullNumber();
			break;

		case 'e':
			logEvent("The user requested to release the list and exit the program\n");
			FreeList();
			logEvent("The list has been freed from memory\n");
			printf("\nend\n");
			break;
		}
	}

	logEvent("The program has finished running\n");
	return 0;
}

void addItem(int val)
{
    current = (struct item*)malloc(sizeof(struct item));

	logEvent("create new item\n");

    current->val = val;
    current->next = NULL;
    //current->prev = NULL;

    printf("\nval=%d\n\n", current->val);

    if (head == NULL)
    {
		logEvent("list is started new\n");
        head = current;
        tail = current;
    }
    else
    {
		//LogEventVal("is Added", current->val);
		tail->next = current;
        current->prev = tail;
        tail = current;
    }
}


void replace(struct item* replaceitem)
{
	if (replaceitem == NULL) //אפס איברים
	{
		logEventVal("no need to swap. no item in list", replaceitem->val);
	}
	else if (replaceitem->next == NULL) // האחרון
	{
		logEventVal("no need to swap", replaceitem->val);
	}
	else if (replaceitem == head && replaceitem->next == tail) // שני איברים ברשימה
	{
		replaceitem->next = NULL;
		replaceitem->prev = tail;
		tail->prev = NULL;
		tail->next = replaceitem;
		tail = replaceitem;
		head = replaceitem->prev;
	}
	else if (replaceitem == head && replaceitem->next != NULL)  // שלוש צמוד לשמאל
	{
		replaceitem->next = replaceitem->next->next;
		replaceitem->next->prev->next = replaceitem;
		replaceitem->next->prev->prev = NULL;
		replaceitem->prev = replaceitem->next->prev;
		replaceitem->next->prev = replaceitem;
		head = replaceitem->prev;
	}
	else if (replaceitem->next == tail)  // שלוש צמוד לימין
	{
		replaceitem->prev->next = replaceitem->next;
		replaceitem->next->prev = replaceitem->prev;
		replaceitem->next->next = replaceitem;
		replaceitem->prev = replaceitem->next;
		replaceitem->next = NULL;
		tail = replaceitem;
	}
	else // שניים באמצע
	{
		replaceitem->prev->next = replaceitem->next; // 1->3
		replaceitem->next->prev = replaceitem->prev; // 3->1 
		replaceitem->next->next->prev = replaceitem; // 4->2
		replaceitem->prev = replaceitem->next; //2->3
		replaceitem->next = replaceitem->next->next; // 2->4
		replaceitem->prev->next = replaceitem; // 3->2
	}
}



void sort()
{
	struct item* sort = head;

	if (!sort)
	{
		logEvent("the list is empty\n");
		return;
	}

	char change = 1;
	
	while (change != 0)
	{
		change = 0;
		while (sort != NULL)
		{
			if (sort->next != NULL && sort->val > sort->next->val)
			{
				replace(sort);
				change++;
			}
			sort = sort->next;
		}
		sort = head;
	}

	PrintList();

}

void Shaker()
{
	struct item* sort = head;

	if (!sort)
	{
		logEvent("the list is empty\n");
		return;
	}

	char change = 1;

	while (change != 0)
	{
		change = 0;
		while (sort != NULL)
		{
			while (sort->next != NULL)
			{
				while (sort->next != NULL && sort->val > sort->next->val)
				{
					replace(sort);
					change++;
				}

				if (sort->next != NULL)
				{
					sort = sort->next;
				}
			}

			while (sort != NULL)
			{
				while (sort->prev != NULL && sort->val < sort->prev->val)
				{
					sort = sort->prev;
					replace(sort);
					change++;
				}
				sort = sort->prev;
			}
		}
		sort = head;
	}

	PrintList();

}

void PrintList()
{
	struct item* printItem = head;
	while (printItem != NULL)
	{
		printf("val=%d\n", printItem->val);
		printItem = printItem->next;
	}
	return;
}

void findItem(int val)
{
	find = head;

	while (find != NULL && find->val != val)
	{
		find = find->next;
	}

	if (find == NULL)
	{
		printf("\nno need to swap. no item in list\n");
	}
	else
	{
		logEvent("The requested item has been voted on\n");
	}

	return;
}

void FreeList()
{
	struct item* current = head;
	struct item* freeitem = head;

	printf("\nFree the list:\n");
	PrintList();

	while (current != NULL)
	{
		int a = current->val;
		current = current->next;
		free(freeitem);
		freeitem = current;
		head = current;
		printf("\nval=%d is free",a);
		logEventVal("is free", a);
	}

	printf("\ncongratulations, the memory of all list is free\n");
	return;
}

void fullNumber()
{
	int Selector = 1;
	int SecBuildList;
	int SecSort;

	while (Selector != 0)
	{
		if (num == 1)
		{
			Selector = 0;
			logEvent("Adds 100000 items and sorts by sort\n");
			startTimeSec = time(&t);
			for (int i = 1; i <= 100000; i++)
			{
				ran = (rand() % 100) + 1;
				addItem(ran);
			}
			endTimeSec = time(&t);
			
			SecBuildList = endTimeSec - startTimeSec;

			startTimeSec = time(&t);
			sort();
			endTimeSec = time(&t);

			SecSort = endTimeSec - startTimeSec;

			logEvent("Sorting has been done\n");
		}
		else if (num == 2)
		{
			Selector = 0;
			logEvent("Adds 100000 items and sorts by Shaker\n");
			startTimeSec = time(&t);
			for (int i = 0; i < 100000; i++)
			{
				ran = (rand() % 100) + 1;
				addItem(ran);
			}
			endTimeSec = time(&t);

			SecBuildList = endTimeSec - startTimeSec;

			startTimeSec = time(&t);
			Shaker();
			endTimeSec = time(&t);

			SecSort = endTimeSec - startTimeSec;

			logEvent("The shaker-style sorting was done\n");
		}
		else
		{
			printf("Click 1 or 2!\n");
			scanf("%d", &num);
		}
	}

	printf("\n%d seconds build list", SecBuildList);
	printf("\n%d seconds sort list\n\n", SecSort);

}