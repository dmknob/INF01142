#include <stdio.h>
#include "sched.h"

void thread1(int arg) {
	printf("1: Thread started with argument %d.\n", arg);
	int i;
	for (i=0; i<3; i++) {
		printf("1\n");
		so_yield();
	}
	printf("1: Finished with so_exit(23).\n");
	so_exit(23);
}

void thread2(int arg) {
	printf("2: Thread started with argument %d.\n", arg);
	int i, status;
	for (i=0; i<5; i++) {
		if (i==3) {
			printf("2: Waiting for %d to finish.\n", arg);
			so_join(arg, &status);
			printf("2: Gotten status %d.\n", status);
		}
		else {
			printf("2\n");
		}
		so_yield();
	}
	printf("2: Finished by returning.\n");
}

void thread3(int arg) {
	printf("2: Thread started with argument %d.\n", arg);
	int i, status;
	for (i=0; i<7; i++) {
		if (i==2) {
			printf("3: Waiting for %d to finish.\n", arg);
			so_join(arg, &status);
			printf("3: Gotten status %d.\n", status);
		}
		else {
			printf("3\n");
		}
		so_yield();
	}
	printf("3: Finished with so_exit(69).\n");
	so_exit(69);
}

int main() {
	int t1, t2, t3, s1, s2, s3;

	so_init();

	t1 = so_create(thread1, 42);
	t2 = so_create(thread2, t1);
	t3 = so_create(thread3, t2);

	so_join(t1, &s1);
	so_join(t2, &s2);
	so_join(t3, &s3);

	printf("Final values: %d %d %d\n", s1, s2, s3);

	return 0;
}
