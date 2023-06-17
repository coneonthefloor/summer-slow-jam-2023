//
// Created by brian on 17/06/2023.
//

#include "aabb.h"

AABB aabb_create(float width, float height, Vector2 pos) {
    AABB aabb;
    aabb.Width = width;
    aabb.Height = height;
    aabb.Position = pos;
    return aabb;
}

void aabb_draw(AABB *aabb) {
    float thickness = 5.0f;
    Rectangle rect = {aabb->Position.x, aabb->Position.y, aabb->Width,
                      aabb->Height + thickness};
    DrawRectangleLinesEx(rect, thickness, WHITE);
}