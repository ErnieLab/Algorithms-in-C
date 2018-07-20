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
int insertion_sort(card_node **);
int insert(card_node **, card_node *, card_node *);
int delete(card_node **);
int check_specific_type(card_node **);

//--------------------------------------------------------------------------

int main(void)
{
    card_node *ptr_player_header[PLAYER] = {NULL}; //4 player deck header
    shuffle(&ptr_player_header[0]); 
    insertion_sort(&ptr_player_header[0]);
    //Game Start
    int pool_state = 0;


    int i;
    for(i = 0; i < 13; i++)
    {
        printf("%d   %d\n", ptr_player_header[0]->deck.suit, ptr_player_header[0]->deck.number);
        ptr_player_header[0] = ptr_player_header[0]->next;
    }
    printf("\n\n");
    
    return 0;
}

int check_specific_type(card_node **player_header)
{
    

}

int insertion_sort(card_node **player_header)
{
    if((*player_header) == NULL)
    {
        printf("Nothing has to sort!!!");
    }
    else
    {
        card_node *target = (*player_header)->next;
        card_node *checker;
        while(target != NULL)
        {
            checker = target->prev;
            while(checker != NULL)
            {
                if((checker->deck.number) > (target->deck.number))
                {
                    if(checker->prev == NULL)
                    {
                        insert(player_header, checker, target);
                        delete(&target);
                        break;
                    }
                    else
                    {
                        checker = checker->prev;
                    }
                }
                else
                {
                    insert(player_header, checker, target);
                    delete(&target);
                    break;
                }
            }
            target = target->next;
        }
    }
}

int insert(card_node **player_header, card_node *checker_node, card_node *target_node)
{
    //First step: insert
    card_node *new   = new_card_node(target_node->deck.suit, target_node->deck.number);
    if(checker_node->prev == NULL && ((target_node->deck.number) < (checker_node->deck.number)))
    {
        checker_node->prev = new;
        new->next          = checker_node;
        *player_header     = new;
    }
    else
    {
        new->prev                = checker_node;
        new->next                = checker_node->next;
        checker_node->next->prev = new;
        checker_node->next       = new;
    }
}

int delete(card_node **target_node)
{
    //Second Step: Delete
    card_node *ready_be_free = *target_node;
    if((*target_node)->next == NULL)
    {
        (*target_node)->prev->next = NULL;
    }
    else
    {
        (*target_node)->next->prev = (*target_node)->prev;
        (*target_node)->prev->next = (*target_node)->next;
    }
    (*target_node) = (*target_node)->prev;   
    free(ready_be_free); 
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
        int number = *(card_index + index)%(CARD_NUM/PLAYER);
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
