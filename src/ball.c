//
// Created by brian on 14/06/2023.
//

#include "ball.h"

int INITIAL_BALL_SPEED = 5;
float INITIAL_BALL_RADIUS = 10.0f;

Ball ball_create() {
    Ball ball;

    ball.Speed = INITIAL_BALL_SPEED;
    ball.Radius = INITIAL_BALL_RADIUS;

    float initialY = (float) GetScreenWidth() / 2 - (float) ball.Radius;
    float initialX = (float) GetScreenHeight() / 2 - (float) ball.Radius;

    Vector2 position = {.x = initialX, .y = initialY};
    Vector2 velocity = {.x = 0, .y = 0};

    ball.Position = position;
    ball.Velocity = velocity;

    return ball;
}

void ball_update(Ball *ball) {
    ball->Position.x += ball->Velocity.x;
    ball->Position.y += ball->Velocity.y;
}

void ball_draw(Ball *ball) {
    DrawCircle((int) ball->Position.x, (int) ball->Position.y,
               ball->Radius, WHITE);
}