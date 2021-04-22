#include<stdio.h>
#include<stdlib.h>

#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
};

struct listNode * list;

void initializeList()
{
    list = 0;  //initially set to NULL
}

int insertItem(int item) //insert at the beginning of the linked list
{
	struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item ;
	newNode->next = list ; //point to previous first node
	list = newNode ; //set list to point to newnode as this is now the first node
	return SUCCESS_VALUE ;
}

int deleteItem(int item)
{
	struct listNode *temp, *prev ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) break ;
		prev = temp;
		temp = temp->next ; //move to next node
	}
	if (temp == 0) return NULL_VALUE ; //item not found to delete
	if (temp == list) //delete the first node
	{
		list = list->next ;
		free(temp) ;
	}
	else
	{
		prev->next = temp->next ;
		free(temp);
	}
	return SUCCESS_VALUE ;
}

struct listNode * searchItem(int item)
{
	struct listNode * temp ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) return temp ;
		temp = temp->next ; //move to next node
	}
	return 0 ; //0 means invalid pointer in C, also called NULL value in C
}

int insertLast(int item)
{
    struct listNode *newItem;
    newItem = (struct listNode*) malloc (sizeof(struct listNode)) ;
    if(list == NULL)
        list = newItem;
    else{
        struct listNode *temp = list;
        while(temp->next != 0){
            temp = temp->next;
        }
        newItem->item = item;
        newItem->next = NULL;
        temp->next = newItem;

    }
}

int insertBefore(int oldItem, int newItem)
{
    int flag = 0;
    struct listNode *prev;
    struct listNode *newNode;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = newItem;
    struct listNode *temp;
    temp = list;
    while(temp != 0){
        //prev = temp;
        if(temp->item == oldItem){
            flag = 1;
            break;
        }
       prev = temp;
       temp = temp->next;

    }
    if(flag == 1){
        if(temp == list){
            newNode->next = temp;
            list = newNode;
        }
        else{
            newNode->next = temp;
            prev->next = newNode;
        }

    }
    else printf("Not found\n");
    return SUCCESS_VALUE;


    //else printf("Not found.\n");

    //return SUCCESS_VALUE;

}

int deleteAfter(int item)
{
	int flag = 0;
    //struct listNode *prev;
    struct listNode *temp;
    temp = list;
    while(temp != 0){
        if(temp->item == item){
            flag = 1;
            break;
        }
       //prev = temp;
       temp = temp->next;
    }
    if(flag == 1){
        struct listNode *curr = temp->next;
        temp->next = temp->next->next;
        //temp->next = prev->next;
        free(curr);
    }
    else printf("Not found\n");
    return SUCCESS_VALUE;
}



int deleteLast()
{
    struct listNode *temp = list;
    struct listNode *prev = NULL;

    //temp = list;
    if(temp == 0)
        printf("List is Empty\n");
        return NULL_VALUE;
    while(temp->next != 0){
        prev = temp;
        temp = temp->next;
    }

    if(prev != NULL){
        prev->next = NULL;
    }
    free(temp);
    return SUCCESS_VALUE;
}

void printList()
{
    struct listNode * temp;
    temp = list;
    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->next;
    }
    printf("\n");
}


int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Insert Last. 5. Print. 6. Delete Last.\n");
        printf("7. Insert Before. 8. Delete After. 9. Exit.\n");
        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int item;
            scanf("%d", &item);
            insertLast(item);
        }
        else if(ch==5)
        {
            printList();
        }
        else if(ch==6)
        {
            deleteLast();
        }
        else if(ch==7)
        {
            int item1,item2;
            scanf("%d %d", &item1,&item2);
            insertBefore(item1,item2);
        }
        else if(ch == 8){
            int item;
            scanf("%d",&item);
            deleteAfter(item);
        }
        else if(ch == 9){
            break;
        }
    }

}

