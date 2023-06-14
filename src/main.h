//
// Created by brian on 14/06/2023.
//

#ifndef SUMMERSLOWJAM2023_MAIN_H
#define SUMMERSLOWJAM2023_MAIN_H


#include <raylib.h>
#include "ball.h"
#include "paddle.h"

typedef struct GameData {
    Ball Ball;
    Paddle LeftPaddle;
    Paddle RightPaddle;
} GameData;

void Draw(GameData* data);
void Update(GameData* data);

#endif //SUMMERSLOWJAM2023_MAIN_H
