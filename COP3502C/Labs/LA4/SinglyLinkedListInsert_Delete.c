#include<stdio.h>
#include<stdlib.h>
#include "main.h"
 typedef struct node{
	int data;
	struct node *next;
}node;

//this function takes an item and insert it in the linked list pointed by root.
node*  insert_front(node *root, int item)
{
	node *temp;
	//create a new node and fill-up the node
	temp= (node *) malloc(sizeof(node));
	temp->data=item;
	temp->next=NULL;
	if(root==NULL) //if there is no node in the linked list
        root=temp;
    else //there is an existing linked list, so put existing root after temp
    {
        temp->next = root; //put the existing root after temp
        root = temp; //make the temp as the root!
    }
  return root;
}

node *reverse(node *head) {
	node *prev = NULL;
	node *cur = head;
	node *next = NULL;

	while (cur != NULL) {
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}

	return prev;
}

void insertToPlace(node *head, int val, int place) {
	node *temp = (node *) malloc(sizeof(node));
	temp->data = val;
	temp->next = NULL;

	node *cur = head;
	int pos = 1;

	while (cur->next != NULL && pos < place - 1) {
		cur = cur->next;
		pos+=1;
	}

	temp->next = cur->next;
	cur->next = temp;
}

void display(node* t)
{
  printf("\nPrinting your linked list.......");

	while(t!=NULL)
	{
		printf("%d ",t->data);
		t=t->next;
	}

}
int main()
{
	node *root=NULL; //very important line. Otherwise all function will fail
	node *t;
	int ch, ele, val, place;
	while(1)
	{
		printf("\nMenu: 1. insert at front, 2. reverse list 3. Insert to place 0. exit: ");
	    scanf("%d",&ch);
		if(ch==0)
		{
			printf("\nGOOD BYE>>>>\n");
			break;
		}
		if(ch==1)
		{
			printf("\nEnter data(an integer): ");
			scanf("%d",&ele);
			root = insert_front(root, ele);

      		display(root);
		}
		if(ch==2)
		{
			root = reverse(root);
			printf("\nList reversed.");
			
      		display(root);
		}
		if(ch==3)
		{
			printf("\nEnter data (an integer) and place (>1) separated by space: ");
			scanf("%d %d", &val, &place);
			if (root == NULL || place <= 1) {
				printf("Empty list or place is invalid");
				display(root);
			} else {
				insertToPlace(root, val, place);
				display(root);
			}
		}
	}
  	return 0;
}
