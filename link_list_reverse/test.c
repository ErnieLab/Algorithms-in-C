#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node *next;
    int data;
}node;

int en_queue(node **, int);
node* new_node(int);
int display(node *);
int reverse_iterative(node **);
node* reverse_recursive(node *);

int main(void)
{
    node *header = NULL;

    int i;
    for(i = 0; i < 10; i++)
    {
        en_queue(&header, i+1);
    }
    //reverse_iterative(&header);
    header = reverse_recursive(header);
    display(header);
}

int reverse_iterative(node **header)
{
    node *next = NULL; 
    node *curr = *header;
    node *prev = NULL;

    while(curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    *header = prev;
}

node *reverse_recursive(node *header)
{
    if(header->next == NULL)
    {
        return header;
    }
    node *revheader = reverse_recursive(header->next);
    header->next->next = header;
    header->next = NULL;
    return revheader;
}

int en_queue(node **header, int value)
{
    node *new = new_node(value);

    if(*header == NULL)
    {
        *header = new;
    }
    else
    {
        node *temp = *header;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = new;
    }
}

node* new_node(int value)
{
    node *new = (node*)malloc(sizeof(node));
    new->next = NULL;
    new->data = value;

    return new;
}

int display(node *header)
{
    if(header == NULL)
    {
        printf("NULL\n");
        return 0;
    }

    printf("%d->", header->data);
    display(header->next);
}
