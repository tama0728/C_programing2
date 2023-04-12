#include<stdio.h>

void a(){
	static int i = 10;
	//int i = 10;
	printf("%d\n", i++);
}

int main(){
	for (int i = 0; i < 3; i++)
		a();
	return 0;
}

