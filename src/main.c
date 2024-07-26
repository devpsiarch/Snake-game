#include "headers.h"
/*moving the snake
1) move the buttom of the snake to the top (recommended)
2) have a linked list of possition of every body part and have it point ot the next one then move them accordinly
*/ 


/*
adding sounds is by using some simple function remember to unload the sounds after you are done.
*/

//Color THEME = {255,13,77};
int cellsize = 25;
int cellcount = 25;
int offset = 75;
double now = 0;
int score = 0;

Rectangle frame = {70,70,635,635};

Vector2 loc[3] = {{6,6},{5,6},{4,6}};
Vector2 UP = {0,-1};
Vector2 DOWN = {0,1};
Vector2 RIGHT = {1,0};
Vector2 LEFT = {-1,0};

snake bob;

typedef struct food {
    Vector2 pos;
    Texture2D skin;
}food;

/*************/
/*  source  */
/************/

void initsnake(){
    clear();
    for (int i = 0; i < 3; i++)
    {
        back(loc[i]);
    }
    
}
void gameover(){
    initsnake();
    bob.direction = LEFT;
    score = 0;
}


bool strict(double interval){
    double current = GetTime();
    if (current - now >= interval)
    {
        now = current;
        return true;
    }
    return false;
    
}


food deffood(){
    srand(time(0));
    food sample;
    sample.pos = getfoodpos(cellcount);
    Image image = LoadImage("pictures/heart.png");
    sample.skin = LoadTextureFromImage(image);
    return sample;
}
void desfood(food sample){
    UnloadTexture(sample.skin);
}
void drawfood(food sample){
   DrawTexture(sample.skin,offset+sample.pos.x*cellsize,offset+sample.pos.y*cellsize,WHITE);
}
void drawsnake(){
    struct snake* temp = tail;
    Rectangle body;
    for (int i = 0; i < sizelinked(); i++)
    {

        body = (Rectangle){offset+cellsize * temp->pos.x,offset+cellsize * temp->pos.y,cellsize,cellsize};
        DrawRectangleRounded(body,0.5,6,WHITE);
        temp = temp->next;
    }
}
void movesnake(Vector2 dir){
    walk(dir);
    //drawsnake();
}

void snakeupdatedirection(){
    if (IsKeyPressed(KEY_UP)&&(legalmoveassert(UP)))
    {
        bob.direction = UP;
    }
    if (IsKeyPressed(KEY_LEFT)&&(legalmoveassert(LEFT)))
    {
        bob.direction = LEFT;
    }
    if (IsKeyPressed(KEY_RIGHT)&&(legalmoveassert(RIGHT)))
    {
        bob.direction = RIGHT;
    }
    if (IsKeyPressed(KEY_DOWN)&&(legalmoveassert(DOWN)))
    {
        bob.direction = DOWN;
    }
}

Vector2 getback(Vector2 dir){
    Vector2 temp;
    temp.x = tail->pos.x - dir.x;
    temp.y = tail->pos.y - dir.y;
    return temp;
}

void checkcollswall(){
    if ((head->pos.x == cellcount) || (head->pos.x == -1))
    {
        gameover();
    }
    if ((head->pos.y == cellcount) || (head->pos.y == -1))
    {
        gameover();
    }
    
}


void updatesnake(food lil){
    drawsnake();
    snakeupdatedirection();
    if (strict(0.1))
    {
        movesnake(bob.direction);
    }
}

void checkeat(food* lil){
    if (Vector2compair(head->pos,(*lil).pos)){
        (*lil).pos = Vector2gen(cellcount);
        back(getback(bob.direction));
        score ++;
    } 
}
void checkcollsslef(){
    if (!legalmoveassert(bob.direction))
    {
        gameover();
    }
}
void checkcolls(){
    checkcollswall();
    checkcollsslef();
}


int main(void)
{
    InitWindow(2*offset + cellcount*cellsize,2*offset + cellcount*cellsize, "Snake game");
    SetTargetFPS(60);
    food lil = deffood();
    bob.direction = RIGHT;
    initsnake();
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        drawfood(lil);
        updatesnake(lil);
        checkeat(&lil);
        checkcolls(&lil);




        DrawText(TextFormat("current score : %d",score),offset-5,offset + cellsize*cellcount+5,40,WHITE);
        DrawRectangleLinesEx(frame,5,WHITE);
        EndDrawing();
    }
    desfood(lil);
    CloseWindow();

    return 0;
}
