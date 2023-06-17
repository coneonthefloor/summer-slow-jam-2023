//
// Created by brian on 14/06/2023.
//

#ifndef SUMMERSLOWJAM2023_PADDLE_H
#define SUMMERSLOWJAM2023_PADDLE_H

#include <raylib.h>
#include "ball.h"
#include "aabb.h"

typedef struct Paddle {
    int Score;
    int Width;
    int Height;
    float Speed;
    Vector2 Position;
    Vector2 Velocity;
} Paddle;

typedef struct Ball Ball;

Paddle paddle_create();
void paddle_draw(Paddle *paddle);
void paddle_update(Paddle *paddle, AABB *bounds);
Vector2 paddle_initial_left_position(Paddle *paddle, AABB *bounds);
Vector2 paddle_initial_right_position(Paddle *paddle, AABB *bounds);
void paddle_chase_ball(Paddle *paddle, Ball *ball);
void paddle_move_to_center(Paddle *paddle, AABB *bounds);

#endif //SUMMERSLOWJAM2023_PADDLE_H
