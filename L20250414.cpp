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

enum EInputResult
{
    NONE,
    UP,
    DOWN,
    RIGHT,
    LEFT,
    QUIT,
};

EInputResult Input(Player* player);
void Tick(Player* player, EInputResult inputResult);
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
        EInputResult nowInput = Input(player1);
        if (nowInput == EInputResult::QUIT)
        {
            return 0;
        }
        Tick(player1, nowInput);
        Render(player1);
    }
    return 0;
}

EInputResult Input(Player* player)
{
    if (GetAsyncKeyState((unsigned short)'Q') & 0x8000)
    {
        return EInputResult::QUIT;
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        return EInputResult::UP;
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        return EInputResult::DOWN;
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        return EInputResult::LEFT;
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        return EInputResult::RIGHT;
    }
}

void Tick(Player* player, EInputResult inputResult)
{
    switch (inputResult)
    {
    case UP:
        if (Map[player->xPos][player->yPos - 1] != WALL)
        {
            player->yPos--;
        }
        break;
    case DOWN:
        if (Map[player->xPos][player->yPos + 1] != WALL)
        {
            player->yPos++;
        }
        break;
    case RIGHT:
        if (Map[player->xPos + 1][player->yPos] != WALL)
        {
            player->xPos++;
        }
        break;
    case LEFT:
        if (Map[player->xPos - 1][player->yPos] != WALL)
        {
            player->xPos--;
        }
        break;
    case QUIT:
        break;
    default:
        break;
    }

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
