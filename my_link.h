#include <stdlib.h>
#include <stdio.h>

struct lnode
{
	char dirp[256];
	struct lnode *next;
};
typedef struct lnode node;

node *create()
{
	node *head;
	if ((head=(node *) malloc(sizeof(node)))==NULL)
	{
		perror("Failed to create Linklist");
		return NULL;
	}

	head->next=NULL;
	strcpy(head->dirp,"\0");

	return head;
}

void insert(node * head, char * newdir)
{
	node *p,*tmp,*q;
	p=head;
	q=p->next;

	while(q!=NULL && strcmp(q->dirp,newdir)<0)
	{
		p=q;
		q=q->next;
	}

	if ((tmp=(node *) malloc(sizeof(node)))==NULL)
	{
		perror("Failed to malloc for a node");
		return ;
	}

	tmp->next=q;
	p->next=tmp;
	strcpy(tmp->dirp,newdir);
}

int get_max_length(node * head)
{
	node *p;
	p=head;

	int max_length=0;
	if (p->next==NULL) return max_length;

	while(p->next!=NULL)
	{
		if(strlen(p->dirp)>max_length)
			max_length=strlen(p->dirp);
		p=p->next;
	}

	return max_length;
}

void display(node * head)
{
	node *p;
	p=head;
	int i=0;
	int max_length=get_max_length(head);


	if (p->next==NULL)
	{
		printf("The linklist is still empty.\n");
		return;
	}
	else 
	{	p=p->next;
		while(p!=NULL)
		{
			printf("%-*s",max_length+2,p->dirp);
			i++;
			if(i==8){printf("\n");i=0;}
			p=p->next;
		}
		printf("\n");
	}
	
}

void nfree(node * head)
{
	node *p,*q;
	p=head;
	while(p->next!=NULL)
	{
		q=p->next;
		p->next=q->next;
		free(q);
	}
	free(p);
}
