#include<stdio.h>
#include<stdlib.h>

#define FALSE_VALUE 0
#define TRUE_VALUE 1

struct treeNode
{
    int item;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};

struct treeNode * root;


void initializeTree()
{
    root = 0;
}


struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};


struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    return node;
};

struct treeNode * insertItem(struct treeNode * node, int item)
{
    if(node==0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item==item) return 0; //already an item exists, so return NULL

    if(item<node->item && node->left==0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        return newNode;
    }

    if(item>node->item && node->right==0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        return newNode;
    }

    if(item<node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
}



int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}


int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node)
{
    if(node==0) return 0;
    int ls = getSize(node->left);
    int rs = getSize(node->right);
    int Size = ls + rs + 1;
    return Size;

}

int calcNodeDepth(struct treeNode * node) //return depth of a node
{
    //write your codes here
    if(root == 0) return -1;
    int value;
    node->item = value;
    int c = 0;
    struct treeNode * res = searchItem(root, node->item);
    if(res != 0) {
        struct treeNode *temp;
        temp = node;
        while(temp != res){
            if(value < temp->item){
                temp = temp->left;
            }
            else{
                temp = temp->right;
            }
            c++;

        }
        printf("Depth is %d\n",c);
    }
    else printf("Not found.\n");


}


int calcDepth(int item)//return depth of an item in the tree
{
    //write your codes here
 /*   int height = calcNodeHeight(root);
    int height1 = calcHeight(item);
    int depth = height - height1;
    return depth;*/
    if(root == 0) return -1;
    int c = 0;
    struct treeNode * res = searchItem(root, item);
    if(res!=0) {
        struct treeNode *temp;
        temp = root;
        while(temp != res){
            if(item < temp->item){
                temp = temp->left;
            }
            else{
                temp = temp->right;
            }
            c++;

        }
        printf("Depth of item is %d\n",c);
    }
    else printf("Not found.\n");
}

int deleteItem(struct treeNode * node, int item)
{
    //write your code here, return TRUE, FALSE
    //struct treeNode *temp;
    int flag = 0;
    struct treeNode *temp = node;
    struct treeNode *prev = NULL;
    if(temp == NULL){
        printf("Deletion cannot be possible\n");
        return 0;
    }
    else if(temp == root && getSize(root) == 1){
        root = NULL;
        printf("Tree becomes Empty\n");
        return 0;
    }
    while(temp != NULL){
        if(temp->item == item){
            flag = 1;
            break;
        }
        else{
            prev = temp;
            if(item < temp->item){
                temp = temp->left;
            }
            else temp = temp->right;
        }
    }
    if(flag == 1){
        if(temp->left == NULL && temp->right != NULL){
            if(prev->left == temp){
                struct treeNode *curr = temp;
                prev->left = temp->right;
                free(curr);
            }
            else if(prev->right == temp){
                struct treeNode *curr = temp;
                prev->right = temp->right;
                free(curr);

            }
        }
        else if(temp->right == NULL && temp->left != NULL){
            if(prev->left == temp){
                struct treeNode *curr = temp;
                prev->left = temp->left;
                free(curr);
            }
            else if(prev->right == temp){
                struct treeNode *curr = temp;
                prev->right = temp->left;
                free(curr);

            }

        }
        else if(temp->left == NULL && temp->right == NULL){
            if(prev->left == temp)
                prev->left = NULL;
            else prev->right = NULL;
            free(temp);
        }
        else if(temp->left != NULL && temp->right != NULL){
            struct treeNode *temp1 = temp->right;
            if(temp1->left != NULL){
                struct treeNode *curr;
                struct treeNode *prevcurr;
                prevcurr = temp1;
                curr = temp1->left;
                while(curr->left != NULL){
                    prevcurr = curr;
                    curr = curr->left;
                }
                temp->item = curr->item;
                prevcurr->left = NULL;
                free(curr);
            }
            else if(temp1->left == NULL && temp1->right != NULL){
                struct treeNode *curr;
                struct treeNode *prevcurr;
                prevcurr = temp1;
                curr = prevcurr->right;
                temp->item = prevcurr->item;
                temp->right = prevcurr->right;
                free(prevcurr);
                //temp->right = temp1->right;
            }
            else if(temp1->left == NULL && temp1->right == NULL){
                struct treeNode *curr;
                //struct treeNode *prevcurr;
                //prevcurr = temp1;
                curr = temp1;
                temp->item = curr->item;
                temp->right = NULL;
                free(curr);
            }


        }
    }

    else printf("Not found.\n");

}



int getMinItem() //returns the minimum item in the tree
{
    //write your codes here
    if(root == NULL){
        printf("Tree is empty\n");
        return -1;
    }
    else{
        struct treeNode *temp;
        temp = root;
        while(temp->left != NULL)
            temp = temp->left;
        int m = temp->item;
        return m;
    }
}

int getMaxItem() //returns the maximum item in the tree
{
    //write your codes here
    if(root == NULL){
        printf("Tree is empty\n");
        return -1;
    }
    else{
        struct treeNode *temp;
        temp = root;
        while(temp->right != NULL)
            temp = temp->right;
        int m = temp->item;
        return m;
    }
}

int rangeSearch(struct treeNode *node, int leftBound, int rightBound)
{
    //write your codes here
    int rangeCount;
    if (node == 0) return 0;

    int leftRange = rangeSearch(node->left, leftBound, rightBound);
    int rightRange = rangeSearch(node->right, leftBound, rightBound);

    if (node->item <= rightBound && node->item >= leftBound)
         rangeCount = 1 + leftRange + rightRange;

    else if (node->item < leftBound)
         rangeCount = rightRange;

    else rangeCount = leftRange;

    return rangeCount;
}

void printInOrder(struct treeNode * node, int height)
{
    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0;i<height;i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}

int getSubtreeSum(struct treeNode *ptr){
    if(ptr == NULL){
        return 0;
    }
    else return getSubtreeSum(ptr->left)+ptr->item+getSubtreeSum(ptr->right);
}

int SubtreeSum(int item){
    int s;
    struct treeNode *res = searchItem(root, item);
    if(res != 0){
        s = getSubtreeSum(res);
        return s;
    }
    else printf("Not found\n");
}



int main(void)
{
    initializeTree();
    while(1)
    {
        printf("1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. 6. PrintInOrder. \n");
        printf("7. Print depth of the item. 8.Print depth of the node. 9. Minimum value \n");
        printf("10. Maximum value. 11. Size of a tree 12.Range search 13. Subtree Sum\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(root, item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(root, item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
        }
        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n", item, height);
        }
        else if(ch==6)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch == 7){
            int item;
            scanf("%d", &item);
            calcDepth(item);
            //printf("depth of %d = %d\n", item, d);
        }
        else if(ch == 8){
            int item;
            scanf("%d",&item);
            struct treeNode *temp;
            temp->item = item;
            calcDepth(item);
            //printf("depth of %d = %d\n", item, d);
        }
        else if(ch==9){
            int s = getMinItem();
            printf("Minimum item is %d\n",s);

        }
        else if(ch==10){
            int s = getMaxItem();
            printf("Maximum item is %d\n",s);

        }
        else if(ch==11)
        {
            int sz = getSize(root);
            printf("Size of a tree is %d\n",sz);
        }
        else if(ch==12)
        {
            int a,b;
            scanf("%d %d",&a,&b);
            if(a<b){
                int range= rangeSearch(root,a,b);
                printf("range is %d\n",range);
            }
            else printf("Invalid range\n");
        }
        else if(ch == 13){
            int a;
            scanf("%d",&a);
            int s = SubtreeSum(a);
            printf("%d\n",s);
        }
    }

}
