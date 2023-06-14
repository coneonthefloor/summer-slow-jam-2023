//
// Created by brian on 14/06/2023.
//

#ifndef SUMMERSLOWJAM2023_BALL_H
#define SUMMERSLOWJAM2023_BALL_H

#include <raylib.h>

typedef struct Ball {
    float Speed;
    float Radius;
    Vector2 Position;
    Vector2 Velocity;
} Ball;

Ball ball_create();
void ball_draw(Ball* ball);
void ball_update(Ball* ball);
bool ball_out_to_left(Ball *ball);
bool ball_out_to_right(Ball *ball);

#endif //SUMMERSLOWJAM2023_BALL_H
