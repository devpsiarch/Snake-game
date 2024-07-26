#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>
#include <raymath.h>



int randint(int min_val, int max_val) {
    srand(time(0));
    return (rand() % (max_val - min_val + 1)) + min_val;
}

struct snake* head = NULL;
struct snake* tail = NULL;


typedef struct snake{
    Vector2 direction;
    Vector2 pos;
    struct snake* next;

}snake;
bool Vector2compair(Vector2 a,Vector2 b){
    if ((a.x == b.x)&&(a.y==b.y))
    {
        return true;
    }
    return false;
}
void front(Vector2 x){
    struct snake* temp = (struct snake*)malloc(sizeof(struct snake));
    (*temp).pos = x;
    if ((head == NULL)&&(tail==NULL))
    {
        temp->next = NULL;
        head = temp;
        tail = temp;
        return ;
    }
    (*head).next = temp;
    head = temp;
    temp->next = NULL;
}
bool legalmoveassert(Vector2 dir){
    Vector2 check;
    struct snake* temp = tail;
    check = Vector2Add(head->pos,dir);
    while (temp != NULL)    
    {
        if (Vector2compair(check,temp->pos))
        {
            return false;
        }
        temp = temp->next;
    }
    return true;
}
void back(Vector2 x){
    struct snake* temp = (struct snake*)malloc(sizeof(struct snake));
    (*temp).pos = x;
    if ((head == NULL)&&(tail == NULL))
    {
        (*temp).next = NULL;
        head = temp;
        tail = temp;
        return ;
    }
    (*temp).next = tail;
    tail = temp;
}
void display(){
    struct snake* temp = tail;
    printf("possitions are : \n");
    while (temp != NULL)
    {
        printf("x = %lf | y = %lf\n",(*temp).pos.x,(*temp).pos.y);
        temp = (*temp).next;
    }
}
void walk(Vector2 dir){
    if (!legalmoveassert(dir))
    {
        return;
    }
    tail->pos = Vector2Add(head->pos , dir);
    front(tail->pos);
    struct snake* temp = tail;
    tail = temp->next;
    free(temp);

}
int sizelinked(){
    struct snake* temp = tail;
    int size = 0;
    while (temp != NULL)
    {
        size++;
        temp = (*temp).next;
    } 
    return size;
}


Vector2 Vector2gen(int x){
    Vector2 temp;
    srand(time(NULL));
    temp.x = rand()%x;
    temp.y = rand()%x;
    return temp;
}

bool insnake(Vector2 food){
    struct snake* temp = tail;
    while (temp != NULL)
    {
        if (Vector2compair(temp->pos,food))
        {
            return true;
        }
    }
    return false;
}



Vector2 getfoodpos(int size){
    Vector2 temp = Vector2gen(size);
    while (insnake(temp))
    {
        temp = Vector2gen(size);
    }
    return temp;
}

void clear(){
    if (tail == NULL)
    {
        printf("already cleared ! \n");
        return;
    }
    struct snake* temp;
    while (tail != NULL)
    {
        temp = tail;
        tail = temp->next;
        free(temp);
    }
    head = tail;
}


#endif
