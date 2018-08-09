#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node *left;
    struct node *right;
    int data;
}node;

int insert(node **, int);
node* new_node(int);
int print_postorder(node *);
node* delete(node *, int);
node* min_value_of_subtree(node *);

int main(void)
{
    int input[] = {25, 14, 44, 9, 20, 30, 66};
    int input_length = sizeof(input)/sizeof(int);
    
    node *header = NULL;
    int i;
    for(i = 0; i < input_length; i++)
    {
        insert(&header, *(input + i));
    }
    header = delete(header, 26);
    print_postorder(header);
    printf("\n");

}

node* delete(node *header, int key)
{
    if(header == NULL)
    {
        printf("your key is wrong!!!\n");
        return 0;
    }

    if(key < header->data)
    {
        header->left  = delete(header->left, key);
    }
    else if(key > header->data)
    {
        header->right = delete(header->right, key);
    }
    else
    {
        if(header->left == NULL)
        {
            node *temp = header->right;
            free(header);
            return temp;
        }
        else if(header->right == NULL)
        {
            node *temp = header->left;
            free(header);
            return temp;
        }

        node *temp = min_value_of_subtree(header->right);

        header->data = temp->data;

        header->right = delete(header->right, temp->data);
    }
    return header;
}


node* min_value_of_subtree(node *sub_header)
{
    node *current = sub_header;

    while(current->left != NULL)
    {
        current = current->left;
    }

    return current;
}


int insert(node **header, int value)
{
    node *new = new_node(value);

    if(*header == NULL)
    {
        *header = new;
    }
    else
    {
        if(value < (*header)->data)
        {
            insert(&((*header)->left), value);
        }
        else
        {
            insert(&((*header)->right), value);
        }
    }
}

node* new_node(int value)
{
    node *new = (node*)malloc(sizeof(node));
    new->left = new->right = NULL;
    new->data = value;

    return new;
}

int print_postorder(node *header)
{
    if(header != NULL)
    {
        print_postorder(header->left);
        print_postorder(header->right);
        printf("%d  ", header->data);
    }
}
