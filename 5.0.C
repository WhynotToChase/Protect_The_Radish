#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BOARD_SIZE 12
#define EMPTY 0
#define BLACK 1
#define WHITE 2
typedef int BOOL;
#define TRUE 1
#define FALSE 0
#define START "START"
#define PLACE "PLACE"
#define TURN "TURN"
#define END "END"
#define MAXDEPTH 4

const double radio = 1.5;
const double bias = 1.2;
const int intmax = 2147483647;
const int intmin = -2147483647;
double maxmin[6] = { 0 };

char board[12][12] = { 0 };
int boardx[12] = { 0 };
int boardy[12] = { 0 };
int boardxy[15] = { 0 };
int boardyx[15] = { 0 };

int threepower[13] = { 1,3,9,27,81,243,729,2187,6561,19683,59049,177147 ,531441 };

int type6[729];
int type7[2187];
int type8[6561];
int type9[19683];
int type10[59049];
int type11[177147];
int type12[531441];
int value[243] = { 0 };

int* all[13] = { 0,0,0,0,0,value,type6,type7,type8,type9,type10,type11,type12 };

int myFlag;
int enemyFlag;
int thescore = 0;

BOOL first = 1;
BOOL themin(const int depth, int* score);
BOOL themax(const int depth, int* score);
BOOL thefrontmax(int* x, int* y, const int depth, int* score);

void unplace(const int x, const int y, const int flag);
void place(const int x, const int y, const int flag);

void debug(const int t1,const int t2)
{
    printf("DEBUG %d\n",t1*100-t2*100);
    fflush(stdout);
}

void create()
{
    int pure[32][2] = { {0,0},{1,12},{3,14},{4,120},{9,14},{10,114},{12,144},{13,1200},{27,14},{28,108},{30,137},
                      {31,1140},{36,144},{37,1140},{39,1440},{40,12000},{81,12},{82,85},{84,108},{85,900},
                      {90,114},{91,902},{93,1140},{94,9500},{108,120},{109,900},{111,1140},{112,9500},{117,1200},{118,9500},
                      {120,12000},{121,100000} };
    if (myFlag == BLACK)
        for (int i = 0; i < 32; i++) {
            value[pure[i][0]] = pure[i][1];
            value[pure[i][0] * 2] = -pure[i][1] * radio;
        }
    else
        for (int i = 0; i < 32; i++) {
            value[pure[i][0]] = -pure[i][1] * radio;
            value[pure[i][0] * 2] = pure[i][1];
        }
}

void largercreate()
{
    int* p = 0, * q = 0, largest = 0, four = 0, set = 0;
    for (int i = 6; i < 13; i++) {
        p = all[i];
        largest = threepower[i - 1];
        q = all[i - 1];
        for (int j = 0; j < largest; j++) {
            four = j % 81 * 3;
            set = j * 3;
            p[set] = q[j] + value[four];
            set++;
            four++;
            p[set] = q[j] + value[four];
            set++;
            four++;
            p[set] = q[j] + value[four];
        }
    }
}

void initAI(int me)
{
    enemyFlag = 3 - me;
}

void start(int flag)
{
    memset(board, 0, sizeof(board));
    int middlePlace = BOARD_SIZE / 2;
    place(5, 5, WHITE);
    place(6, 6, WHITE);
    place(5, 6, BLACK);
    place(6, 5, BLACK);
    create();
    largercreate();
    initAI(flag);
}

void turn()
{
    int x = -11, y = -11;
    int score = intmin;
    thefrontmax(&x, &y, 1, &score);
    printf("%d %d\n", x, y);
    fflush(stdout);
    place(x, y, myFlag);
}

void end(int x)
{
    exit(0);
}

void loop()
{
    char tag[10] = { 0 };
    int x = 0, y = 0;
    int status;
    while (TRUE)
    {
        memset(tag, 0, sizeof(tag));
        scanf("%s", tag);
        if (strcmp(tag, START) == 0)
        {
            scanf("%d", &myFlag);
            start(myFlag);
            printf("OK\n");
            fflush(stdout);
        }
        else if (strcmp(tag, PLACE) == 0)
        {
            scanf("%d %d", &x, &y);
            place(x, y, enemyFlag);
        }
        else if (strcmp(tag, TURN) == 0)
        {
                turn();
        }
        else if (strcmp(tag, END) == 0)
        {
            scanf("%d", &status);
            end(status);
        }
    }
}

int main(int argc, char* argv[])
{
    loop();
    return 0;
}


void place(const int x, const int y, const int flag)
{
    board[x][y] = flag;
    thescore -= type12[boardx[y]] + type12[boardy[x]];
    boardx[y] += flag * threepower[x];
    boardy[x] += flag * threepower[y];
    thescore += type12[boardx[y]] + type12[boardy[x]];

    int b = y - x, b1 = b < 0 ? y : x, b2 = b + 7, b3 = b>0 ? 12 - b : 12 + b;
    //b纵截距 b1当前位数 b2 序号 b3 总位数
    if (b >= -7 && b <= 7) {
        thescore -= all[b3][boardxy[b2]] * bias;
        boardxy[b2] += flag * threepower[b1];
        thescore += all[b3][boardxy[b2]] * bias;
    }


    int c = y + x, c1 = c > 11 ? 11 - y : x, c2 = c - 4, c3 = c > 11 ? 23 - c : c + 1;
    if (c >= 4 && c <= 18) {
        thescore -= all[c3][boardyx[c2]] * bias;
        boardyx[c2] += flag * threepower[c1];
        thescore += all[c3][boardyx[c2]] * bias;
    }
}

void unplace(const int x, const int y, const int flag)
{
    board[x][y] = 0;
    thescore -= type12[boardx[y]] + type12[boardy[x]];
    boardx[y] -= flag * threepower[x];
    boardy[x] -= flag * threepower[y];
    thescore += type12[boardx[y]] + type12[boardy[x]];

    int b = y - x, b1 = b < 0 ? y : x, b2 = b + 7, b3 = b>0 ? 12 - b : 12 + b;
    //b纵截距 b1当前位数 b2 序号 b3 总位数
    if (b >= -7 && b <= 7) {
        thescore -= all[b3][boardxy[b2]] * bias;
        boardxy[b2] -= flag * threepower[b1];
        thescore += all[b3][boardxy[b2]] * bias;
    }


    int c = y + x, c1 = c > 11 ? 11 - y : x, c2 = c - 4, c3 = c > 11 ? 23 - c : c + 1;
    if (c >= 4 && c <= 18) {
        thescore -= all[c3][boardyx[c2]] * bias;
        boardyx[c2] -= flag * threepower[c1];
        thescore += all[c3][boardyx[c2]] * bias;
    }
}

BOOL themax(const int depth, int* score)
{
    if (depth < MAXDEPTH)
        maxmin[depth + 1] = intmin;
    else if (depth == MAXDEPTH) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == 0) {
                    place(i, j, myFlag);
                    if (*score< thescore)
                        *score = thescore;
                    unplace(i, j, myFlag);
                }
            }
        }
        return 0;
    }

    int minscore = 0;
    BOOL p = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                minscore = intmax;
                p = 0;
                place(i, j, myFlag);
                p = themin(depth + 1, &minscore);
                if (p) {
                    unplace(i, j, myFlag);
                    continue;
                }
                if (minscore > maxmin[depth]) {
                    unplace(i, j, myFlag);
                    return 1;
                }
                else if (minscore > *score) {
                    *score = minscore;
                }
                unplace(i, j, myFlag);
            }
        }
    }

        maxmin[depth] = maxmin[depth] > *score ? *score : maxmin[depth];
    return 0;
}

BOOL themin(const int depth, int* score)
{
    if (depth < MAXDEPTH) {
        maxmin[depth + 1] = intmax;
    }
    else if (depth == MAXDEPTH) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == 0) {
                    place(i, j, enemyFlag);
                    if (*score > thescore)
                        *score = thescore;
                    unplace(i, j, enemyFlag);
                }
            }
        }
        return 0;
    }

    int maxscore = 0;
    BOOL p = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                maxscore = intmin;
                p = 0;
                place(i, j, enemyFlag);
                p = themax(depth + 1, &maxscore);
                if (p) {
                    unplace(i, j, enemyFlag);
                    continue;
                }
                if (maxscore < maxmin[depth]) {
                    unplace(i, j, enemyFlag);
                    return 1;
                }
                else if (maxscore < *score) {
                    *score = maxscore;
                }
                unplace(i, j, enemyFlag);
            }
        }
    }
    maxmin[depth] = maxmin[depth] < *score ? *score : maxmin[depth];
    return 0;
}

BOOL thefrontmax(int* x, int* y, const int depth, int* score)
{
    maxmin[depth + 1] = intmin;

    int minscore = 0;
    BOOL p = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                minscore = intmax;
                p = 0;
                place(i, j, myFlag);
                p = themin(depth + 1, &minscore);
                if (p) {
                    unplace(i, j, myFlag);
                    continue;
                }
                if (minscore > *score) {
                    *x = i, * y = j;
                    *score = minscore;
                }
                unplace(i, j, myFlag);
            }
        }
    }

    return 0;
}