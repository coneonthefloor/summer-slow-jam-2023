#include <stdio.h>

#include "main.h"

void Update(GameData *data) {
    paddle_update(&data->RightPaddle);
    paddle_update(&data->LeftPaddle);
    ball_update(&data->Ball);
}

void Draw(GameData *data) {
    BeginDrawing();

    ClearBackground(BLACK);

    paddle_draw(&data->RightPaddle);
    paddle_draw(&data->LeftPaddle);
    ball_draw(&data->Ball);

    EndDrawing();
}

GameData init() {
    GameData data;

    data.Ball = ball_create();
    data.LeftPaddle = paddle_create();
    data.RightPaddle = paddle_create();

    Vector2 left_paddle_pos = paddle_initial_left_position(&data.LeftPaddle);
    Vector2 right_paddle_pos = paddle_initial_right_position(&data.RightPaddle);

    data.LeftPaddle.Position = left_paddle_pos;
    data.RightPaddle.Position = right_paddle_pos;

    return data;
}

int main(void) {
    const int screenWidth = 600;
    const int screenHeight = 600;
    const char title[] = "SummerSlowJams2023";

    InitWindow(screenWidth, screenHeight, title);

    SetTargetFPS(60);

    GameData data = init();

    while (!WindowShouldClose()) {
        Update(&data);
        Draw(&data);
    }

    CloseWindow();
    return 0;
}
