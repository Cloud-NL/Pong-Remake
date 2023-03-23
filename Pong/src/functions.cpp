#include "functions.h"
#include "raylib.h"
#include <iostream>

typedef struct Player1
{
    Vector2 position;
    float width;
    float height;
    Color color;
    Texture2D texture;
    int points;
    int speed;
} Player1;

typedef struct Player2
{
    Vector2 position;
    float width;
    float height;
    Color color;
    Texture2D texture;
    int points;
    int speed;
} Player2;

typedef struct Screen
{
    int width;
    int height;
    bool started;
} Screen;

static Player1 player1 = {0};
static Player2 player2 = {0};
static Screen screen = {0};

class Ball {
    public: 
    float x, y;
    int speed_x, speed_y;
    int radius;
    Color color;

    void Draw() {
        DrawCircle(x, y, radius, color);
        // DrawText(("%i", GetScreenWidth()), GetScreenWidth() / 2, 30, 20, WHITE);
        // DrawText(("%i", GetScreenWidth()), GetScreenWidth() / 2, 30, 20, WHITE);
    }

    void Update() {
        x += speed_x;
        y += speed_y;

        if(y > 650 - 10)
        {
            speed_y *= -1;
        }else if(y <= 0 - 10)
        {
            speed_y *= -1;
        }
        if(x > 800 - 10)
        {
            player1.points++;
            Reset();
        } else if(x <= 0 - 10)
        {
            player2.points++;
            Reset();
        }

        if(CheckCollisionCircleRec(Vector2{x, y}, radius, Rectangle{player1.position.x, player1.position.y, 10, 150}))
        {
            // speed_x *= -1;
            int choice[2] = {-1, 1};
            speed_x *= - 1;
            speed_y *= choice[GetRandomValue(0, 1)];
        }

        if(CheckCollisionCircleRec(Vector2{x, y}, radius, Rectangle{player2.position.x, player2.position.y, 10, 150}))
        {
            int choice[2] = {-1, 1};
            speed_x *= - 1;
            speed_y *= choice[GetRandomValue(0, 1)];
        }
    }

    void Reset()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int choice[2] = {-1, 1};
        speed_x *= choice[GetRandomValue(0, 1)];
        speed_y *= choice[GetRandomValue(0, 1)];
    }
};

Ball ball;

void game_update(void) // Gelooped door main
{
    
    game_draw();
    game_input();
    game_collision();
}

void game_draw(void)
{
    BeginDrawing();
        if(!screen.started)
        {
            DrawText("Press [SPACE] to start game", screen.width / 2 - MeasureText("Press [SPACE] to start game", 20) / 2, screen.height / 2, 20, LIGHTGRAY);
            if(IsKeyDown(KEY_SPACE))
            {
                screen.started = true;
            }
        } else {
            ClearBackground(BLACK);
            ball.Update();
            DrawRectangle(player1.position.x, player1.position.y, player1.width, player1.height, player1.color);
            DrawRectangle(player2.position.x, player2.position.y, player2.width, player2.height, player2.color);
            DrawText(TextFormat("%i", player1.points), GetScreenWidth() / 2 - 200, 100, 30, WHITE);
            DrawText(TextFormat("%i", player2.points), GetScreenWidth() / 2 + 200, 100, 30, WHITE);
            ball.Draw();
        }
    EndDrawing();
}

void game_collision(void)
{
    if(player1.position.y > 650 - 150)
    {
        player1.position.y = 650 - 150;
    } else if(player1.position.y <= 0)
    {
        player1.position.y = 0;
    }

    if(player2.position.y > 650 - 150)
    {
        player2.position.y = 650 - 150;
    } else if(player2.position.y <= 0)
    {
        player2.position.y = 0;
    }
}

void game_initialize(void)
{
    player1.position.x = 50;
    player1.position.y = GetScreenHeight() / 2 - 75;
    player1.width = 10;
    player1.height = 150;
    player1.color = WHITE;
    player1.points = 0;
    player1.speed = 10;

    player2.position.x = 750;
    player2.position.y = GetScreenHeight() / 2 - 75;
    player2.width = 10;
    player2.height = 150;
    player2.color = WHITE;
    player2.points = 0;
    player2.speed = 10;

    ball.radius = 10.0;
    ball.color = WHITE;
    ball.speed_x = 7;
    ball.speed_y = 7;


    screen.height = 650;
    screen.width = 800;
}

void game_input(void) {
    if(IsKeyDown(KEY_W))
    {
        player1.position.y -= player1.speed;
    } else if(IsKeyDown(KEY_S))
    {
        player1.position.y += player1.speed;
    }
    if(IsKeyDown(KEY_UP))
    {
        player2.position.y -= player2.speed;
    } else if(IsKeyDown(KEY_DOWN))
    {
        player2.position.y += player2.speed;
    }
}