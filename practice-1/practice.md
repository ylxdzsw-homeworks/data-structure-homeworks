---
title: "数据结构第一次作业"
author: "ylxdzsw"
date: "2014年10月3日"
output: pdf_document
---

###72页第4题
C语言代码如下(假定原本是降序排列):

	LIST merge(LIST a, LIST b){
		LIST L;
		position pa,pb;
		MakeNull(L);
		pa = First(a);
		pb = First(b);
		while(pa != End(pa,a) || pb != End(pb,b)){ //假设position类型可以用!=,==操作符来比较
			if(pa != End(pa,a) && pb != End(pb,b)){
				if(compare(Retrieve(pa,a),Retrieve(pb,b)) > 0){
					Insert(Retrieve(pa,a),End(L),L);
					pa = Next(pa,a);
				}else if(compare(Retrieve(pa,a),Retrieve(pb,b)) == 0){
					Insert(Retrieve(pa,a),End(L),L);
					Insert(Retrieve(pb,b),End(L),L);
					pa = Next(pa,a);
					pb = Next(pb,b);
				}else{
					Insert(Retrieve(pb,b),End(L),L);
					pb = Next(pb,b);
				}
			}else if(pa != End(pa,a)){
				Insert(Retrieve(pa,a),End(L),L);
				pa = Next(pa,a);
			}else{
				Insert(Retrieve(pb,b),End(L),L);
				pb = Next(pb,b);
			}
		}
	}

###72页第8题
使用以下脚本即可获得结果(JavaScript实现):

	a = "3*-y-a/y^2".split('')
	b = "3y-*ay2^/-".split('')
	iter = function(a,b,s,ans){
		if(!a.length){
			if(!s.length){
				return ans
			}
			ans += 'S'
			s.pop()
			return iter(a,b,s,ans)
		}
		if(s.length && s[s.length-1] == b[0]){
			ans += 'S'
			b.shift()
			s.pop()
			return iter(a,b,s,ans)
		}else if(a[0] == b[0]){
			ans += 'XS'
			a.shift()
			b.shift()
			return iter(a,b,s,ans)
		}else{
			ans += 'X'
			s.push(a.shift())
			return iter(a,b,s,ans)
		}
	}
	console.log(iter(a,b,[],""))

得到结果:
	XSXXXSSSXXSXXSXXSSSS

###73页第15题
在单向链表的基础上使尾节点的next指向头结点即可。
遍历算法C语言代码如下:

	typedef void* (*funp)(void*);
	typedef struct node{
		void* value;
		struct node* next;
	} NODE;

	void traverse(NODE* start, funp f){ //这里f是要应用的函数指针
		NODE* p = start->next;
		(*f)(start->value);
		while(p != start){
			(*f)(p->value);
			p = p->next;
		}
	}

###73页第18题
C语言代码如下:

	typedef void* (*funp)(void*, void*);
	typedef struct node{
		void* value;
		struct node* next;
	} NODE;

	int search(void* e, NODE* h, funp equal){ //这里equal是判断两个元素是否相等的函数指针
		NODE* p = h; //这里h是表头结点，第一个数据从h->next开始
		NODE* temp;
		int pos = 1;
		while(p->next){
			if((*equal)(e,p->next->value)){
				return pos;
			}
			p = p->next;
			pos++;
		}
		//if arrived here, p->next==NULL, so insert here
		if((NODE*)0==(temp = (NODE*)malloc(sizeof(NODE)))){
			return -1;
		}
		temp->value = e;
		temp->next = NULL;
		p->next = temp;
		return pos; //返回插入后的位置，即表尾位置
	}

###73页第19题
本题可由复制链表的函数稍加改造得到，C语言代码如下:

	typedef void* (*funp)(void*, void*);
	typedef struct node{
		void* value;
		struct node* next;
	} NODE;
	/*
	 *	返回值是一个长度为2的NODE*型数组,代表拆分后的两个头结点
	 *	copy是用于复制元素值的函数指针，原型为void copy(void* from, void* to);
	 */
	NODE** split(NODE* h,funp copy){
		NODE** ha = (NODE**)malloc(2 * sizeof(NODE*)); //ha[0]和ha[1]分别是拆分后的两个头结点
		NODE** pa = (NODE**)malloc(2 * sizeof(NODE*));
		NODE* p = h;
		int i = 0; //用来指示奇偶,每次循环后会执行i = !i
		ha[0] = (NODE*)malloc(sizeof(NODE));
		ha[0]->value = (int*)malloc(sizeof(int));
		*((int*)(ha[0]->value)) = 0;
		ha[0]->next = NULL;
		ha[1] = (NODE*)malloc(sizeof(NODE));
		ha[1]->value = (int*)malloc(sizeof(int));
		*((int*)(ha[1]->value)) = 0;
		ha[1]->next = NULL;
		pa[0] = ha[0];
		pa[1] = ha[1];
		whlie(p->next){
			p = p->next;
			pa[i]->next = (NODE*)malloc(sizeof(NODE));
			pa[i] = pa[i]->next;
			copy(p->value,pa[i]->value);
			pa[i]->next = ha[i]->next; //让尾节点的next指向第一个节点，构成循环链表
			(*((int*)(ha[i]->value)))++ //环形表的长度计数器+1
			i = !i; //这是共用一个循环而又能保证奇偶项被拆分到不同的环形表的关键,也是我觉得我这个函数的设计中最精妙的地方
		}
		free(pa);
		return ha;
	}

###73页第22题
C语言代码如下:

	typedef struct node{
		char value;
		struct node* next;
	} mychar;

	mychar* Substr(mychar* S, unsigned int m, unsigned int n){
		mychar* R = (mychar*)malloc(sizeof(mychar));
		mychar *p,*q;
		R->next = (mychar*)malloc(sizeof(mychar));
		R->next->value = (char)0;
		R->next->next = (mychar*)0;
		p = S->next;
		q = R->next;
		while(p && p->value){ //假设NULL='\0'=false
			if(m){
				m--;
				continue;
			}
			if(n){
				n--;
				q->value = p->value; //char型可以直接用=复制
				q->next = (mychar*)malloc(sizeof(mychar));
				q->next->value = (char)0;
				q->next->next = (mychar*)0;
				continue;
			}
			break;
		}
		if(m || n){
			//释放内存略
			return NULL;
		}
		return R;
	}
