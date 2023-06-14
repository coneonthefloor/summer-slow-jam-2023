//
// Created by brian on 14/06/2023.
//

#include "paddle.h"

const int INITIAL_PADDLE_WIDTH = 10;
const int INITIAL_PADDLE_HEIGHT = 120;
const float INITIAL_PADDLE_SPEED = 50.0f;

Paddle paddle_create() {
    Paddle paddle;

    paddle.Score = 0;
    paddle.Width = INITIAL_PADDLE_WIDTH;
    paddle.Height = INITIAL_PADDLE_HEIGHT;
    paddle.Speed = INITIAL_PADDLE_SPEED;

    Vector2 position = {.x = 0, .y = 0};
    Vector2 velocity = {.x = 0, .y = 0};

    paddle.Position = position;
    paddle.Velocity = velocity;

    return paddle;
}

void paddle_update(Paddle *paddle) {
    paddle->Position.x += paddle->Velocity.x;
    paddle->Position.y += paddle->Velocity.y;

    float halfHeight = (float) paddle->Height / 2;
    float minY = halfHeight;
    float maxY = (float) GetScreenHeight() - halfHeight;

    if (paddle->Position.y < minY) {
        paddle->Position.y = minY;
    }

    if (paddle->Position.y > maxY) {
        paddle->Position.y = maxY;
    }
}

void paddle_draw(Paddle *paddle) {
    DrawRectangle((int) paddle->Position.x,
                  (int) paddle->Position.y,
                  paddle->Width, paddle->Height, WHITE);
}

Vector2 paddle_initial_left_position(Paddle *paddle) {
    Vector2 pos;
    float xOffset = 20.0f;
    pos.x = xOffset;
    pos.y = (float) GetScreenHeight() / 2 -
            (float) paddle->Height / 2;
    return pos;
}

Vector2 paddle_initial_right_position(Paddle *paddle) {
    Vector2 pos;
    float xOffset = 20.0f;
    pos.x = (float) GetScreenWidth() - xOffset - (float) paddle->Width;
    pos.y = (float) GetScreenHeight() / 2 -
            (float) paddle->Height / 2;
    return pos;
}