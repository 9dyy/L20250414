#include <iostream>
#include <Windows.h>

#define MAPLENGTH 10
#define WALL '#'
#define SPACE ' '

using namespace std;

struct Player
{
    int xPos = 1;
    int yPos = 1;
    char playerMesh = 'P';
};

bool Input(Player* player);
void Tick(Player* player);
void Render(Player* player);

char Map[MAPLENGTH][MAPLENGTH] = {};
char RenderMap[MAPLENGTH][MAPLENGTH] = {};

int main()
{
    // Wall init
    for (int i = 0;i < MAPLENGTH; i++)
    {
        for (int j = 0; j < MAPLENGTH; j++)
        {
            if (i == 0 || j == 0 || i == MAPLENGTH - 1 || j == MAPLENGTH - 1)
            {
                Map[j][i] = WALL;
            }
            else
            {
                Map[j][i] = SPACE;
            }
        }
    }
    Player* player1 = new Player;

    bool IsRunning = true;
    while (IsRunning)
    {
        IsRunning = Input(player1);
        Tick(player1);
        Render(player1);
    }

    return 0;
}

bool Input(Player* player)
{
    if (GetAsyncKeyState((unsigned short)'Q') & 0x8000)
    {
        return false;
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        if (Map[player->xPos][player->yPos - 1] != WALL)
        {
            player->yPos--;
        }
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        if(Map[player->xPos][player->yPos + 1] != WALL)
        {
            player->yPos++;
        }
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        if(Map[player->xPos - 1][player->yPos] != WALL)
        {
            player->xPos--;
        }
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        if(Map[player->xPos + 1][player->yPos] != WALL)
        {
            player->xPos++;
        }
    }
    return true;
}

void Tick(Player* player)
{
    for (int i = 0;i < MAPLENGTH; i++)
    {
        for (int j = 0; j < MAPLENGTH; j++)
        {
            RenderMap[j][i] = Map[j][i];
        }
    }
    RenderMap[player->xPos][player->yPos] = player->playerMesh;
}

void Render(Player* player)
{
    system("cls");
    for (int i = 0;i < MAPLENGTH; i++)
    {
        for (int j = 0; j < MAPLENGTH; j++)
        {
            cout << RenderMap[j][i];
        }
        cout << "\n";
    }
    cout << "Exit : Q\n";
    Sleep(5);
}
