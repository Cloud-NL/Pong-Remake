#include "raylib.h"
#include "functions.h"

typedef struct Screen
{
    int width;
    int height;
} Screen;

static Screen screen = {0};

int main(void)
{
    screen.width = 800;
    screen.height = 650;

    InitWindow(screen.width, screen.height, "Pong");
    game_initialize();
    SetTargetFPS(60);
    while (!WindowShouldClose())    
    {
        game_update();
    }
    CloseWindow();

    return 0;
}