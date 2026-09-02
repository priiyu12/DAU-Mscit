// use test_atomic_makefile to create kernel object (ko) file

#include<linux/kernel.h>

#include<linux/module.h> 

atomic_t *test; 

int test_init(void) 

{

	atomic_set(test,2);

	atomic_add(2,test);

	return 0;

}

void test_exit(void)

{

}

module_init(test_init);

module_exit(test_exit);

MODULE_LICENSE("GPL");