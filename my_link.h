#include <stdlib.h>
#include <stdio.h>
#include "stat_print.h"

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

void insert_by_name(node * head, char * newdir)
{
	node *p,*tmp,*q;
	p=head;
	q=p->next;

	while(q!=NULL && strcasecmp(q->dirp,newdir)<0)
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

void insert_by_time(char *path,node * head, char * newdir)
{
	node *p,*tmp,*q;
	p=head;
	q=p->next;

	while(q!=NULL)
	{
		unsigned long int mtime1,mtime2;
		mtime1=get_mtime(path,newdir);
		mtime2=get_mtime(path,q->dirp);
		if (mtime1>=mtime2)
			break;
		else
		{
			p=q;
			q=q->next;
		}
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

void display(char *path,node * head,int a,int i,int l,int t)
{
	node *p;
	p=head;
	int j=0;
	int max_length=get_max_length(head);

	int row=8;
	if (i!=0) row=6;


	if (p->next==NULL)
	{
		printf("The linklist is still empty.\n");
		return;
	}
	else 
	{	p=p->next;
//-----------------   normal  --------------------------
		if (a+l==0)
		{
			while(p!=NULL)
			{
				if (p->dirp[0]=='.')	//hidden files
				{
					p=p->next;
					continue;
				}					
			
				if (i!=0) 
					print_inode(path,p->dirp);

				printf("%-*s",max_length+2,p->dirp);
				j++;
				if(j==row){printf("\n");j=0;}
				p=p->next;
			}
		}
//-----------------  -a  all  -----------------------
		else if (a==1 && l==0)
		{
			while(p!=NULL)
			{	

				if (i!=0) 
					print_inode(path,p->dirp);

				printf("%-*s",max_length+2,p->dirp);
				j++;
				if(j==row){printf("\n");j=0;}
				p=p->next;
			}
		}
//-----------------  -l  list detail  -----------------------
		else if (l==1 && a==0)
		{
			while(p!=NULL)
			{	
				if (p->dirp[0]=='.')	//hidden files
				{
					p=p->next;
					continue;
				}	

				if (i!=0) 
					print_inode(path,p->dirp);

				print_stat(path,p->dirp);
				printf("%-*s",max_length+2,p->dirp);
				printf("\n");

				j++;
				p=p->next;
			}
		}
//-----------------  -al  all _list detail  -----------------------
		else if (l*a==1)
		{
			while(p!=NULL)
			{

				if (i!=0) 
					print_inode(path,p->dirp);

				print_stat(path,p->dirp);
				printf("%-*s",max_length+2,p->dirp);
				printf("\n");
				
				j++;
				p=p->next;
			}
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
