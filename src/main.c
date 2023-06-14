#include <stdio.h>

#include "main.h"

Ball BALL;

void Update() {
    // update game state
}

void Draw() {
    BeginDrawing();

    ClearBackground(BLACK);

    ball_draw(&BALL);

    EndDrawing();
}

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;
    const char title[] = "SummerSlowJams2023";

    InitWindow(screenWidth, screenHeight, title);

    SetTargetFPS(60);

    BALL = ball_create();
    Vector2 pos = {.x = GetScreenWidth() / 2, .y = GetScreenHeight() / 2};
    BALL.Position = pos;

    while (!WindowShouldClose()) {
        Update();
        Draw();
    }

    CloseWindow();
    return 0;
}
