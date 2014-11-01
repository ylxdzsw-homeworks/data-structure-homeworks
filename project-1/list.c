#include <stdio.h>
#include <stdlib.h>

#include "list.h"

typedef struct node{
	void* v;
	struct node* next;
} NODE;

typedef int (*funp1)(void*);
typedef int (*funp2)(void*,void*);

typedef struct config
{
	int size;
	funp2 equal;
	funp1 print;
} CONFIG;

int _size(NODE* h);
funp2 _equal(NODE* h);
funp1 _print(NODE* h);
NODE* reverse_iter(NODE* h);

int _size(NODE* h){
	return ((CONFIG*)(h->v))->size;
}
funp2 _equal(NODE* h){
	return ((CONFIG*)(h->v))->equal;
}
funp1 _print(NODE* h){
	return ((CONFIG*)(h->v))->print;
}

void* makelist(int size,void* equal,void* print){
	NODE* x = (NODE*)malloc(sizeof(NODE));
	x->v = malloc(sizeof(CONFIG));
	((CONFIG*)(x->v))->size = size;
	((CONFIG*)(x->v))->equal = (funp2)equal;
	((CONFIG*)(x->v))->print = (funp1)print;
	x->next = NULL;
	return (void*)x;
}

void* addto(void* v,void* h){
	NODE* p = (NODE*)h;
	while(p->next){
		p = p->next;
	}
	p->next = (NODE*)malloc(sizeof(NODE));
	p->next->next = NULL;
	p->next->v = v;
	return (NODE*)(p->next);
}

int delone(void* v,void* h){
	NODE* p = (NODE*)h;
	funp2 equal = _equal(p);
	NODE* temp;
	while(p->next){
		if((*equal)(p->next->v,v)){
			temp = p->next;
			p->next = p->next->next;
			free(temp);/*TODO*/
			return 1;
		}
	}
	return 0;
}

void* retrieve(unsigned int pos,void* h){
	NODE* p = (NODE*)h;
	while(pos--){
		if(p->next){
			p = p->next;
		}else{
			return NULL;
		}
	}
	return p->v;
}

unsigned int find(void* v,void* h){
	NODE* p = (NODE*)h;
	funp2 equal = _equal(p);
	unsigned int count = 0;
	while(p->next){
		count++;
		p=p->next;
		if((*equal)(p->v,v)){
			return count;
		}
	}
	return 0u;
}

unsigned int getlength(void* h){
	NODE* p = (NODE*)h;
	unsigned int count = 0;
	while(p->next){
		p = p->next;
		count++;
	}
	return count;
}

void* reverse(void* h){
	NODE* temp;
	NODE* p = (NODE*)h;
	if(!(p->next)){
		return h;
	}
	temp = reverse_iter(p->next);
	p->next->next = NULL;
	p->next = temp;
	return (void*)p;
}

NODE* reverse_iter(NODE* h){
	NODE* temp;
	if(h->next){
		temp = reverse_iter(h->next);
		h->next->next = h;
		return temp;
	}
	return h;
}

void* nextone(void* node){
	NODE* p = (NODE*)node;
	return (void*)(p->next);
}

void* getvalue(void* node){
	NODE* p = (NODE*)node;
	return p->v;
}

int listprint(void* h){
	funp1 print = _print(h);
	NODE* p = (NODE*)h;
	while(p->next){
		(*print)(p->next->v);
		p = p->next;
	}
	return 0;
}