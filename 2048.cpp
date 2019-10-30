#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

bool checkArrow()
{
    char ipt;
    ipt = getch();
    switch(ipt)
       {
       case 0:
           ipt = getch();
           return false;
           break;
       case -32:
           ipt = getch();
           break;
       case 27:

       default:
           return false;
           break;
       }
       //printf("%d\n",ipt);
       /*if(ipt == 27)
       {
           printf("escape(quit program)\n");
           return true;
       }
       else printf("%d\n",ipt);*/
       switch(ipt)
       {
       case KEY_UP:
        printf("UP\n");
        break;
       case KEY_DOWN:
        printf("DOWN\n");
        break;
       case KEY_LEFT:
        printf("LEFT\n");
        break;
       case KEY_RIGHT:
        printf("RIGHT\n");
        break;
       default:
           return false;
        printf("NOT ARROW\n");
        break;
       }
       return true;
}

int plate2print(int x)
{
    int base;
    if(x == 0) return 0;
    base = 2;
    while(--x) base = base*2;
    return base;
}

class game
{
public:
    int plate[4][4];
    int plate_next[4][4][4]; //the plate that up,down,left,right been pressed
    bool validate[4];//if is validate pressing the key,then true;if all false, game over
    int score;
    int next_score[4];
    int cnt;
    bool ctn;
    time_t t;

    game()
    {
        int i,j;
        for(i = 0;i < 4;i++)
        {
            for(j = 0;j < 4;j++)
            {
                plate[i][j] = 0;
                plate_next[0][i][j] = 0;
                plate_next[1][i][j] = 0;
                plate_next[2][i][j] = 0;
                plate_next[3][i][j] = 0;
            }
        }
        cnt = 0;
        next_score[0] = 0;
        next_score[1] = 0;
        next_score[2] = 0;
        next_score[3] = 0;
        score = 0;
        ctn = true;
        srand((unsigned) time(&t));
        randPanel();
        randPanel();
    }

    void print()
    {
        int i,j;
        printf("***** %d move(s) done *****\n\n",cnt);
        for(i = 0;i < 4;i++)
        {
            for(j = 0;j < 4;j++)
            {
                printf("%5d ",plate2print(plate[i][j]));
            }
            printf("\n");
        }
        printf("***** Score:%d *****\n",score);
        printf("\n");
        return;
    }

    void print_next()
    {
        int i,j,k;
        printf("\n\n");
        for(i = 0;i < 4;i++)
        {
            for(j = 0;j < 4;j++)
            {
                for(k = 0;k < 4;k++) printf("%5d ",plate2print(plate_next[i][j][k]));
                printf("\n");
            }
            printf("\n\n");
        }
        printf("\n");
        return;
    }

    bool setNext()
    {
        int i,j,k;
        //copy
        for(i = 0;i < 4;i++)
        {
            for(j = 0;j < 4;j++)
            {
                for(k = 0;k < 4;k++)
                {
                    plate_next[k][i][j] = plate[i][j];
                }
            }
        }
        //print_next();

        //left
        next_score[0] = 0;
        validate[0] = false;
       for(i = 0;i<4;i++) //move panel again
        {
            for(j = 0;j<3;j++)
            {
                if(plate_next[0][i][j] == 0)
                {
                    for(k = j+1;k < 4;k++)
                    {
                        if(plate_next[0][i][k]!=0)
                        {
                            plate_next[0][i][j] = plate_next[0][i][k];
                            plate_next[0][i][k] = 0;
                            validate[0] = true;
                            break;
                        }
                    }
                }
            }
        }
        for(i = 0;i<4;i++) //move panel
        {
            for(j = 0;j<3;j++)
            {
                if(plate_next[0][i][j] != 0 && plate_next[0][i][j] == plate_next[0][i][j+1])
                {
                    plate_next[0][i][j] ++;
                    next_score[0] += plate2print(plate_next[0][i][j]);
                    plate_next[0][i][j+1] = 0;
                    validate[0] = true;
                }
            }
        }
        for(i = 0;i<4;i++) //move panel again
        {
            for(j = 0;j<3;j++)
            {
                if(plate_next[0][i][j] == 0)
                {
                    for(k = j+1;k < 4;k++)
                    {
                        if(plate_next[0][i][k]!=0)
                        {
                            plate_next[0][i][j] = plate_next[0][i][k];
                            plate_next[0][i][k] = 0;
                            validate[0] = true;
                            break;
                        }
                    }
                }
            }
        }

         //right
        next_score[1] = 0;
        validate[1] = false;
        for(i = 0;i<4;i++) //move panel again
        {
            for(j = 3;j>0;j--)
            {
                if(plate_next[1][i][j] == 0)
                {
                    for(k = j-1;k >= 0;k--)
                    {
                        if(plate_next[1][i][k]!=0)
                        {
                            plate_next[1][i][j] = plate_next[1][i][k];
                            plate_next[1][i][k] = 0;
                            validate[1] = true;
                            break;
                        }
                    }
                }
            }
        }
        for(i = 0;i<4;i++) //move panel
        {
            for(j = 3;j>0;j--)
            {
                if(plate_next[1][i][j] != 0 && plate_next[1][i][j] == plate_next[1][i][j-1])
                {
                    plate_next[1][i][j] ++;
                    next_score[1] += plate2print(plate_next[1][i][j]);
                    plate_next[1][i][j-1] = 0;
                    validate[1] = true;
                }
            }
        }
        for(i = 0;i<4;i++) //move panel again
        {
            for(j = 3;j>0;j--)
            {
                if(plate_next[1][i][j] == 0)
                {
                    for(k = j-1;k >= 0;k--)
                    {
                        if(plate_next[1][i][k]!=0)
                        {
                            plate_next[1][i][j] = plate_next[1][i][k];
                            plate_next[1][i][k] = 0;
                            validate[1] = true;
                            break;
                        }
                    }
                }
            }
        }

        //up
        next_score[2] = 0;
        validate[2] = false;
        for(j = 0;j<4;j++) //move panel again
        {
            for(i = 0;i<3;i++)
            {
                if(plate_next[2][i][j] == 0)
                {
                    for(k = i+1;k < 4;k++)
                    {
                        if(plate_next[2][k][j]!=0)
                        {
                            plate_next[2][i][j] = plate_next[2][k][j];
                            plate_next[2][k][j] = 0;
                            validate[2] = true;
                            break;
                        }
                    }
                }
            }
        }
        for(j = 0;j<4;j++) //move panel
        {
            for(i = 0;i<3;i++)
            {
                if(plate_next[2][i][j] != 0 && plate_next[2][i][j] == plate_next[2][i+1][j])
                {
                    plate_next[2][i][j] ++;
                    next_score[2] += plate2print(plate_next[2][i][j]);
                    plate_next[2][i+1][j] = 0;
                    validate[2] = true;
                }
            }
        }
        for(j = 0;j<4;j++) //move panel again
        {
            for(i = 0;i<3;i++)
            {
                if(plate_next[2][i][j] == 0)
                {
                    for(k = i+1;k < 4;k++)
                    {
                        if(plate_next[2][k][j]!=0)
                        {
                            plate_next[2][i][j] = plate_next[2][k][j];
                            plate_next[2][k][j] = 0;
                            validate[2] = true;
                            break;
                        }
                    }
                }
            }
        }

       //down
        next_score[3] = 0;
        validate[3] = false;
        for(j = 0;j<4;j++) //move panel again
        {
            for(i = 3;i > 0;i--)
            {
                if(plate_next[3][i][j] == 0)
                {
                    for(k = i-1;k >= 0;k--)
                    {
                        if(plate_next[3][k][j]!=0)
                        {
                            plate_next[3][i][j] = plate_next[3][k][j];
                            plate_next[3][k][j] = 0;
                            validate[3] = true;
                            break;
                        }
                    }
                }
            }
        }
        for(j = 0;j<4;j++) //move panel
        {
            for(i = 3;i > 0;i--)
            {
                if(plate_next[3][i][j] != 0 && plate_next[3][i][j] == plate_next[3][i-1][j])
                {
                    plate_next[3][i][j] ++;
                    next_score[3] += plate2print(plate_next[3][i][j]);
                    plate_next[3][i-1][j] = 0;
                    validate[3] = true;
                }
            }
        }
        for(j = 0;j<4;j++) //move panel again
        {
            for(i = 3;i > 0;i--)
            {
                if(plate_next[3][i][j] == 0)
                {
                    for(k = i-1;k >= 0;k--)
                    {
                        if(plate_next[3][k][j]!=0)
                        {
                            plate_next[3][i][j] = plate_next[3][k][j];
                            plate_next[3][k][j] = 0;
                            validate[3] = true;
                            break;
                        }
                    }
                }
            }
        }

        return validate[0] || validate[1] || validate[2] || validate[3];
    }

    void randPanel()
    {
        int new_num;
        int i,j,k;
        int zero_cnt,pos;
        //print();
        new_num = ((rand() % 5) == 0 ? 2 : 1);
        zero_cnt = 0;
        for(i = 0;i < 4; i++)
        {
            for(j = 0;j < 4; j++)
            {
                if(plate[i][j] == 0) zero_cnt++;
            }
        }
        pos = rand() % zero_cnt;

        printf("%d %d\n",zero_cnt,pos);
        k = 0;
        for(i = 0;i < 4; i++)
        {
            for(j = 0;j < 4; j++)
            {
                if(plate[i][j] == 0)
                {
                    if(k == pos)
                    {
                        plate[i][j] = new_num;
                        return;
                    }
                    else k++;
                }
            }
        }
        return;
    }

    bool action(int way)
    {
        int i,j;
        //printf("Action:%d\n",way);
        switch(way)
        {
        case 0:
        case 1:
        case 2:
        case 3:
            if(validate[way])
            {
                for(i = 0;i < 4;i++)
                {
                    for(j = 0;j < 4;j++)
                    {
                        plate[i][j] = plate_next[way][i][j];
                    }
                }
                score += next_score[way];
                randPanel();
                print();
                cnt++;
                ctn = setNext();
                return true;
            }
            else return false;
            break;
        default:
            return false;
            break;
        }
    }

    int getKey()
    {
        char ipt;
        ipt = getch();
        switch(ipt)
       {
       case 0:
           ipt = getch();
           return -1;
           break;
       case -32:
           ipt = getch();
           break;
       case 27:
           return 5;
           break;
       default:
           return -1;
           break;
       }
       switch(ipt)
       {
       case KEY_UP:
        return 2;
        break;
       case KEY_DOWN:
        return 3;
        break;
       case KEY_LEFT:
        return 0;
        break;
       case KEY_RIGHT:
        return 1;
        break;
       default:
           return -1;
        break;
       }
       return -1;
    }

    int play()
    {
        printf("2048 start\nUse arrow key to play.\nPress ESC to escape the game\n");
        print();
        ctn = setNext();
        //print_next();
        while(ctn)
        {
            int act;
            //printf("%d %d %d %d\n",validate[0]?1:0,validate[1]?1:0,validate[2]?1:0,validate[3]?1:0);
            act = getKey();
            if(act == 5)
            {
                printf("Escape the game.\n");
                break;
            }
            else if(act != -1)
            {
                if(action(act));
            }
        }
        if(!ctn)
        {
            printf("GAME OVER\n");
        }
        printf("Final score:%d\n",score);
        return score;
    }
};

int main()
{
    char c;
    bool flag = true;
    printf("2048\n");
    while(flag)
    {
        printf("Play game? : (Y:yes)");
        c = getche();
        if(c != 'Y' && c != 'y') break;
        printf("\n");
        game g;
        g.play();
    }
    printf("\nQuit\n");
    return 0;
}

