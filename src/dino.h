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
    bool IsIdle;
    bool IsJumping;
    bool IsRunning;
    bool IsGrounded;
    Vector2 Velocity;
    Vector2 Position;
    Texture2D Texture;
    int FrameSpeed;
    int FrameOffset;
    int CurrentFrame;
    int FramesCounter;
    int CurrentAnimationFrames;
    Rectangle FrameRec;
} Dino;

void dino_draw(Dino *dino);
void dino_update(Dino *dino, AABB *bounds);
Dino dino_create(Texture2D *texture, Vector2 pos);

#endif //SUMMERSLOWJAM2023_DINO_H
