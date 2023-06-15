//
// Created by brian on 14/06/2023.
//

#include "ball.h"

const float INITIAL_BALL_SPEED = 2.0f;
const float INITIAL_BALL_RADIUS = 10.0f;

void ball_set_default_values(Ball *ball) {
    ball->Active = true;
    ball->Speed = INITIAL_BALL_SPEED;
    ball->Radius = INITIAL_BALL_RADIUS;

    float initialX = (float) GetScreenWidth() / 2;
    float initialY = (float) GetScreenHeight() / 2;

    Vector2 position = {.x = initialX, .y = initialY};
    Vector2 velocity = {.x = -ball->Speed, .y = ball->Speed / 2};

    ball->Position = position;
    ball->Velocity = velocity;
}

Ball ball_create() {
    Ball ball;

    ball_set_default_values(&ball);

    return ball;
}

void ball_update(Ball *ball) {
    if(!ball->Active) {
        return;
    }

    ball->Position.x += ball->Velocity.x;
    ball->Position.y += ball->Velocity.y;

    if (ball->Position.y - ball->Radius < 0) {
        ball->Velocity.y = ball->Speed;
    }

    if (ball->Position.y + ball->Radius > (float) GetScreenHeight()) {
        ball->Velocity.y = -ball->Speed;
    }
}

void ball_draw(Ball *ball) {
    DrawCircle((int) ball->Position.x, (int) ball->Position.y,
               ball->Radius, WHITE);
}

bool ball_out_to_right(Ball *ball) {
    return ball->Position.x - ball->Radius > (float) GetScreenWidth();
}

bool ball_out_to_left(Ball *ball) {
    return ball->Position.x + ball->Radius < 0;
}
