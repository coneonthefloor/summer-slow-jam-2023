//
// Created by brian on 18/06/2023.
//

#ifndef SUMMERSLOWJAM2023_DINO_H
#define SUMMERSLOWJAM2023_DINO_H

#include <raylib.h>
#include "aabb.h"

typedef struct Dino {
    float Speed;
    float Width;
    float Height;
    bool IsGrounded;
    Vector2 Velocity;
    Vector2 Position;
    Texture2D Texture;
} Dino;

void dino_draw(Dino *dino);
Dino dino_create(Texture2D *texture);
void dino_update(Dino *dino, AABB *bounds);

#endif //SUMMERSLOWJAM2023_DINO_H
