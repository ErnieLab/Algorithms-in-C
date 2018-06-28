#include <stdio.h>
#include <stdlib.h>

#define SIZE 9

typedef struct node
{
    int row;
    int col;
    int dir;
    struct node *back;
}position;

typedef struct
{
    int horiz;
    int verti;
}offset;

offset move[4] = 
{
    [0] = {
            .horiz = 1,
            .verti = 0,
          },
    [1] = {
            .horiz = 0,
            .verti = 1,
          },
    [2] = {
            .horiz = -1,
            .verti = 0,
          },
    [3] = {
            .horiz = 0,
            .verti = -1,
          },
};

position* create(position*, int*); //initial link
position* add(position*, int);     //add link
position* delete(position*);       //delete link

int main()
{
    int maze[SIZE+1][SIZE+1] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                {1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
                                {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
                                {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
                                {1, 0, 0, 1, 1, 0, 0, 0, 0, 1},
                                {1, 1, 0, 0, 1, 0, 1, 1, 0, 1},
                                {1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
                                {1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
                                {1, 1, 1, 0, 0, 0, 0, 1, 0, 1},
                                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    //initial
    int start[2] = {1,1}; //define starting point
    int end[2]   = {8,8}; //define ending point
    int dir = 0;
    position *ptr_top = create(ptr_top, start);

    //find
    while(ptr_top->row != end[1] || ptr_top->col != end[0])
    {
        for(dir = dir; dir < 4; dir++)
        {
            //if next step is available
            if(maze[ptr_top->row + move[dir].verti][ptr_top->col + move[dir].horiz] == 0)
            {
                if(move[dir].verti == -move[ptr_top->dir].verti && move[dir].horiz == -move[ptr_top->dir].horiz)
                {
                    continue;
                }
                else
                {
                    ptr_top = add(ptr_top, dir);
                    dir = 0;
                    break;
                }
            }
            else if(dir == 3 && maze[ptr_top->row + move[dir].verti][ptr_top->col + move[dir].horiz] == 1)
            {
                dir = ptr_top->dir;
                maze[ptr_top->row][ptr_top->col] = 1;
                ptr_top = delete(ptr_top);

                while(ptr_top->dir == 3)
                {
                    dir = ptr_top->dir;
                    maze[ptr_top->row][ptr_top->col] = 1;
                    ptr_top = delete(ptr_top);
                }
                break;
            }
        }

        printf("row = %d, column = %d, dir = %d\n", ptr_top->row, ptr_top->col, ptr_top->dir);
    }
    return 0;
}

position* create(position *top, int *start)
{
    position *new_position;

    new_position = (position*)malloc(sizeof(position));

    new_position->row  = start[1];
    new_position->col  = start[0];
    new_position->dir  = 0;
    new_position->back = top;

    top = new_position;
    return top;
}


position* add(position *top, int dir) //NOTICE
{
    position *new_position;

    new_position = (position*)malloc(sizeof(position));

    new_position->row  = top->row + move[dir].verti;
    new_position->col  = top->col + move[dir].horiz;
    new_position->dir  = dir;
    new_position->back = top;

    //printf("address of new_position: %p\n", new_position->back);
    top = new_position;

    return top;
}

position* delete(position *top)
{
    position *ptr_tmp;

    ptr_tmp = top;
    top = top->back;

    free(ptr_tmp);

    return top;
}
