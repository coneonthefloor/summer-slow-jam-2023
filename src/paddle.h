//
// Created by brian on 14/06/2023.
//

#ifndef SUMMERSLOWJAM2023_PADDLE_H
#define SUMMERSLOWJAM2023_PADDLE_H

#include <raylib.h>

typedef struct Paddle {
    int Score;
    int Width;
    int Height;
    float Speed;
    Vector2 Position;
    Vector2 Velocity;
} Paddle;

Paddle paddle_create();
void paddle_draw(Paddle *paddle);
void paddle_update(Paddle *paddle);
Vector2 paddle_initial_left_position(Paddle *paddle);
Vector2 paddle_initial_right_position(Paddle *paddle);

#endif //SUMMERSLOWJAM2023_PADDLE_H
