//
// Created by brian on 14/06/2023.
//

#ifndef SUMMERSLOWJAM2023_MAIN_H
#define SUMMERSLOWJAM2023_MAIN_H

#include <raylib.h>
#include "ball.h"
#include "paddle.h"
#include "aabb.h"
#include "dino.h"
#include "text.h"

typedef struct GameData {
    int Gold;
    Ball Ball;
    AABB PongBounds;
    Paddle LeftPaddle;
    Paddle RightPaddle;
} GameData;

void Draw(GameData* data);
void Update(GameData* data);

#endif //SUMMERSLOWJAM2023_MAIN_H
