#include <stdio.h>
#include <stdlib.h>

#include "list.c"

typedef struct polyterm
{
	int c;
	int e;
} TERM;

int polyEqual(void* a,void* b){
	TERM* x = (TERM*)a;
	TERM* y = (TERM*)b;
	if(x->c == y->c && x->e == y->e){
		return 1;
	}
	return 0;
}

int polyprint(void* a){
	TERM* x = (TERM*)a;
	printf("%d,%d\n", x->c, x->e);
	return 1;
}

int polycopy(void* from, void* to){
	TERM* a = (TERM*)from;
	TERM* b = (TERM*)to;
	b->e = a->e;
	b->c = a->c;
	return 1;
}

void* readFileIntoList(FILE* fp,void* list){
	void* p = list;
	int x,y;
	TERM* t;
	while(fscanf(fp,"%d%*c%d",&x,&y) != EOF){
		t = (TERM*)malloc(sizeof(TERM));
		t->c = x;
		t->e = y;
		p = addto((void*)t,p);
	}
	return list;
}

void* add2polylists(void* a, void* b){
	void* c = makelist(sizeof(TERM),(void*)polyEqual,(void*)polyprint);
	void* na = nextone(a);
	void* nb = nextone(b);
	void* nc = c;
	TERM *av,*bv;
	void* temp;
	while(na || nb){
		temp = malloc(sizeof(TERM));/*this will be added to the list*/
		if(na && nb){
			av = (TERM*)getvalue(na);
			bv = (TERM*)getvalue(nb);
			if(av->e > bv->e){
				polycopy((void*)av,temp);
				nc = addto(temp,nc);
				na = nextone(na);
			}else if(av->e == bv->e){
				polycopy((void*)av,temp);
				((TERM*)temp)->c += bv->c;
				if(((TERM*)temp)->c){
					nc = addto(temp,nc);
				}else{
					free(temp);
				}
				na = nextone(na);
				nb = nextone(nb);
			}else{
				polycopy((void*)bv,temp);
				nc = addto(temp,nc);
				nb = nextone(nb);
			}
		}else if(na){
			polycopy(getvalue(na),temp);
			nc = addto(temp,nc);
			na = nextone(na);
		}else{
			polycopy(getvalue(nb),temp);
			nc = addto(temp,nc);
			nb = nextone(nb);
		}
	}
	return c;
}

int main(int argc, char const *argv[]){
	void* p1 = makelist(sizeof(TERM),(void*)polyEqual,(void*)polyprint);
	void* p2 = makelist(sizeof(TERM),(void*)polyEqual,(void*)polyprint);
	FILE *fp1,*fp2;
	char const *path1,*path2;
	if(argc > 2){
		path1 = argv[1];
		path2 = argv[2];
	}else{
		path1 = "./polylist1.txt";
		path2 = "./polylist2.txt";
	}
	if(!(fp1 = fopen(path1,"r")) || !(fp2 = fopen(path2,"r"))){
		printf("%s\n", "file not exist");
		return 1;
	}
	readFileIntoList(fp1,p1);
	readFileIntoList(fp2,p2);
	fclose(fp1);
	fclose(fp2);
	printf("%s\n", "this is the first polynomial");
	listprint(p1);
	printf("%s\n", "this is the second polynomial");
	listprint(p2);
	printf("%s\n", "this is the sum polynomial");
	listprint(add2polylists(p1,p2));
	return 0;
}
