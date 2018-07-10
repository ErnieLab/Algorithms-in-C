#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define PLAYER 4
#define CARD_NUM 52

//--------------------------------------------------------------------------
 
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
int shuffle(card_node **);
int sorting(card_node **);

//--------------------------------------------------------------------------

int main(void)
{
    card_node *ptr_player_header[PLAYER] = {NULL}; //4 player deck header
    shuffle(&ptr_player_header[0]);
    //sorting(&ptr_player_header[0]);

    /*   
    int i;
    for(i = 0; i < 13; i++)
    {
        printf("%d   %d\n", ptr_player_header[1]->deck.suit, ptr_player_header[1]->deck.number);
        ptr_player_header[1] = ptr_player_header[1]->next;
    }
    */
    
    return 0;
}

int sorting(card_node **player_header)
{
    
}

int shuffle(card_node **player_header)
{
    srand(time(NULL));
    int card_index[CARD_NUM];
    int index;

    //initial
    for(index = 0; index < CARD_NUM; index++)
    {
        *(card_index + index) = index + 1;
    }

    //shuffle
    for(index = 0; index < CARD_NUM; index++)
    {
        int swap_index = rand()%(CARD_NUM); //generator [0,51] random number

        //Swap
        int temp                   = *(card_index + swap_index);
        *(card_index + swap_index) = *(card_index + index);
        *(card_index + index)      = temp;
    }

    //dealing
    int count        = CARD_NUM/PLAYER;
    int player_index = 0;
    for(index = 0; index < CARD_NUM; index++)
    { 
        int suit   = *(card_index + index)/(CARD_NUM/PLAYER);
        int number = *(card_index + index)%(CARD_NUM);
        if(number == 0)
        {
            number = CARD_NUM/PLAYER;
        }

        add_card(player_header + player_index, suit, number);
        count--;

        if(count == 0)
        {
            player_index++;
            count = CARD_NUM/PLAYER;
        }
    }
}


card_node* new_card_node(int suit, int number)
{
    card_node *temp   = (card_node*)malloc(sizeof(card_node));
    temp->deck.suit   = suit;
    temp->deck.number = number;
    temp->next        = temp->prev = NULL;

    return temp;
}

int add_card(card_node **player_header, int suit, int number)
{
    card_node *new = new_card_node(suit, number);
    
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
