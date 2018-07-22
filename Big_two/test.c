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
int play_card(card_node **, int);
int print_your_hand(card_node **);
int what_you_get(card_node **, int *);
int Play_Single_Card(card_node **);
int remove_card(card_node **, int);
//--------------------------------------------------------------------------

int main(void)
{
    card_node *ptr_player_header[PLAYER] = {NULL}; //4 player deck header
    shuffle(&ptr_player_header[0]); 
    insertion_sort(&ptr_player_header[0]);
    //Game Start
    
    /*------------------------------------------------------
    state = 0 : Pool is empty
          = 1 : Single card
          = 2 : Pair            Ex: 22   , 33
          = 3 : Full House      Ex: 33355, 77733
          = 4 : Straight        Ex: 23456, 56789
          = 5 : Four of a King  Ex: 44446, 88885
          = 6 : Straight Flush  Ex: 23456, 56789(same suit)
    -------------------------------------------------------*/
    int pool_state = 0;

    play_card(&ptr_player_header[0], pool_state);

    return 0;
}

int play_card(card_node **player_header, int pool_state)
{
    switch(pool_state)
    {
        case 1:
        {
            print_your_hand(player_header);
            pool_state = Play_Single_Card(player_header);
            print_your_hand(player_header);
            break;
        }
        default:
        {
            print_your_hand(player_header);
            int combination_type[6] = {0};
            what_you_get(player_header, combination_type);
            printf("0 : repeat card combination\n");
            if(*(combination_type + 0) != 0)
            {
                printf("1 : Single card\n");
            }
            if(*(combination_type + 1) != 0)
            {
                printf("2 : Pair\n");
            }
            if(*(combination_type + 2) != 0)
            {
                printf("3 : Full House\n");
            }
            if(*(combination_type + 3) != 0)
            {
                printf("4 : Straight\n");
            }
            if(*(combination_type + 4) != 0)
            {
                printf("5 : Four of King\n");
            }
            if(*(combination_type + 5) != 0)
            {
                printf("6 : Straight Flush\n");
            }
            printf("Please type your card which you want to play\n");
            scanf("%d", &pool_state);
            printf("\n");
            play_card(player_header, pool_state);
        }
    }
}

int Play_Single_Card(card_node **player_header)
{
    int card_index = 0;
    int remove_orNOT;
    printf("Please type your single card which you want to play\n");
    scanf("%d", &card_index);
    printf("\n");
    remove_orNOT = remove_card(player_header, card_index);
    
    if(remove_orNOT == 0)
    {
        Play_Single_Card(player_header);
    }
    else
    {    
        return 1;
    }
}

int what_you_get(card_node **player_header, int *combination_type)
{
    card_node *card_checker = (*player_header)->next;
    int count = 0;

    //"Single Card" exist ot not
    if((*player_header) != NULL)
    {
        *(combination_type) = *(combination_type) + 1;
    }

    //"Pair" "Full house" "Four of King" exist or not
    while(card_checker != NULL)
    {
        if(card_checker->deck.number == card_checker->prev->deck.number)
        {
            count++;
            if(count == 3)
            {
                *(combination_type + 4) = *(combination_type +4) + 1;
                printf("you get '%d' Four of King\n", card_checker->deck.number);
            }
            else if(count == 2)
            {
                *(combination_type + 2) = *(combination_type + 2) + 1;
                printf("you get '%d' full house\n", card_checker->deck.number);
            }
            else if(count == 1)
            {
                *(combination_type + 1) = *(combination_type + 1) + 1;
                printf("you get '%d' pair\n", card_checker->deck.number);
            }
        }
        else
        {
            count = 0;
        }
        card_checker = card_checker->next;
    }

    //"Straight" "Straight Flush" exist or not
    card_checker = (*player_header);
    count = 0;

    int temp_suit   = (*player_header)->deck.suit;
    while(card_checker->next != NULL)
    {
        if(card_checker->deck.number == card_checker->next->deck.number)
        {
            card_checker = card_checker->next;
        }
        else if(card_checker->deck.number == ((card_checker->next->deck.number)-1))
        {
            count++;
            card_checker = card_checker->next;
            if(count >= 4)
            {
                *(combination_type + 3) = *(combination_type + 3) + 1;
                printf("you get '%d %d %d %d %d' straight\n", (card_checker->deck.number)-4, (card_checker->deck.number)-3, (card_checker->deck.number)-2, (card_checker->deck.number)-1, (card_checker->deck.number));
            }
        }
        else
        {
            count = 0;
            card_checker = card_checker->next;
        }
    }
    printf("\n");
}

int remove_card(card_node **player_header, int card_index)
{
    if(card_index == 0 || card_index > 13)
    {
        printf("Please key the 'correct' card index\n");
        return 0;
    }
    else
    {
        int i = 1;
        card_node *target = *player_header;
        while(i < card_index)
        {
            if(target == NULL)
            {
                break;
            }
            else
            {
                target = target->next;
                i++;
            }
        }

        if(target == NULL)
        {
            printf("Please key the 'correct' card index\n");
            return 0;
        }
        else
        {
            if(target == *player_header)
            {
                *player_header = target->next;
                target->next->prev = NULL;
            }
            else if(target->next == NULL)
            {
                target->prev->next = NULL;
            }
            else
            {
                target->prev->next = target->next;
                target->next->prev = target->prev;
            }
            free(target);
            return 1;
        }
    }
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
                if((checker->deck.number) > (target->deck.number) || ( ((checker->deck.number) == (target->deck.number)) && ((checker->deck.suit) > (target->deck.suit)))  )
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

int print_your_hand(card_node **player_header)
{
    int i = 1;
    card_node *temp = *player_header;
    printf("Your hand:\n");
    while((*player_header) != NULL) 
    {
        printf("%d : %d   %d\n", i++, (*player_header)->deck.suit, (*player_header)->deck.number);
        (*player_header) = (*player_header)->next;
    }

    (*player_header) = temp;
    printf("\n");
}
