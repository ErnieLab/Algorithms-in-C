#include <stdio.h>
#include <stdlib.h>

struct card
{
    int suit;
    int number;
};

typedef struct node
{
    struct card deck;
    struct node *next;
    struct node *prev;
}card_node;

card_node* new_card_node(int, int);
int add_card(card_node **, int, int);

int main(void)
{
    card_node *ptr_player_header[4] = {NULL}; //4 player deck header
    add_card(&ptr_player_header[0], 3, 4);
    printf("%d\n", ptr_player_header[0]->deck.suit);
    
    return 0;
}

card_node* new_card_node(int suit, int number)
{
    card_node *temp   = (card_node*)malloc(sizeof(card_node));
    temp->deck.suit   = suit;
    temp->deck.number = number;
    temp->next        = temp->prev = NULL;

    return temp;
}

int add_card(card_node **player_header, int card_suit, int card_number)
{
    card_node *new = new_card_node(card_suit, card_number);
    
    if(*player_header == NULL)
    {
        *player_header = new;
    }
    else
    {
        card_node *temp = *player_header;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new;
        new->prev  = temp;
    }
} 
