#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include "dungeon.h"

#define up 'w'
#define down 's'
#define right 'd'
#define left 'a'

#define moveMode 1
#define battleMode 2

void mapInit(int dungeon[dlength][dwidth]){

    FILE *map;
    char mapBuff;
    int i,j;

    map = fopen("dungeons/1","r");

    for (i = 0; i < dlength; i++){
        for (j = 0; j < dwidth; j++){
                do{
                    mapBuff = fgetc(map);
                }while(mapBuff=='\n');

                dungeon[i][j] = mapBuff - '0';
        }
    }

    fclose(map);

}

typedef struct position {
    int x;
    int y;
} position;

typedef struct element {
    position elementPos;
    int health;
    int maxhealth;
} element;

typedef struct attack {
    int id;
    char name[80];
    int damage;
} attack;

position getPosition(int dungeon[dlength][dwidth],int elem){
    int i, j;
    struct position player;

    for (i = 0; i < dlength; i++){
        for (j = 0; j < dwidth; j++){
            if (dungeon[i][j] == elem){
                player.x = j;
                player.y = i;
                break;
            }
        }
    }

    return player;
}

void movePlayer(int dungeon[dlength][dwidth], char move, position *player){
    position newPos = *player;
    switch(move){
        case up:
            if (dungeon[(*player).y-1][(*player).x] == 0)
                newPos.y--;
            break;
        case right:
            if (dungeon[(*player).y][(*player).x+1] == 0)
                newPos.x++;
            break;
        case down:
            if (dungeon[(*player).y+1][(*player).x] == 0)
                newPos.y++;
            break;
        case left:
            if (dungeon[(*player).y][(*player).x-1] == 0)
                newPos.x--;
            break;
    }
    dungeon[(*player).y][(*player).x] = 0;
    dungeon[newPos.y][newPos.x] = 2;
}

void drawHealthbar(int hp, int maxHp, char label[25]){
    int i,percent, barLength;

    barLength = 76 - strlen(label);

    printf("Ú");
    for (i = 0; i < strlen(label); i++)
        printf("Ä");
    printf("Â");

    for (i = 0;  i < barLength; i++)
        printf("Ä");
    printf("¿\n");

    printf("³%s³",label);

    percent  = (int)(((float)hp/(float)maxHp)*100);

    for (i = 0;  i < barLength; i++){
        if (i < (int)(barLength * ((float)percent/100)))
            printf("Û");
        else
            printf("°");
    }

    printf("³\nÀ");
    for (i = 0; i < strlen(label); i++)
        printf("Ä");
    printf("Á");
    for (i = 0; i < barLength; i++)
        printf("Ä");
    printf("Ù\n");

}

int getDistance(element e1,  element e2){
    int distance = abs((e1.elementPos.x-e2.elementPos.x)+(e1.elementPos.y-e2.elementPos.y));
    return distance;
}

void changeView(element e1, element e2, int *viewMode){
    if (*viewMode == moveMode){
       if (getDistance(e1,e2) <= 1)
            *viewMode = battleMode;
    }
}

void drawBattle(){
    printf("\t\t ÉÍÍÍ»  ");     printf("\t\t          ÉÍÍÍÍÍ»\n");
    printf("\t\tÉ¼   È» ");     printf("\t\t         É¼     È»\n");
    printf("\t\tÌÍÍÍÍÍ¹ ");     printf("\t\t        É¼       È»\n");
    printf("\t\t³ ù ù ³ ");     printf("\t\t       ÉÊÍ»       º\n");
    printf("\t\t³  Ä  ³ ");     printf("\t\t  ÉÍÍ»É¼  È»     É¼\n");
    printf("\t\tÀÂÄÄÄÂÙ ");     printf("\t\t É¼  È¹         É¼\n");
    printf("\t\t ÃÙ À´  ");     printf("\t\tÉ¼          ÌÍËÍ¼\n");
    printf("\t\t ÃÂÄÂ´  ");     printf("\t\tºøå  åø ÌÍËÍ¹ È» \n");
    printf("\t\t ÃÙ À´  ");     printf("\t\tÈ»     É¼ º È»\n");
    printf("\t\t ÀÂÁÂÙ  ");     printf("\t\t ÈÍËÍËÍ¼  È»\n");
    printf("\t\t  Ù À   ");     printf("\t\t   È ¼\n");
}

attack *getAllAttack(){
    attack *attackList = malloc(4 * sizeof(attack));

    strcpy(attackList[0].name,"Punch");
    attackList[0].damage = 10;

    strcpy(attackList[1].name,"Kick");
    attackList[1].damage = 15;

    strcpy(attackList[2].name,"Ember");
    attackList[2].damage = 25;

    strcpy(attackList[3].name,"Flamethrower");
    attackList[3].damage = 50;

    return attackList;
}

void drawAttackOption(){
    attack *attackList = getAllAttack();
    int i,j;

    for (i = 0; i < 4; i++){
        printf("ÚÄÂ");
        for (j = 0; j < strlen(attackList[i].name); j++)
            printf("Ä");
        printf("¿");
        if (i == 3)
            printf("\n");
    }

    for (i = 0; i < 4; i++){
        printf("³%d³%s³",i,attackList[i].name);
        if (i == 3)
            printf("\n");
    }

    for (i = 0; i < 4; i++){
        printf("ÀÄÁ");
        for (j = 0; j < strlen(attackList[i].name); j++)
            printf("Ä");
        printf("Ù");
        if (i == 3)
            printf("\n");
    }
}

int playerAttack(element *enemy,char move){
    attack *attackList  = getAllAttack();
    switch(move){
        case '0':
            if ((*enemy).health > attackList[0].damage){
                (*enemy).health -=  attackList[0].damage;
                return 0;
            }else
                return 1;
            break;
        case '1':
            if ((*enemy).health > attackList[1].damage){
                (*enemy).health -=  attackList[1].damage;
                return 0;
            }else
                return 1;
            break;
        case '2':
            if ((*enemy).health > attackList[2].damage){
                (*enemy).health -=  attackList[2].damage;
                return 0;
            }else
                return 1;
            break;
        case '3':
            if ((*enemy).health > attackList[3].damage){
                (*enemy).health -=  attackList[3].damage;
                return 0;
            }else
                return 1;
            break;
    }
    free(attackList);
    return 0;
}

int main(){

    int dungeon[dlength][dwidth];
    int viewMode = moveMode;
    int enemyDead = 0;
    char response;

    //player stuff
    element player;
    player.health = 100;
    player.maxhealth = 100;

    //enemy stuff
    element enemy;
    enemy.health = 100;
    enemy.maxhealth = 100;

    dungeonInit(dungeon);
    mapInit(dungeon);

    do{
        system("cls");
        player.elementPos = getPosition(dungeon,2);
        enemy.elementPos = getPosition(dungeon,3);
        changeView(player,enemy,&viewMode);
        if (viewMode == moveMode){
            drawDungeon(dungeon);
            drawHealthbar(player.health,player.maxhealth,"Player HP");
        } else {
            drawBattle();
            printf("\t\t\tSpider is ready for battle...\n");
            drawHealthbar(player.health,player.maxhealth,"Player HP");
            drawHealthbar(enemy.health,enemy.maxhealth,"Spider HP");
            drawAttackOption();
        }
        response = getch();
        if (viewMode == moveMode)
            movePlayer(dungeon,response,&player.elementPos);
        else {
            enemyDead = playerAttack(&enemy,response);
            if (enemyDead){
                dungeon[enemy.elementPos.y][enemy.elementPos.x] = 0;
                viewMode = moveMode;
            }
        }

    }while(response != 0);

    return 0;
}
