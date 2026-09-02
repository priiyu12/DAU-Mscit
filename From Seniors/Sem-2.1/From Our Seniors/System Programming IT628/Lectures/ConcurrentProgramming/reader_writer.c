#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

/* a linked list node */
struct node_t {
  int data;
  struct node_t* next;
};

/* add an element at front of list */
void list_insert(struct node_t** head, int data) {
  struct node_t* new = malloc(sizeof(struct node_t));
  new->data = data;
  new->next = *head;
  *head = new;
}

/* remove the first instance of an element from a list */
void list_remove(struct node_t** head, int data) {
  struct node_t* previous = NULL;
  struct node_t* current = *head;
  while (current) {
	if (current->data == data) {
	  if (previous) {
		previous->next = current->next;
	  } else {
		*head = current->next;
	  }
	  free(current);
	  return;
	}
	current = current->next;
  }
}

/* print a linked list to the screen */
void list_print(struct node_t* head) {
  struct node_t* current = head;
  while (current) {
	printf("%ld:%d ", pthread_self(), current->data);
	current = current->next;
  }
  printf("\n");
}

void delete_all_nodes(struct node_t* head)
{
	struct node_t* current = head;
	while (current) {
		printf("%d ", current->data);
		head = head->next;
		free(current);
		current = head;
  }
  printf("\n");
}

/* our list is global */
struct node_t* head = NULL;

/* thread function which inserts and removes elements */
void* writer_no_lock(void* idp) {
  /* continually insert and remove items */
  while (1) {
	list_insert(&head, rand( ) % 100);
	list_insert(&head, rand( ) % 100);
	list_insert(&head, rand( ) % 100);
	list_remove(&head, rand( ) % 100);
  }

  return NULL;
}

/* thread function which prints the list */
void* reader_no_lock(void* idp) {
  /* continually print the list */
  while (1) {
	list_print(head);
  }

  return NULL;
}


/*
Mutex Solution
We could prevent this with a mutex. In this case, we would put a lock/unlock around every access to the linked list.
*/
/* a mutex */
pthread_mutex_t lock;

/* thread function which inserts and removes elements */
void* writer_mutex_lock(void* idp) {
  /* continually insert and remove items */
  while (1) {
	pthread_mutex_lock(&lock);
	list_insert(&head, rand( ) % 100);
	list_insert(&head, rand( ) % 100);
	list_insert(&head, rand( ) % 100);
	list_remove(&head, rand( ) % 100);
	pthread_mutex_unlock(&lock);
  }

  return NULL;
}

/* thread function which tests if elements are in the list */
void* reader_mutex_lock(void* idp) {
  /* continually print the list */
  while (1) {
	pthread_mutex_lock(&lock);
	list_print(head);
	pthread_mutex_unlock(&lock);
  }

  return NULL;
}

/*
Reader-Writer Locks Solution
We can replace the mutexes with read-write locks
*/
/* a read-write lock */
pthread_rwlock_t rw_lock;

/* thread function which inserts and removes elements */
void* writer_rw_lock(void* idp) {
  /* continually insert and remove items */
  int i=0;
  for (i=0; i<100; i++)
  {
	pthread_rwlock_wrlock(&rw_lock);
	list_insert(&head, rand( ) % 100);
	list_insert(&head, rand( ) % 100);
	list_insert(&head, rand( ) % 100);
	list_remove(&head, rand( ) % 100);
	pthread_rwlock_unlock(&rw_lock);
	sleep(0.5);
  }

  return NULL;
}

/* thread function which tests if elements are in the list */
void* reader_rw_lock(void* idp) {
  /* continually print the list */
  int i=0;
  for (i=0; i<100; i++)
  {
	pthread_rwlock_rdlock(&rw_lock);
	list_print(head);
	pthread_rwlock_unlock(&rw_lock);
	sleep(0.5);
  }

  return NULL;
}

int main()
{
	int ret;
	pthread_t thread1, thread2, thread3;
	ret = pthread_rwlock_init(&rw_lock, NULL);
	pthread_create (&thread1, NULL, reader_rw_lock, NULL);
	pthread_create (&thread3, NULL, reader_rw_lock, NULL);
	pthread_create (&thread2, NULL, writer_rw_lock, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread2, NULL);
	delete_all_nodes(head);
	ret = pthread_rwlock_destroy(&rw_lock);
}