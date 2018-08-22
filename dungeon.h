#define dwidth 79
#define dlength 15

void dungeonInit(int dungeon[dlength][dwidth]){
    int i,j;
    for (i = 0; i < dlength; i++){
        for (j = 0; j < dwidth ;j++)
            dungeon[i][j] = 0;
    }
}

int getWallValue(int dungeon[dlength][dwidth], int x, int y){
    int value = 0;
    if (y > 0){
        if (dungeon[y - 1][x] == 1)
            value += 1;
    }
    if (x > 0){
        if (dungeon[y][x - 1] == 1)
            value += 2;
    }
    if (y < dlength-1){
        if (dungeon[y + 1][x] == 1)
            value += 4;
    }
    if (x < dwidth-1){
        if (dungeon[y][x + 1] == 1)
            value += 8;
    }
    return value;
}

void drawDungeon(int dungeon[dlength][dwidth]){
    int i, j, value;
    for (i = 0; i < dlength; i++){
        for (j = 0; j < dwidth; j++){
             switch(dungeon[i][j]){
                case 0:
                    printf(" ");
                    break;
                case 1:
                    value = getWallValue(dungeon,j,i);
                    switch(value){
                        case 0:
                        case 15:
                            printf("�");
                            break;
                        case 1:
                        case 4:
                        case 5:
                            printf("�");
                            break;
                        case 2:
                        case 8:
                        case 10:
                            printf("�");
                            break;
                        case 3:
                            printf("�");
                            break;
                        case 6:
                            printf("�");
                            break;
                        case 7:
                            printf("�");
                            break;
                        case 9:
                            printf("�");
                            break;
                        case 11:
                            printf("�");
                            break;
                        case 12:
                            printf("�");
                            break;
                        case 13:
                            printf("�");
                            break;
                        case 14:
                            printf("�");
                            break;
                    }
                    break;
                case 2:
                    printf("�");
                    break;
                case 3:
                    printf("�");
                    break;
            }
        }
        printf("\n");
    }
}
