/*   헤더 파일   */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

/*    가중치   */
#define Gard3 500
#define Gard2 300
#define AttackPoint100 100
#define AttackPoint200 200
#define AttackPoint800 800 // 정답 배열 가드보다 우선권.
#define AttackPoint20 20
#define WarnPoint999 999
#define WarnPoint100 100

/*    함수     */

// AI 알고리즘
void AI();
void AIDrawMap(int x);
void AIGard3();
void AIGard2();
void Attack4();
void Attack3();
void WeightPlus();
void WeightMinus();
//
void InitialArr(int *a);
void InitialData();
void PlayerMoveAction();
void DrawMap();
void CorrectDrawMap();
int ReStart();
int ArrayCheck1();
int ArrayCheck2();
//
void Intro();
void DigitalPrint(int dim[], int line);
void SpellCheck1(int line);
void SpellCheck2(int line);

/*    전역 변수   */
char ch;
char player1_ch = 'O';
char player2_ch = '@';
int Playerx = 0;
int Playery = 0;
int PlayCount = 1;
char data[7][9] = {
        {'|', '.', '.', '.', '.', '.', '.', '.', '|'},
        {'|', '.', '.', '.', '.', '.', '.', '.', '|'},
        {'|', '.', '.', '.', '.', '.', '.', '.', '|'},
        {'|', '.', '.', '.', '.', '.', '.', '.', '|'},
        {'|', '.', '.', '.', '.', '.', '.', '.', '|'},
        {'|', '.', '.', '.', '.', '.', '.', '.', '|'},
        {'|', '_', '_', '_', '_', '_', '_', '_', '|'}
    };
char Initial_data[7][9] = {
        {'|', '.', '.', '.', '.', '.', '.', '.', '|'},
        {'|', '.', '.', '.', '.', '.', '.', '.', '|'},
        {'|', '.', '.', '.', '.', '.', '.', '.', '|'},
        {'|', '.', '.', '.', '.', '.', '.', '.', '|'},
        {'|', '.', '.', '.', '.', '.', '.', '.', '|'},
        {'|', '.', '.', '.', '.', '.', '.', '.', '|'},
        {'|', '_', '_', '_', '_', '_', '_', '_', '|'}
    };
int WeightData[6][7] = {0,};
char player_ch[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
int CorrectArr[4][2] = {0,};
int Duo = 1;

int Spell_F[15] = {
    1, 1, 1,
    1, 0, 0,
    1, 1, 1,
    1, 0, 0,
    1, 0, 0
};
int Spell_o[15] = {
    0, 0, 0,
    0, 0, 0,
    1, 1, 1,
    1, 0, 1,
    1, 1, 1
};
int Spell_u[15] = {
    0, 0, 0,
    0, 0, 0,
    1, 0, 1,
    1, 0, 1,
    1, 1, 1
};
int Spell_r[15] = {
    0, 0, 0,
    0, 0, 0,
    1, 1, 1,
    1, 0, 0,
    1, 0, 0
};
int Spell_i[15] = {
    0, 1, 0,
    0, 0, 0,
    0, 1, 0,
    0, 1, 0,
    0, 1, 0
};
int Spell_n[15] = {
    0, 0, 0,
    0, 0, 0,
    1, 1, 1,
    1, 0, 1,
    1, 0, 1
};
int Spell_a[15] = {
    0, 0, 0,
    0, 1, 0,
    1, 0, 1,
    1, 1, 1,
    1, 0, 1
};
int Spell_R[15] = {
    1, 1, 1,
    1, 0, 1,
    1, 1, 1,
    1, 1, 0,
    1, 0, 1
};
int Spell_w[15] = {
    0, 0, 0,
    0, 0, 0,
    1, 1, 1,
    1, 1, 1,
    0, 1, 0
};

int main(void)
{
    Intro();
    if(Duo == 0)
    {
        while (1)
        {
            DrawMap();
            if(PlayCount % 2 == 1) PlayerMoveAction();
            if(ArrayCheck1())
            {
                CorrectDrawMap();
                if(ReStart()) InitialData();
                else break;
            }
            if(PlayCount % 2 == 0) AI();
            if(ArrayCheck2())
            {
                CorrectDrawMap();
                if(ReStart()) InitialData();
                else break;
            }
        }
    }
    else
    {
        while (1)
        {
            DrawMap();
            PlayerMoveAction();
            if(ArrayCheck1())
            {
                CorrectDrawMap();
                if(ReStart()) InitialData();
                else break;
            }
            if(ArrayCheck2())
            {
                CorrectDrawMap();
                if(ReStart()) InitialData();
                else break;
            }
        }
    }
    printf("\n             GG Good Game..\n");
    Sleep(1000);
    return 0;
}

void AI()
{
    srand(time(NULL));
    // 가중치 초기화
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            WeightData[i][j] = 0;
        }
    }
    int x = rand() % 7 + 1, y = 0, min_weight;
    int dy = 1;
    AIGard3();
    AIGard2();
    Attack4();
    Attack3();
    WeightMinus();
    WeightPlus();
    min_weight = 0;
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            if(min_weight > WeightData[i][j] && data[i][j + 1] == '.')
            {
                min_weight = WeightData[i][j];
                x = j + 1;
            }
        }
    }
    while(data[y+dy][x] == '.' && y != 5)
    {
        y += dy;
    }
    AIDrawMap(x);
    data[y][x] = '@';
    PlayCount++;
    x = 0;
    y = 0;
}
void AIGard2()
{
    // 가로 체크
    for(int i = 0 ; i < 6; i++)
    {
        for(int j = 4; j < 8; j++)
        {
            if(data[i][j-3] == '.' && data[i][j-2] == 'O' && data[i][j-1] == 'O' && data[i][j] == '.')
            {
                if(i == 5)
                {
                    WeightData[i][j - 1] -= Gard2;
                    WeightData[i][j - 4] -= Gard2;
                }
                else
                {
                    if(data[i + 1][j] != '.') WeightData[i][j - 1] -= Gard2;
                    if(data[i + 1][j - 3] != '.') WeightData[i][j - 4] -= Gard2;
                }
            }
        }
    }
    for(int i = 0 ; i < 6; i++)
    {
        for(int j = 5; j < 8; j++)
        {
            if(data[i][j - 4] == '.' && data[i][j-3] == 'O' && data[i][j-2] == '.' && data[i][j-1] == 'O' && data[i][j] == '.')
            {
                if(i == 5) WeightData[i][j - 3] -= Gard2;
                else if(data[i + 1][j - 2] != '.') WeightData[i][j - 3] -= Gard2;
            }
        }
    }
}
void AIGard3()
{   
    // 가로 체크
    for(int i = 0; i < 6; i++)
    {
        for(int j = 4; j < 8; j++)
        {
            if(data[i][j-3] == 'O' && data[i][j-2] == 'O' && data[i][j-1] == 'O' && data[i][j] == '.')  
            {   
                if(i == 5) WeightData[i][j - 1] -= Gard3;
                else 
                {
                    if(data[i + 1][j] != '.') WeightData[i][j - 1] -= Gard3;
                    else if(data[i + 2][j] != '.') WeightData[i+1][j - 1] += WarnPoint999;
                    else if(data[i + 2][j] == '.') WeightData[i+2][j - 1] += WarnPoint100;
                }
            }
            if(data[i][j-3] == '.' && data[i][j-2] == 'O' && data[i][j-1] == 'O' && data[i][j] == 'O')
            {
                if(i == 5) WeightData[i][j - 4] -= Gard3;
                else
                {
                    if(data[i + 1][j-3] != '.') WeightData[i][j-4] -= Gard3;
                    else if(data[i + 2][j-3] != '.') WeightData[i+1][j-4] += WarnPoint999;
                    else if(data[i + 2][j-3] == '.') WeightData[i+2][j-4] += WarnPoint100;
                }
            }
            if(data[i][j-3] == 'O' && data[i][j-2] == '.' && data[i][j-1] == 'O' && data[i][j] == 'O')  
            {
                if(i == 5) WeightData[i][j - 3] -= Gard3;
                else
                {
                    if(data[i + 1][j - 2] != '.') WeightData[i][j - 3] -= Gard3;
                    else if(data[i + 2][j - 2] != '.') WeightData[i+1][j - 3] += WarnPoint999;
                    else if(data[i + 2][j - 2] == '.') WeightData[i+2][j - 3] += WarnPoint100;
                }  
            }
            if(data[i][j-3] == 'O' && data[i][j-2] == 'O' && data[i][j-1] == '.' && data[i][j] == 'O')
            {
                if(i == 5) WeightData[i][j - 2] -= Gard3;
                else
                {
                    if(data[i + 1][j - 1] != '.') WeightData[i][j - 2] -= Gard3;
                    else if(data[i + 2][j - 1] != '.') WeightData[i+1][j - 2] += WarnPoint999;
                    else if(data[i + 2][j - 1] == '.') WeightData[i+2][j - 2] += WarnPoint100;
                }
            }
        }
    }
    // 세로 체크
    for(int i = 1;i < 8; i++)
    {
        for(int j = 3; j<6;j++)
        {
            if(data[j-3][i] == '.' && data[j-2][i] == 'O' && data[j-1][i] == 'O' && data[j][i] == 'O') WeightData[j-3][i - 1] -= Gard3;
        }
    }
    // 대각선 체크
    for(int i = 3;i < 6; i++)
    {
        for(int j = 4; j<8;j++)
        {
            if(data[i-3][j-3] == '.' && data[i-2][j-2] == 'O' && data[i-1][j-1] == 'O' && data[i][j] == 'O')
            {
                if(data[i-2][j-3] != '.') WeightData[i-3][j-4] -= Gard3;
                else if(data[i-1][j-3] != '.') WeightData[i-2][j-4] += WarnPoint999;
                else if(data[i-1][j-3] == '.') WeightData[i-1][j-4] += WarnPoint100;
            }
            if(data[i-3][j-3] == 'O' && data[i-2][j-2] == 'O' && data[i-1][j-1] == 'O' && data[i][j] == '.')
            {
                if(i == 5) WeightData[i][j - 1] -= Gard3;
                else
                {
                    if(data[i+1][j] != '.') WeightData[i][j - 1] -= Gard3;
                    else if(data[i+2][j] != '.') WeightData[i+1][j - 1] += WarnPoint999; 
                    else if(data[i+2][j] == '.') WeightData[i+2][j - 1] += WarnPoint100; 
                }
            }
            if(data[i-3][j-3] == 'O' && data[i-2][j-2] == '.' && data[i-1][j-1] == 'O' && data[i][j] == 'O')
            {
                if(data[i-1][j-2] != '.') WeightData[i-2][j-3] -= Gard3;
                else if(data[i][j-2] != '.') WeightData[i - 1][j-3] += WarnPoint999;
                else if(data[i][j-2] == '.') WeightData[i][j-3] += WarnPoint100;
            }
            if(data[i-3][j-3] == 'O' && data[i-2][j-2] == 'O' && data[i-1][j-1] == '.' && data[i][j] == 'O')
            {
                if(data[i][j - 1] != '.') WeightData[i - 1][j - 2] -= Gard3;
                else if(data[i+1][j - 1] != '.') WeightData[i][j - 2] += WarnPoint999;
                else if(data[i+1][j - 1] == '.') WeightData[i+1][j - 2] += WarnPoint100;
            }
        }
    }
    // 역 대각선 체크
    for(int i = 3;i < 6; i++)
    {
        for(int j = 4; j<8;j++)
        {
            if(data[i-3][j] == '.' && data[i-2][j-1] == 'O' && data[i-1][j-2] == 'O' && data[i][j-3] == 'O')
            {
                if(data[i-2][j] != '.') WeightData[i-3][j - 1] -= Gard3;
                else if(data[i-1][j] != '.') WeightData[i-2][j - 1] += WarnPoint999;
                else if(data[i-1][j] == '.') WeightData[i-1][j - 1] += WarnPoint100;
            }
            if(data[i-3][j] == 'O' && data[i-2][j-1] == 'O' && data[i-1][j-2] == 'O' && data[i][j-3] == '.')
            {
                if(i == 5) WeightData[i][j-4] -= Gard3;
                else
                {
                    if(data[i+1][j-3] != '.') WeightData[i][j-4] -= Gard3;
                    else if(data[i+2][j-3] != '.') WeightData[i+1][j-4] += WarnPoint999;
                    else if(data[i+2][j-3] == '.') WeightData[i+2][j-4] += WarnPoint100;
                }
            }
            if(data[i-3][j] == 'O' && data[i-2][j-1] == '.' && data[i-1][j-2] == 'O' && data[i][j-3] == 'O')
            {
                if(data[i-1][j - 1] != '.') WeightData[i-2][j - 2] -= Gard3;
                else if(data[i][j - 1] != '.') WeightData[i-1][j - 2] += WarnPoint999;
                else if(data[i][j - 1] == '.') WeightData[i][j - 2] += WarnPoint100;
            }
            if(data[i-3][j] == 'O' && data[i-2][j-1] == 'O' && data[i-1][j-2] == '.' && data[i][j-3] == 'O')
            {
                if(data[i][j - 2] != '.') WeightData[i - 1][j - 3] -= Gard3;
                else if(data[i+1][j-2] != '.') WeightData[i][j - 3] += WarnPoint999;
                else if(data[i+1][j-2] == '.') WeightData[i+1][j - 3] += WarnPoint100;
            }
        }
    }
}
void Attack4()
{
    // 가로 체크
    for(int i= 0; i < 6; i++)
    {
        for(int j = 4; j < 8; j++)
        {
            if(data[i][j-3] == '@' && data[i][j-2] == '@' && data[i][j-1] == '@' && data[i][j] == '.')
            {  
                if(i == 5) WeightData[i][j - 1] -= AttackPoint800;
                else
                {
                    if(data[i + 1][j] != '.') WeightData[i][j - 1] -= AttackPoint800;
                    else if(data[i + 2][j] != '.') WeightData[i+1][j - 1] += AttackPoint200;
                    else if(data[i + 2][j] == '.') WeightData[i+2][j - 1] -= AttackPoint200;  // weight point
                }
            }
            if(data[i][j-3] == '.' && data[i][j-2] == '@' && data[i][j-1] == '@' && data[i][j] == '@')
            {
                if(i == 5) WeightData[i][j - 4] -= AttackPoint800;
                else
                {
                    if(data[i + 1][j - 3] != '.') WeightData[i][j - 4] -= AttackPoint800;
                    else if(data[i + 2][j - 3] != '.') WeightData[i+1][j - 4] += AttackPoint200;
                    else if(data[i + 2][j - 3] == '.') WeightData[i+2][j - 4] -= AttackPoint200;  // weight point
                }
            }
            if(data[i][j-3] == '@' && data[i][j-2] == '.' && data[i][j-1] == '@' && data[i][j] == '@')
            {  
                if(i == 5) WeightData[i][j - 3] -= AttackPoint800;
                else
                {
                    if(data[i + 1][j - 2] != '.') WeightData[i][j - 3] -= AttackPoint800;
                    else if(data[i + 2][j - 2] != '.') WeightData[i+1][j - 3] += AttackPoint200;
                    else if(data[i + 2][j - 2] == '.') WeightData[i+2][j - 3] -= AttackPoint200;  // weight point
                }
            }
            if(data[i][j-3] == '@' && data[i][j-2] == '@' && data[i][j-1] == '.' && data[i][j] == '@')
            {
                if(i == 5) WeightData[i][j - 3] -= AttackPoint800;
                else
                {
                    if(data[i + 1][j - 1] != '.') WeightData[i][j - 2] -= AttackPoint800;
                    else if(data[i + 2][j - 1] != '.') WeightData[i+1][j - 2] += AttackPoint200;
                    else if(data[i + 2][j - 1] == '.') WeightData[i+2][j - 2] -= AttackPoint200;  // weight point
                }
            }
        }
    }
    // 세로 체크
    for(int i = 1;i < 8; i++)
    {
        for(int j = 3; j<6;j++)
        {
            if(data[j-3][i] == '.' && data[j-2][i] == '@' && data[j-1][i] == '@' && data[j][i] == '@') WeightData[j-3][i - 1] -= AttackPoint800;
        }
    }
    // 대각선 체크
    for(int i = 3;i < 6; i++)
    {
        for(int j = 4; j<8;j++)
        {
            if(data[i-3][j-3] == '.' && data[i-2][j-2] == '@' && data[i-1][j-1] == '@' && data[i][j] == '@')
            {
                if(data[i-2][j-3] != '.') WeightData[i-3][j - 4] -= AttackPoint800;
                else if(data[i-1][j-3] != '.') WeightData[i-2][j-4] += AttackPoint200;
                else if(data[i-1][j-3] == '.') WeightData[i-1][j-4] -= AttackPoint200;
            }
            if(data[i-3][j-3] == '@' && data[i-2][j-2] == '@' && data[i-1][j-1] == '@' && data[i][j] == '.')
            {
                if(i == 5) WeightData[i][j - 1] -= AttackPoint800;
                else
                {
                    if(data[i+1][j] != '.') WeightData[i][j - 1] -= AttackPoint800;
                    else if(data[i+2][j] != '.') WeightData[i+1][j - 1] += AttackPoint200; 
                    else if(data[i+2][j] == '.') WeightData[i+2][j - 1] -= AttackPoint200; 
                }
            }
            if(data[i-3][j-3] == '@' && data[i-2][j-2] == '.' && data[i-1][j-1] == '@' && data[i][j] == '@')
            {
                if(data[i-1][j-2] != '.') WeightData[i-2][j-3] -= AttackPoint800;
                else if(data[i][j-2] != '.') WeightData[i - 1][j-3] += AttackPoint200;
                else if(data[i][j-2] == '.') WeightData[i][j-3] -= AttackPoint200;
            }
            if(data[i-3][j-3] == '@' && data[i-2][j-2] == '@' && data[i-1][j-1] == '.' && data[i][j] == '@')
            {
                if(data[i][j - 1] != '.') WeightData[i - 1][j - 2] -= AttackPoint800;
                else if(data[i+1][j - 1] != '.') WeightData[i][j - 2] += AttackPoint200;
                else if(data[i+1][j - 1] == '.') WeightData[i+1][j - 2] -= AttackPoint200;
            }
        }
    }
    // 역 대각선 체크
    for(int i = 3;i < 6; i++)
    {
        for(int j = 4; j<8;j++)
        {
            if(data[i-3][j] == '.' && data[i-2][j-1] == '@' && data[i-1][j-2] == '@' && data[i][j-3] == '@')
            {
                if(data[i-2][j] != '.') WeightData[i-3][j - 1] -= AttackPoint800;
                else if(data[i-1][j] != '.') WeightData[i-2][j - 1] += AttackPoint200;
                else if(data[i-1][j] == '.') WeightData[i-1][j - 1] -= AttackPoint200;
            }
            if(data[i-3][j] == '@' && data[i-2][j-1] == '@' && data[i-1][j-2] == '@' && data[i][j-3] == '.')
            {
                if(i == 5) WeightData[i][j - 4] -= AttackPoint800;
                else
                {
                    if(data[i+1][j-3] != '.') WeightData[i][j-4] -= AttackPoint800;
                    else if(data[i+2][j-3] != '.') WeightData[i+1][j-4] += AttackPoint200;
                    else if(data[i+2][j-3] == '.') WeightData[i+2][j-4] -= AttackPoint200;
                }
            }
            if(data[i-3][j] == '@' && data[i-2][j-1] == '.' && data[i-1][j-2] == '@' && data[i][j-3] == '@')
            {
                if(data[i-1][j - 1] != '.') WeightData[i-2][j - 2] -= AttackPoint800;
                else if(data[i][j - 1] != '.') WeightData[i-1][j - 2] += AttackPoint200;
                else if(data[i][j - 1] == '.') WeightData[i][j - 2] -= AttackPoint200;
            }
            if(data[i-3][j] == '@' && data[i-2][j-1] == '@' && data[i-1][j-2] == '.' && data[i][j-3] == '@')
            {
                if(data[i][j - 2] != '.') WeightData[i - 1][j - 3] -= AttackPoint800;
                else if(data[i+1][j-2] != '.') WeightData[i][j - 3] += AttackPoint200;
                else if(data[i+1][j-2] == '.') WeightData[i+1][j - 3] -= AttackPoint200;
            }
        }
    }
}
void Attack3()
{
    // 가로 체크
    for(int i = 0;i<6;i++)
    {
        for(int j = 3; j < 8;j++)
        {
            if(data[i][j - 2] == '.' && data[i][j - 1] == '@' && data[i][j] == '@')
            {
                if(i == 5) WeightData[i][j - 3] -= AttackPoint100;
                else
                {
                    if(data[i + 1][j - 2] != '.') WeightData[i][j-3] -= AttackPoint100;
                    else if(data[i + 2][j - 2] == '.') WeightData[i+2][j-3] -= AttackPoint20;
                }
            }
            if(data[i][j - 2] == '@' && data[i][j - 1] == '@' && data[i][j] == '.')
            {
                if(i == 5) WeightData[i][j - 1] -= AttackPoint100;
                else
                {
                    if(data[i + 1][j] != '.') WeightData[i][j - 1] -= AttackPoint100;
                    else if(data[i + 2][j] == '.') WeightData[i+2][j - 1] -= AttackPoint20;
                }
            } 
        }
    }
    for(int i = 0; i < 6; i++)
    {
        for(int j = 4; j < 8; j++)
        {
            if(data[i][j-3] == '@' && data[i][j-2] == '.' && data[i][j-1] == '@' && data[i][j] == '.')
            {
                if(i == 5)
                {
                    WeightData[i][j - 3] -= AttackPoint200;
                    WeightData[i][j - 1] -= AttackPoint200;
                } 
                else
                {
                    if(data[i + 1][j - 2] != '.') WeightData[i][j - 3] -= AttackPoint200;
                    else if(data[i + 2][j - 2] == '.') WeightData[i+2][j - 3] -= AttackPoint20;  // weight point
                    if(data[i + 1][j] != '.') WeightData[i][j - 1] -= AttackPoint200;
                    else if(data[i + 2][j] == '.') WeightData[i+2][j - 1] -= AttackPoint20;  // weight point
                }  
            }
            if(data[i][j-3] == '.' && data[i][j-2] == '@' && data[i][j-1] == '.' && data[i][j] == '@')
            {
                if(i == 5)
                {
                    WeightData[i][j - 2] -= AttackPoint200;
                    WeightData[i][j - 4] -= AttackPoint200;
                } 
                else
                {
                    if(data[i + 1][j - 1] != '.') WeightData[i][j - 2] -= AttackPoint200;
                    else if(data[i + 2][j - 1] == '.') WeightData[i+2][j - 2] -= AttackPoint20;  // weight point
                    if(data[i + 1][j-3] != '.') WeightData[i][j-4] -= AttackPoint200;
                    else if(data[i + 2][j-3] != '.') WeightData[i+1][j-4] -= AttackPoint20;  // weight point
                }
            }
        }
    }
    // 세로 체크
    for(int i = 1; i < 8;i++)
    {
        for(int j = 2; j < 6; j++)
        {
            if(data[j - 2][i] == '.' && data[j - 1][i] == '@' && data[j][i] == '@') WeightData[j - 2][i - 1] -= AttackPoint200;
        }
    }

    // 대각선 체크
    for(int i = 2; i < 6; i++)
    {
        for(int j = 3;j < 8; j++)
        {
            if(data[i - 2][j - 2] == '.' && data[i - 1][j - 1] == '@' && data[i][j] == '@')
            {
                if(data[i - 1][j - 2] != '.') WeightData[i - 2][j - 3] -= AttackPoint100;
                else
                {
                    if(data[i][j - 2] == '.') WeightData[i][j - 3] -= AttackPoint20;
                }
            }
            if(data[i - 2][j - 2] == '@' && data[i - 1][j - 1] == '@' && data[i][j] == '.')
            {
                if(i == 5) data[i][j - 1] -= AttackPoint100;
                else
                {
                    if(data[i+1][j] != '.') WeightData[i][j - 1] -= AttackPoint100;
                    else if(data[i+2][j] == '.') WeightData[i+2][j - 1] -= AttackPoint20;
                }
            }
        }
    }
    for(int i = 3; i < 6; i++)
    {
        for(int j = 4;j < 8; j++)
        {
            if(data[i - 3][j - 3] == '.' && data[i - 2][j - 2] == '@' && data[i - 1][j - 1] == '.' && data[i][j] == '@')
            {
                if(data[i - 2][j - 3] != '.') WeightData[i - 3][j - 4] -= AttackPoint200;
                else if(data[i - 1][j - 3] == '.') WeightData[i - 1][j - 4] -= AttackPoint20; // weight point
                if(data[i][j - 1] != '.') WeightData[i - 1][j - 2] -= AttackPoint200;
                else if(data[i + 1][j - 1] == '.') WeightData[i + 1][j - 2] -= AttackPoint20; // weight point
            }
            if(data[i - 3][j - 3] == '@' && data[i - 2][j - 2] == '.' && data[i - 1][j - 1] == '@' && data[i][j] == '.')
            {
                if(i == 5) WeightData[i][j - 1] -= AttackPoint200;
                else
                {
                    if(data[i - 1][j - 2] != '.') WeightData[i - 2][j - 3] -= AttackPoint200;
                    else if(data[i][j - 2] == '.') WeightData[i][j - 3] -= AttackPoint20; // weight point
                    if(data[i + 1][j] != '.') WeightData[i][j - 1] -= AttackPoint200;
                    else if(data[i + 2][j] == '.') WeightData[i + 2][j - 1] -= AttackPoint20; // weight point
                }
            }
        }
    }
    // 역 대각선 체크
    for(int i = 2; i < 6; i++)
    {
        for(int j = 3;j < 8; j++)
        {
            if(data[i - 2][j] == '.' && data[i - 1][j - 1] == '@' && data[i][j - 2] == '@')
            {
                if(data[i - 1][j] != '.') WeightData[i - 2][j - 1] -= AttackPoint100;
                else if(data[i][j] == '.') WeightData[i][j - 1] -= AttackPoint20;
            }
            if(data[i - 2][j] == '@' && data[i - 1][j - 1] == '@' && data[i][j - 2] == '.')
            {
                if(i == 5) data[i][j - 3] -= AttackPoint100;
                else
                {
                    if(data[i+1][j - 2] != '.') WeightData[i][j - 3] -= AttackPoint100;
                    else if(data[i+2][j - 2] == '.') WeightData[i+2][j - 3] -= AttackPoint20;
                }
            }
        }
    }
    for(int i = 3; i < 6; i++)
    {
        for(int j = 4;j < 8; j++)
        {
            if(data[i - 3][j] == '.' && data[i - 2][j - 1] == '@' && data[i - 1][j - 2] == '.' && data[i][j - 3] == '@')
            {
                if(data[i - 2][j] != '.') WeightData[i - 3][j - 1] -= AttackPoint200;
                else if(data[i - 1][j] == '.') WeightData[i - 1][j - 1] -= AttackPoint20; // weight point
                if(data[i][j - 2] != '.') WeightData[i - 1][j - 3] -= AttackPoint200;
                else if(data[i + 1][j - 2] == '.') WeightData[i + 1][j - 3] -= AttackPoint20; // weight point
            }
            if(data[i - 3][j] == '@' && data[i - 2][j - 1] == '.' && data[i - 1][j - 2] == '@' && data[i][j - 3] == '.')
            {
                if(i == 5) WeightData[i][j] -= AttackPoint200;
                else
                {
                    if(data[i - 1][j - 1] != '.') WeightData[i - 2][j - 2] -= AttackPoint200;
                    else if(data[i][j - 1] == '.') WeightData[i][j - 2] -= AttackPoint20; // weight point
                    if(data[i + 1][j - 3] != '.') WeightData[i][j - 4] -= AttackPoint200;
                    else if(data[i + 2][j - 3] == '.') WeightData[i + 2][j - 4] -= AttackPoint20; // weight point
                }
            }
        }
    }
}
void WeightPlus()
{
    int x, y;
    for(int i = 0; i<6;i++)
    {
        for(int j = 1;j<8;j++)
        {
            if(data[i][j] == '@')
            {
                y = i, x = j;
                for(int a = -1; a < 2; a++)
                {
                    for(int b = -1; b < 2; b++)
                    {
                        if(data[y + a][x + b] == '.') WeightData[y+a][x+b]++;
                    }
                }
            }
        }
    }
}
void WeightMinus()
{
    int x, y;
    for(int i = 0; i<6;i++)
    {
        for(int j = 1;j<8;j++)
        {
            if(data[i][j] == 'O')
            {
                y = i, x = j;
                for(int a = -1; a < 2; a++)
                {
                    for(int b = -1; b < 2; b++)
                    {
                        if(data[y + a][x + b] == '.') WeightData[y+a][x+b]--;
                    }
                }
            }
        }
    }
}
void InitialArr(int *a)
{
    for(int i = 0;i<4;i++) CorrectArr[i][0] = 0,  CorrectArr[i][1] = 0;
    *a = 0;
}

void InitialData()
{
    for(int i = 0; i < 9;i++)
    {
        player_ch[i] = ' ';
    }
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            data[i][j] = Initial_data[i][j];
        }
    }
    if(PlayCount % 2 == 0) PlayCount = 1;
    else PlayCount = 0;
    printf("\n             Restarting.");
    Sleep(600);
    printf(".");
    Sleep(600);
    printf(".");
    Sleep(800);
}

void PlayerMoveAction()
{
    int dx = 0, dy = 0;
    ch = getch();
    // 홀 짝으로 플레이 순서 구분
    if(PlayCount % 2 == 1)
    {
        switch (ch)
        {
        case 'a': dx = -1; break;
        case 'A': dx = -1; break;
        case 'd': dx = 1; break;
        case 'D': dx = 1; break;
        case 's': dy = 1; break;
        case 'S': dy = 1; break;
        }
        if((Playerx == 0 && dx == -1)|| (Playerx == 8 && dx == 1)) return;
        player_ch[Playerx] = ' ';
        if(ch == 's' || ch == 'S')
        {
            if(data[0][Playerx] != '.') return;
            // 빈 공간일 경우 초기 위치에 dy++
            while(data[Playery+dy][Playerx] == '.' && Playery != 5)
            {
                Playery += dy;
            }
            data[Playery][Playerx] = player1_ch;
            PlayCount++;
            Playery = 0;
            Playerx = 0;
            return;
        }
        Playerx += dx;
    }
    else
    {
        switch (ch)
        {
        case 'j': dx = -1; break;
        case 'J': dx = -1; break;
        case 'l': dx = 1; break;
        case 'L': dx = 1; break;
        case 'k': dy = 1; break;
        case 'K': dy = 1; break;
        }
        if((Playerx == 0 && dx == -1)|| (Playerx == 8 && dx == 1)) return;
        player_ch[Playerx] = ' ';
        if(ch == 'k' || ch == 'K')
        {
            if(data[0][Playerx] != '.') return;
            while(data[Playery+dy][Playerx] == '.' && Playery != 5)
            {
                Playery += dy;
            }
            data[Playery][Playerx] = player2_ch;
            PlayCount++;
            Playery = 0;
            Playerx = 0;
            return;
        }
        Playerx += dx;
    }
}

void AIDrawMap(int x)
{
    int dx, rx = 0;
    for(dx = 0; dx <= x; dx++)
    {
        system("cls");
        printf("\n\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        // 26칸 띄움.
        printf("                          Four      In      A      Row");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        printf("\n\n");
        // 6칸 띄움.
        printf("      ");
        player_ch[rx] = '@';
        for(int i = 0; i<9;i++) 
        {
            if(player_ch[i] == '@')
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                printf("%7c", player_ch[i]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
            else printf("%7c", player_ch[i]);
        }
        player_ch[rx] = ' ';
        rx++;
        printf("\n\n");
        for(int i = 0;i<7;i++)
        {
            printf("      ");
            for(int j=0;j<9;j++)
            {
                if(data[i][j] == 'O')
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
                    printf("%7c", data[i][j]);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
                else if(data[i][j] == '@')
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    printf("%7c", data[i][j]);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
                else printf("%7c", data[i][j]);
            }
            printf("\n\n");
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        Sleep(500);
    }
}
void DrawMap()
{
    system("cls");
    
    printf("\n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    // 26칸 띄움.
    printf("                          Four      In      A      Row");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    printf("\n\n");
    if(PlayCount % 2 == 1) player_ch[Playerx] = player1_ch;
    else player_ch[Playerx] = player2_ch;
    // 6칸 띄움.
    printf("      ");
    for(int i = 0; i<9;i++) 
    {
        if(player_ch[i] == 'O')
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
            printf("%7c", player_ch[i]);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

        }
        else if(player_ch[i] == '@')
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            printf("%7c", player_ch[i]);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }
        else printf("%7c", player_ch[i]);
    }
    printf("\n\n");
    for(int i = 0;i<7;i++)
    {
        printf("      ");
        for(int j=0;j<9;j++)
        {
            if(data[i][j] == 'O')
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
                printf("%7c", data[i][j]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
            else if(data[i][j] == '@')
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                printf("%7c", data[i][j]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
            else printf("%7c", data[i][j]);
        }
        printf("\n\n");
    }
}

void CorrectDrawMap()
{
    system("cls");
    printf("\n\n");
    // 20칸 띄움.
    if(PlayCount % 2 == 0)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        printf("                    A   Player");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        printf("   V   I   C   T   O   R   Y  !!");
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        printf("                    B   Player");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        printf("   V   I   C   T   O   R   Y  !!");
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    printf("\n\n");
    printf("      ");
    for(int i = 0; i<9;i++) 
    {
        printf("%7c", ' ');
    }
    printf("\n\n");
    for(int i = 0;i<7;i++)
    {
        printf("      ");
        for(int j=0;j<9;j++)
        {
            if((i == CorrectArr[0][0] && j == CorrectArr[0][1]) || (i == CorrectArr[1][0] && j == CorrectArr[1][1]) || (i == CorrectArr[2][0] && j == CorrectArr[2][1]) || (i == CorrectArr[3][0] && j == CorrectArr[3][1]))
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                printf("%7c", data[i][j]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
            else printf("%7c", data[i][j]);
        }
        printf("\n\n");
    }
}

int ReStart()
{
    char ch1;
    int Re;
    printf("             Restart? (Y/N) : ");
    while(1)
    {
        ch = getch();
        switch (ch)
        {
        case 'y':
            Re = 1, printf("%c\n", ch); return Re;
            break;
        case 'Y':
            Re = 1, printf("%c\n", ch); return Re;
            break;
        case 'n':
            Re = 0, printf("%c\n", ch); return Re;
            break;
        case 'N':
            Re = 0, printf("%c\n", ch); return Re;
            break;
        default:
            break;
        }
    }
}

int ArrayCheck1()
{
    int count = 0;
    int a = 0;
    // 가로로 배열 확인
    for(int i = 0; i < 6;i++)
    {
        for(int j = 1; j < 8; j++)
        {
            if(data[i][j] == 'O')
            {
                count++;
                CorrectArr[a][0] = i, CorrectArr[a][1] = j;
                a++;
                if(count >= 4) return 1;
            }
            else
            {
                count = 0;
                InitialArr(&a);
            }
        }
        count = 0;
        InitialArr(&a);
    }
    // 세로로 배열 확인
    count = 0;
    for(int i = 1; i < 8;i++)
    {
        for(int j = 0; j < 6; j++)
        {
            if(data[j][i] == 'O')
            {
                count++;
                CorrectArr[a][0] = j, CorrectArr[a][1] = i;
                a++;
                if(count >= 4) return 1;
            }
            else
            {
                count = 0;
                InitialArr(&a);
            }
        }
        count = 0;
        InitialArr(&a);
    }
    // 대각선으로 배열 확인
    count = 0;
    int spin1, spin2;
    // 왼쪽 계단
    for(int j = 0; j < 6; j++)
    {
        spin1 = j;
        for(int i = 1; i < 7; i++)
        {
            if(data[spin1][i] == 'O')
            {
                count++;
                CorrectArr[a][0] = spin1, CorrectArr[a][1] = i;
                a++;
                if(count >= 4) return 1;
            }
            else
            {
                count = 0;
                InitialArr(&a);
            }
            spin1++;
            if(spin1 > 5) break;
        }
        count = 0;
        InitialArr(&a);
    }
    count = 0;
    // 왼쪽 역계단
    for(int j = 5; j >= 0; j--)
    {
        spin1 = j;
        for(int i = 1; i < 7; i++)
        {
            if(data[spin1][i] == 'O')
            {
                count++;
                CorrectArr[a][0] = spin1, CorrectArr[a][1] = i;
                a++;
                if(count >= 4) return 1;
            }
            else
            {
                count = 0;
                InitialArr(&a);
            }
            spin1--;
            if(spin1 < 0) break;
        }
        count = 0;
        InitialArr(&a);
    }
    count = 0;
    // 오른쪽 역계단
    for(int j = 5; j >= 0; j--)
    {
        spin2 = j;
        for(int i = 7; i > 1; i--)
        {
            if(data[spin2][i] == 'O')
            {
                count++;
                CorrectArr[a][0] = spin2, CorrectArr[a][1] = i;
                a++;
                if(count >= 4) return 1;
            }
            else
            {
                count = 0;
                InitialArr(&a);
            }
            spin2--;
            if(spin2 < 0) break;
        }
        count = 0;
        InitialArr(&a);
    }
    count = 0;
    // 오른쪽 계단
    for(int j = 0; j < 6; j++)
    {
        spin2 = j;
        for(int i = 7; i > 1; i--)
        {
            if(data[spin2][i] == 'O')
            {
                count++;
                CorrectArr[a][0] = spin2, CorrectArr[a][1] = i;
                a++;
                if(count >= 4) return 1;
            }
            else
            {
                count = 0;
                InitialArr(&a);
            }
            spin2++;
            if(spin2 > 5) break;
        }
        count = 0;
        InitialArr(&a);
    }
    return 0;
}
int ArrayCheck2()
{
    int count = 0;
    int a = 0;
    // 가로로 배열 확인
    for(int i = 0; i < 6;i++)
    {
        for(int j = 1; j < 8; j++)
        {
            if(data[i][j] == '@')
            {
                count++;
                CorrectArr[a][0] = i, CorrectArr[a][1] = j;
                a++;
                if(count >= 4) return 1;
            }
            else
            {
                count = 0;
                InitialArr(&a);
            }
        }
        count = 0;
        InitialArr(&a);
    }
    // 세로로 배열 확인
    count = 0;
    for(int i = 1; i < 8;i++)
    {
        for(int j = 0; j < 6; j++)
        {
            if(data[j][i] == '@')
            {
                count++;
                CorrectArr[a][0] = j, CorrectArr[a][1] = i;
                a++;
                if(count >= 4) return 1;
            }
            else
            {
                count = 0;
                InitialArr(&a);
            }
        }
        count = 0;
        InitialArr(&a);
    }
    // 대각선으로 배열 확인
    count = 0;
    int spin1, spin2;
    // 왼쪽 계단
    for(int j = 0; j < 6; j++)
    {
        spin1 = j;
        for(int i = 1; i < 7; i++)
        {
            if(data[spin1][i] == '@')
            {
                count++;
                CorrectArr[a][0] = spin1, CorrectArr[a][1] = i;
                a++;
                if(count >= 4) return 1;
            }
            else
            {
                count = 0;
                InitialArr(&a);
            }
            spin1++;
            if(spin1 > 5) break;
        }
        count = 0;
        InitialArr(&a);
    }
    count = 0;
    // 왼쪽 역계단
    for(int j = 5; j >= 0; j--)
    {
        spin1 = j;
        for(int i = 1; i < 7; i++)
        {
            if(data[spin1][i] == '@')
            {
                count++;
                CorrectArr[a][0] = spin1, CorrectArr[a][1] = i;
                a++;
                if(count >= 4) return 1;
            }
            else
            {
                count = 0;
                InitialArr(&a);
            }
            spin1--;
            if(spin1 < 0) break;
        }
        count = 0;
        InitialArr(&a);
    }
    count = 0;
    // 오른쪽 역계단
    for(int j = 5; j >= 0; j--)
    {
        spin2 = j;
        for(int i = 7; i > 1; i--)
        {
            if(data[spin2][i] == '@')
            {
                count++;
                CorrectArr[a][0] = spin2, CorrectArr[a][1] = i;
                a++;
                if(count >= 4) return 1;
            }
            else
            {
                count = 0;
                InitialArr(&a);
            }
            spin2--;
            if(spin2 < 0) break;
        }
        count = 0;
        InitialArr(&a);
    }
    count = 0;
    // 오른쪽 계단
    for(int j = 0; j < 6; j++)
    {
        spin2 = j;
        for(int i = 7; i > 1; i--)
        {
            if(data[spin2][i] == '@')
            {
                count++;
                CorrectArr[a][0] = spin2, CorrectArr[a][1] = i;
                a++;
                if(count >= 4) return 1;
            }
            else
            {
                count = 0;
                InitialArr(&a);
            }
            spin2++;
            if(spin2 > 5) break;
        }
        count = 0;
        InitialArr(&a);
    }
    return 0;
}

void Intro()
{
    printf(" ==============================================================================\n\n");
    for(int line = 0; line < 5; line++)
    {
        // 16 칸
        printf("                ");
        SpellCheck1(line);
        printf("\n");
    }
    printf("\n");
    for(int line = 0; line < 5; line++)
    {
        // 24 칸 띄우기
        printf("                        ");
        SpellCheck2(line);
        printf("\n");
    }
    printf("\n ==============================================================================\n");
    printf("                1 Player                                2 Player\n\n");
    printf("       a : ← , s : 놓기 , d : →              j : ← , k : 놓기 , k : →\n\n");
    printf("          (s : 1 인용 게임, n : 2 인용 게임)\n\n");
    printf("          (s / n) 키를 입력해서 게임을 시작하시오 : ");
    while(1)
    {
        char ch = getch();
        if(ch == 'n' || ch == 'N')
        {
            printf("%c\n\n", ch);
            printf("          GameStarting.");
            Sleep(1000);
            printf(".");
            Sleep(500);
            printf(".");
            Sleep(500);
            break;
        }
        if(ch == 's' || ch == 'S')
        {
            Duo = 0;
            printf("%c\n\n", ch);
            printf("          GameStarting.");
            Sleep(1000);
            printf(".");
            Sleep(500);
            printf(".");
            Sleep(500);
            break;
        }
    }
}

void DigitalPrint(int dim[], int line)
{
    for(int i= line*3 ; i <= line*3 + 2; i++)
    {
        if(dim[i] == 1) printf("■");
        else printf("  ");
    }
    printf("  ");
}

void SpellCheck1(int line)
{
    DigitalPrint(Spell_F, line);
    DigitalPrint(Spell_o, line);
    DigitalPrint(Spell_u, line);
    DigitalPrint(Spell_r, line);
    printf("  ");
    DigitalPrint(Spell_i, line);
    DigitalPrint(Spell_n, line);
    
}

void SpellCheck2(int line)
{
    DigitalPrint(Spell_a, line);
    printf("  ");
    DigitalPrint(Spell_R, line);
    DigitalPrint(Spell_o, line);
    DigitalPrint(Spell_w, line);
}