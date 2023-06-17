//
// Created by brian on 14/06/2023.
//

#ifndef SUMMERSLOWJAM2023_BALL_H
#define SUMMERSLOWJAM2023_BALL_H

#include <raylib.h>
#include "paddle.h"

typedef struct Ball {
    bool Active;
    float Speed;
    float Radius;
    Vector2 Position;
    Vector2 Velocity;
} Ball;

Ball ball_create(AABB *bounds);
void ball_draw(Ball* ball);
void ball_update(Ball* ball, AABB *bounds);
bool ball_out_to_left(Ball *ball, AABB  *bounds);
bool ball_out_to_right(Ball *ball, AABB  *bounds);
bool ball_hits_paddle(Ball *ball, Paddle *paddle);
void ball_set_default_values(Ball *ball, AABB *bounds);

#endif //SUMMERSLOWJAM2023_BALL_H
