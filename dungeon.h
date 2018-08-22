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
                            printf("Î");
                            break;
                        case 1:
                        case 4:
                        case 5:
                            printf("º");
                            break;
                        case 2:
                        case 8:
                        case 10:
                            printf("Í");
                            break;
                        case 3:
                            printf("¼");
                            break;
                        case 6:
                            printf("»");
                            break;
                        case 7:
                            printf("¹");
                            break;
                        case 9:
                            printf("È");
                            break;
                        case 11:
                            printf("Ê");
                            break;
                        case 12:
                            printf("É");
                            break;
                        case 13:
                            printf("Ì");
                            break;
                        case 14:
                            printf("Ë");
                            break;
                    }
                    break;
                case 2:
                    printf("ê");
                    break;
                case 3:
                    printf("è");
                    break;
            }
        }
        printf("\n");
    }
}
