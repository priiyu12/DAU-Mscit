#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct query
{
	int query_id;	// unique id
	char* query_text;	// actual query text
	int status;	// 0=submitted, 1=running, 2=completed
	int time_elapsed;	// time in microsec it took to run the query
	struct query *next;	// if you are using singly or doubly linked list
	struct query *prev;	// if you are using doubly linked list
};

struct query *head=NULL;

void print_query(struct query *qry)
{
	printf("Query ID:%d, Query Status: %s, Query Text:%s\n", qry->query_id, qry->status==1?"Running":qry->status==0?"submitted":"completed", qry->query_text);
}

void print_list()
{
	struct query *tmp=head;
	while (tmp!=NULL)
	{
		printf("Query ID:%d, Query Status: %s, Query Text:%s\n", tmp->query_id, tmp->status==1?"Running":tmp->status==0?"submitted":"completed", tmp->query_text);
		tmp = tmp->next;
	}
}

struct query *search_query(char *qry_txt)
{
	struct query *found=head;
	
	// Insert code here to look for qry_txt in each node and set the pointer to that node in found if qry_txt is found otherwise set found=NULL
	
	
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
	new->query_text = (char *)malloc(sizeof(strlen(qry_txt)));
	strcpy(new->query_text, qry_txt);
	new->status = 0;
	new->time_elapsed = 0;
	
	// Insert your code to add node to the list
	
	
	// After inserting query to the list print the whole list
	print_list();
	
	
}

void delete_query()
{
	printf("delete_query function called\n");

	// Insert code to delete all the query nodes with 2=completed status
	
	
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
		// Insert code to update staus to 1=running
		
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
		// Insert code to update staus to 2=completed
		
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
}

int main(int argc, char *argv[])
{
	void (*fns[6])() = {add_query, delete_query, start_query, update_time_elapsed, finish_query, stop_process };
	int i, ch;
	while (1)
	{
		printf("1 for Add Query\n");
		printf("2 for Delete Query\n");
		printf("3 for Start Query\n");
		printf("4 for Update Time Elapsed For All Running Queries\n");
		printf("5 for Finish Query\n");
		printf("6 for Exit\n");
		printf("Enter operation to perform: ");
		scanf("%d", &ch);
		if (ch<1 || ch>6)
		{
			printf("%d invalid option\n", ch);
		}
		else
		{
			fns[ch-1]();
		}
	}
}