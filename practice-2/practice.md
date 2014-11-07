---
title: "数据结构第二次作业"
author: "ylxdzsw"
date: "2014年11月7日"
output: pdf_document
---

###121页第12题

完整带主函数C语言代码如下(关键部分为bianhao函数):

	#include <stdio.h>
	#include <stdlib.h>

	#define NODE_NUM_MAX 10

	typedef struct {
		int left;
		int right;
		int level;
	}NODE;

	int readFile(FILE* fp, NODE* a)
	{
		int i=1;
		while(i<NODE_NUM_MAX && fscanf(fp,"%d%*c%d",&(a[i].left),&(a[i].right)) != EOF){
	        i++;
		}
		return i-1;
	}

	int bianhao(NODE* a, int now, int num)
	{
		int heightl,heightr;
		if(now){
			a[now].level = num;
	        heightl = bianhao(a,a[now].left,num+1);
	        heightr = bianhao(a,a[now].right,num+1);
			return heightl>heightr?heightl:heightr;
		}
		return num-1;
	}

	int main(int argc, char const *argv[])
	{
		FILE* fp;
		int levels,nums;
		NODE a[NODE_NUM_MAX];
		if(argc > 1){
			if(!(fp = fopen(argv[1],"r"))){
				printf("%s\n", "file not exist");
				return 1;
			}
		}else{
			fp = stdin;
			printf("%s\n", "Input numbers and end with Ctrl+D(linux) / Ctrl+Z(windows)\nYou can include a file path as the first parameter instead of inputting in console\n");
		}
		nums = readFile(fp,a);
		levels = bianhao(a,1,1);
	    printf("levels=%d\n",levels);
	    for(int i = 1; i <= nums;i++){
			printf("node %d is in level %d\n",i,a[i].level);
	    }
	    return 0;
	}

###121页第13题

证明：高度为h的二叉树其结点总数最多为(2^h)-1,而叶结点最多为2^(h-1),根节点为1,所以其内部节点的个数小于2^(h-1)-1。

###121页第14题

完整带主函数C语言代码如下(关键部分为findMW函数)：

	#include <stdio.h>
	#include <stdlib.h>

	#define nnode 10

	typedef struct {
		int left;
		int right;
		int lw;
		int rw;
		int mw;
	}NODE;

	int readFile(FILE* fp, NODE* a)
	{
		int i=1;
		while(i<nnode && fscanf(fp,"%d%*c%d%*c%d%*c%d",&(a[i].left),&(a[i].right),&(a[i].lw),&(a[i].rw)) != EOF){
	        i++;
		}
		return i-1;
	}

	int findMW(NODE* a, int now, int num)
	{
		int weightl,weightr;
		if(now){
	        weightl = a[now].lw + findMW(a,a[now].left,num+1);
	        weightr = a[now].rw + findMW(a,a[now].right,num+1);
			a[now].mw = weightl>weightr?weightl:weightr;
			return a[now].mw;
		}
		a[now].mw = 0;
		return a[now].mw;
	}

	int main(int argc, char const *argv[])
	{
		FILE* fp;
		int nums;
		NODE a[nnode];
		if(argc > 1){
			if(!(fp = fopen(argv[1],"r"))){
				printf("%s\n", "file not exist");
				return 1;
			}
		}else{
			fp = stdin;
			printf("%s\n", "Input numbers and end with Ctrl+D(linux) / Ctrl+Z(windows)\nYou can include a file path as the first parameter instead of inputting in console\n");
		}
		nums = readFile(fp,a);
		findMW(a,1,1);
	    for(int i = 1; i <= nums;i++){
			printf("node %d 's max weight is %d\n",i,a[i].mw);
	    }
	    return 0;
	}

###121页第16题

算法简要描述：如果当前节点未被遍历，则将指针指向他的左儿子；否则，交换左右儿子。当两个儿子都已遍历时回溯到父节点。  

C语言代码关键部分如下：
	
	typedef struct node{
		struct node* left;
		struct node* right;
		int tag; //假定所有节点的tag在初始化时已赋值为0
		void* data;
	}NODE;

	NODE* farther(NODE* tr, NODE* p)
	{
		NODE* q;
		while(true){
			if(q->left == p)
			return q;
		}
	}
	mapNode(NODE* tr)
	{
		NODE* p = tr;
		NODE* temp;
		int dir = 1;//0表示上一步是返回，1表示上一步是深入
		while(p!=tr || dir!=0){
			if(dir==0){
				if(p->right && p->right->tag==0){
					VISIT(p->data); //遍历到了这个节点
					temp=p->right;
					p->right=p->left;
					p->left=temp;
					dir=1;
					continue;
				}else{
					p->tag = 1;
					p = farther(tr,p);
					continue;
				}
			}
			if(p->left==NULL){
				if(p->right==NULL){
					VISIT(p->data);
					p->tag=1;
					p = farther(tr,p);
					dir=0;
					continue;
				}
				temp=p->right;
				p->right=p->left;
				p->left=temp;
				continue;
			}
			if(p->left->tag==1){
				dir=0;
				continue;
			}
			p = p->left;
		}
	}

###121页第34题

完整带主函数C语言代码如下(关键部分为printTree函数):

	#include <stdio.h>
	#include <stdlib.h>

	typedef struct node{
		struct node* left;
		struct node* right;
		int key;
	}NODE;

	void readTree(FILE* fp, NODE* a)
	{
		int tmp;
		printf("请输入节点%d的『左』儿子(#表示无左儿子):",a->key);
		if(fscanf(fp,"%d",&tmp)==1){
			a->left = (NODE*)malloc(sizeof(NODE));
			a->left->key = tmp;
			readTree(fp,a->left);
		}else{
			a->left=NULL;
			getchar();
		}
		printf("请输入节点%d的『右』儿子(#表示无右儿子):",a->key);
		if(fscanf(fp,"%d",&tmp)==1){
			a->right = (NODE*)malloc(sizeof(NODE));
			a->right->key = tmp;
			readTree(fp,a->right);
		}else{
			a->right=NULL;
			getchar();
		}
		return;
	}

	void printTree(NODE* a)
	{
		if(!a){
			return;
		}
		if(!a->left && !a->right){
			printf("(%d)",a->key);
			return;
		}
		printf("(%d:",a->key);
		printTree(a->left);
		printf(",");
		printTree(a->right);
		printf(")");
	}

	int main(int argc, char const *argv[])
	{
		FILE* fp;
		NODE* a = (NODE*)malloc(sizeof(NODE));
		if(argc > 1){
			if(!(fp = fopen(argv[1],"r"))){
				printf("%s\n", "file not exist");
				return 1;
			}
		}else{
			fp = stdin;
			printf("%s\n", "按照提示先根顺序输入二叉树\n可以以文件作为第一个参数代替输入\n");
		}

		printf("输入根节点:");
		int tmp;
		fscanf(fp,"%d",&tmp);
		a->key = tmp;

		readTree(fp,a);
		printTree(a);
	    return 0;
	}

###121页第36题

使用如下javascript代码建立哈夫曼树:

	Array.prototype.createHuffmanTree = function() {
		var Node = function(x) {
			return {
				key:x[0],
				value:x[1],
				left:null,
				right:null
			};
		}
		var nodes = this.map(Node);
		while(nodes.length > 1) {
			nodes.sort(function(a, b) {
				return a.value - b.value;
			});
			var one = nodes.shift();
			var two = nodes.shift(); 
			var root = Node([false,one.value+two.value])
			root.left = one;
			root.right = two; 
			nodes.unshift(root); 
		} 
		return nodes[0];
	}
	var test = [['a',0.07],
				['b',0.09],
				['c',0.12],
				['d',0.22],
				['e',0.23],
				['f',0.27]].createHuffmanTree();
	(function printTree(x,code){
		if(x.key){console.log(x.key+':'+code);}
		if(x.left){printTree(x.left,code+'0')}
		if(x.right){printTree(x.right,code+'1')}
	})(test,'');

得到以下输出：

	d:00
	e:01
	f:10
	c:110
	a:1110
	b:1111

画出的哈夫曼编码树如下:
	略