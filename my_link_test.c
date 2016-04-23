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

void display(node * head)
{
	node *p;
	p=head;

	if (p->next==NULL)
	{
		printf("The linklist is still empty.\n");
		return;
	}
	else 
	{	p=p->next;
		while(p!=NULL)
		{
			printf("%s ",p->dirp);
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

int main()
{
	node *cc;
	cc=create();
	display(cc);
	while(1)
	{
		char s[256];
		scanf("%s",s);
		if (strcmp(s,"!")!=0)
			insert(cc,s);

		else break;
	}

	display(cc);
	nfree(cc); 
	return 0;

}