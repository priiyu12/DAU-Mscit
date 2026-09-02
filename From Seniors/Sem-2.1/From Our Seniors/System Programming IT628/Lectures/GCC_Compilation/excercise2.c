#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <inttypes.h>

#define submitted 0
#define running 1
#define completed 2

void update_time_elapsed();

struct query
{
	int query_id;	// unique id
	char* query_text;	// actual query text
	int status;	// 0=submitted, 1=running, 2=completed
	uint64_t start_time;
	uint64_t time_elapsed;	// time in microsec it took to run the query
	struct query *next;	// if you are using singly or doubly linked list
	//struct query *prev;	// if you are using doubly linked list
};

struct query *head=NULL;

// Time measurement function
uint64_t get_posix_clock_time ()
{
	struct timespec ts;
	#ifdef _SC_MONOTONIC_CLOCK
	if (sysconf(_SC_MONOTONIC_CLOCK) > 0)
	{
		/* A monotonic clock presents */
		//printf("Monotonic time is present\n");
		if (clock_gettime (CLOCK_MONOTONIC, &ts) == 0)
			return (uint64_t) (ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
		else
			return 0;
	}
	#endif
}

uint64_t get_gtod_clock_time ()
{
	struct timeval tv;
	if (gettimeofday (&tv, NULL) == 0)
		return (uint64_t) (tv.tv_sec * 1000000 + tv.tv_usec);
	else
		return 0;
}



void print_query(struct query *qry)
{
	update_time_elapsed();
	
	printf("Query ID:%d, Query Status: %s, Time taken %"PRIu64", Query Text:%s\n", qry->query_id, qry->status==running?"Running":qry->status==submitted?"Submitted":"Completed", qry->time_elapsed, qry->query_text);
}

void print_list()
{	
	struct query *tmp=head;
	if(tmp == NULL)
		printf("List is empty\n");
	while (tmp!=NULL)
	{
		print_query(tmp);
		tmp = tmp->next;
	}
}

struct query *search_query(char *qry_txt)
{
	struct query *found=NULL, *temp=head;
	
	// Insert code here to look for qry_txt in each node and set the pointer to that node in found if qry_txt is found otherwise set found=NULL
	if (temp == NULL)
		printf("List is empty\n");
	else
	{
		while(temp != NULL)
		{
			if (strcmp(temp->query_text, qry_txt) == 0)
			{
				found = temp;
				return found;
			}
			temp = temp->next;
		}
	}	
	return found;
}

void add_query()
{
	printf("add_query function called\n");

	// keeps track of query id
	static int qry_id=0;

	char qry_txt[100];
	printf("Enter new query:");
	scanf("%s", qry_txt);
	
	// Create new node and initialize the values
	struct query *new;
	new = (struct query *)malloc(sizeof(struct query));
	new->query_id = ++qry_id;
	new->query_text = (char *)malloc(strlen(qry_txt));
	strcpy(new->query_text, qry_txt);
	new->status = submitted;
	new->start_time = get_gtod_clock_time();
	new->time_elapsed = 0;
	new->next = NULL;
	
	// Insert your code to add node to the list
	if (head == NULL)
		head = new;
	else
	{
		struct query *temp;
		//while(temp->next != NULL)
		//	temp = temp->next;
		for(temp = head; temp->next != NULL; temp = temp->next);
		temp->next = new;
	}
	
	
	// After inserting query to the list print the whole list
	print_list();
	
	
}

void delete_query()
{
	printf("delete_query function called\n");

	// Insert code to delete all the query nodes with 2=completed status
	struct query *temp=head;
	
	while (temp != NULL)
	{
		if (temp->status == completed)
		{
			if (temp == head)
			{
				head = head->next;
				free(temp->query_text);
				free(temp);
				temp = head;
			}
			else
			{
				struct query *temp1;
				for(temp1=head; temp1->next != temp; temp1 = temp1->next);
				temp1->next = temp->next;
				free(temp->query_text);
				free(temp);
				temp = temp1->next;
			}
		}
		else
			temp = temp->next;
	}
	
	
	// After inserting query to the list print the whole list
	print_list();

}

void start_query()
{
	printf("start_query function called\n");
	
	char qry_txt[100];
	printf("Enter query:");
	scanf("%s", qry_txt);
	
	// Insert code to first search for the query text in the list
	// This code will be used multiple times so you can create a function that will return the pointer to the found node or NULL if not found
	struct query *qry_ptr = search_query(qry_txt);
	
	if (qry_ptr != NULL)
	{
		// Insert code to update staus to 1=running only if query is in 0=submitted state
		if (qry_ptr->status == submitted)
		{
			qry_ptr->status = running;
			qry_ptr->start_time = get_gtod_clock_time();
		}
		else
			printf("%s is not in submitted state so cannot run", qry_txt);

		// After status change print the query node
		print_query(qry_ptr);		
	}
	else
		printf("%s query not found in the list",qry_txt);


}

void update_time_elapsed()
{
	printf("update_time_elapsed function called\n");
	
	// Insert code to go through each node and update the time elapsed for each query in 1=running state
	// Ideally this code will be executed as timer event through SIGNALS
	struct query *temp=head;
	while (temp != NULL)
	{
		if (temp->status == running)
			temp->time_elapsed = get_gtod_clock_time() - temp->start_time;
		temp = temp->next;
	}
	
	
}

void finish_query()
{
	printf("finish_query function called\n");
	
	char qry_txt[100];
	printf("Enter query:");
	scanf("%s", qry_txt);
	
	// Insert code to first search for the query text in the list
	// This code will be used multiple times so you can create a function that will return the pointer to the found node or NULL if not found
	struct query *qry_ptr = search_query(qry_txt);
	
	if (qry_ptr != NULL)
	{
		// Insert code to update staus to 2=completed only if query is in 1=running state
		if (qry_ptr->status == running)
			qry_ptr->status = completed;
		else
			printf("%s is not in running state so cannot be completed", qry_txt);

		// After status change print the query node
		print_query(qry_ptr);		
	}
	else
		printf("%s query not found in the list",qry_txt);

}

void stop_process()
{
	printf("stop_process function called\n");
	
	// Insert code to free all the nodes of the list and exit
	struct query *temp=head;
	while(temp!=NULL)
	{
		head = head->next;
		free(temp->query_text);
		free(temp);
		temp = head;
	}
	
	// print the list to make sure it is empty
	print_list();
	exit(0);
}

int main(int argc, char *argv[])
{
	void (*fns[7])() = {add_query, delete_query, start_query, update_time_elapsed, finish_query, print_list, stop_process };
	int i, ch;
	while (1)
	{
		printf("1 for Add Query\n");
		printf("2 for Delete Query\n");
		printf("3 for Start Query\n");
		printf("4 for Update Time Elapsed For All Running Queries\n");
		printf("5 for Finish Query\n");
		printf("6 for Print All Queries\n");
		printf("7 for Exit\n");
		printf("Enter operation to perform: ");
		scanf("%d", &ch);
		if (ch<1 || ch>7)
		{
			printf("%d invalid option\n", ch);
		}
		else
		{
			fns[ch-1]();
		}
	}
}