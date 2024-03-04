/*   헤더 파일   */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

/*    함수     */

//
void InitialArr(int *a);
void InitialData();
void PlayerMoveAction();
void DrawMap();
void CorrectDrawMap();
int ReStart();
int ArrayCheck1();
int ArrayCheck2();
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
    printf("\n             GG Good Game..\n");
    Sleep(1000);
    return 0;
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
                CorrectArr[a][0] = i, CorrectArr[a][1] = j; // 정답 위치 순서쌍 저장
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
    printf("================================================================================\n");
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
    printf("\n================================================================================\n");
    printf("                1 Player                                2 Player\n\n");
    printf("       a : ← , s : 놓기 , d : →              j : ← , k : 놓기 , l : →\n\n");

    printf("       (n / N) 키를 입력해서 게임을 시작하시오 : ");
    while(1)
    {
        char ch = getch();
        if(ch == 'n' || ch == 'N')
        {
            printf("%c\n\n", ch);
            printf("       GameStarting.");
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