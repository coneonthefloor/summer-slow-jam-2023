//
// Created by brian on 17/06/2023.
//

#ifndef SUMMERSLOWJAM2023_AABB_H
#define SUMMERSLOWJAM2023_AABB_H

#include <raylib.h>

typedef struct AABB {
    float Width;
    float Height;
    Vector2 Position;
} AABB;

void aabb_draw(AABB *aabb);
AABB aabb_create(float width, float height, Vector2 pos);

#endif //SUMMERSLOWJAM2023_AABB_H
