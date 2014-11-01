#include <stdio.h>
#include <stdlib.h>

#include "list.c"

int intEqual(void* a, void* b){
	int x = *((int*)a);
	int y = *((int*)b);
	if(a == b){
		return 1;
	}
	return 0;
}

int intprint(void* a){
	printf("%d\n", *((int*)a));
	return 1;
}

void* readFileIntoList(FILE* fp,void* list){
	void* p = list;
	int* x = (int*)malloc(sizeof(int));
	while(fscanf(fp,"%d",x) != EOF){
		p = addto((void*)x,p);
		x = (int*)malloc(sizeof(int));
	}
	free(x);
	return list;
}

int main(int argc, char const *argv[]){
	void* a = makelist(sizeof(int),(void*)intEqual,(void*)intprint);
	FILE* fp;
	if(argc > 1){
		if(!(fp = fopen(argv[1],"r"))){
			printf("%s\n", "file not exist");
			return 1;
		}
	}else{
		fp = stdin;
		printf("%s\n", "Input numbers and end with Ctrl+D(linux) / Ctrl+Z(windows)\nYou can include a file path as the first parameter instead of inputting in console\n");
	}
	a = readFileIntoList(fp,a);
	fclose(fp);
	printf("%s\n", "this is the list");
	listprint(a);
	reverse(a);
	printf("%s\n", "this is reversed list");
	listprint(a);
	return 0;
}
