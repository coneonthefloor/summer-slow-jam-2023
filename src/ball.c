//
// Created by brian on 14/06/2023.
//

#include "ball.h"
#include "paddle.h"

const float INITIAL_BALL_SPEED = 4.0f;
const float INITIAL_BALL_RADIUS = 10.0f;

void ball_set_default_values(Ball *ball, AABB *bounds) {
    ball->Active = true;
    ball->Speed = INITIAL_BALL_SPEED;
    ball->Radius = INITIAL_BALL_RADIUS;

    float initialX = bounds->Width / 2;
    float initialY = bounds->Height / 2;

    Vector2 position = {.x = initialX, .y = initialY};
    Vector2 velocity = {.x = -ball->Speed, .y = ball->Speed / 2};

    ball->Position = position;
    ball->Velocity = velocity;
}

Ball ball_create(AABB *bounds) {
    Ball ball;

    ball_set_default_values(&ball, bounds);

    return ball;
}

void ball_update(Ball *ball, AABB *bounds) {
    if (!ball->Active) {
        return;
    }

    ball->Position.x += ball->Velocity.x;
    ball->Position.y += ball->Velocity.y;

    if (ball->Position.y - ball->Radius < 0) {
        ball->Velocity.y = ball->Speed;
    }

    if (ball->Position.y + ball->Radius > bounds->Height) {
        ball->Velocity.y = -ball->Speed;
    }
}

void ball_draw(Ball *ball) {
    DrawCircle((int) ball->Position.x, (int) ball->Position.y,
               ball->Radius, WHITE);
}

bool ball_out_to_right(Ball *ball, AABB *bounds) {
    return ball->Position.x - ball->Radius > bounds->Width;
}

bool ball_out_to_left(Ball *ball, AABB *bounds) {
    return ball->Position.x + ball->Radius < bounds->Position.x;
}

bool ball_hits_paddle(Ball *ball, Paddle *paddle) {
    Rectangle paddleBounds = {.x = paddle->Position.x +
                                   (float) paddle->Width, .y = paddle->Position.y,
            .width = (float) paddle->Width, .height = (float) paddle->Height};
    Rectangle ballBounds = {.x = ball->Position.x, .y = ball->Position.y, .width =
    ball->Radius * 2, .height = ball->Radius * 2};

    return CheckCollisionRecs(paddleBounds, ballBounds);
}
