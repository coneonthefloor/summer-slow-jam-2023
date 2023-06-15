#include <stdio.h>

#include "main.h"

void Update(GameData *data) {
    paddle_update(&data->RightPaddle);
    paddle_update(&data->LeftPaddle);
    ball_update(&data->Ball);

    if (ball_out_to_left(&data->Ball)) {
        data->RightPaddle.Score++;
        data->Ball.Active = false;
    }

    if (ball_out_to_right(&data->Ball)) {
        data->LeftPaddle.Score++;
        data->Ball.Active = false;
    }

    if (data->Ball.Active) {
        if (data->Ball.Velocity.x > 0) {
            paddle_move_to_center(&data->LeftPaddle);
            paddle_chase_ball(&data->RightPaddle, &data->Ball);
        }

        if (data->Ball.Velocity.x < 0) {
            paddle_move_to_center(&data->RightPaddle);
            paddle_chase_ball(&data->LeftPaddle, &data->Ball);
        }
    }

    if (!data->Ball.Active) {
        ball_set_default_values(&data->Ball);
    }
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
    const int screenWidth = 640;
    const int screenHeight = 480;
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
