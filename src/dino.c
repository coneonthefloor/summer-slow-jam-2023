//
// Created by brian on 18/06/2023.
//

#include "dino.h"
#include "aabb.h"

const int IdleFrames = 4;
const int IdleOffset = 0;

const int RunningFrames = 6;
const int RunningOffset = 4;

void dino_set_idle_animation(Dino *dino) {
    dino->IsIdle = true;
    dino->IsJumping = false;
    dino->IsRunning = false;

    dino->FrameOffset = IdleOffset;
    dino->CurrentAnimationFrames = IdleFrames;
}

void dino_set_running_animation(Dino *dino) {
    dino->IsIdle = false;
    dino->IsJumping = false;
    dino->IsRunning = true;

    dino->FrameOffset = RunningOffset;
    dino->CurrentAnimationFrames = RunningFrames;
}


Dino dino_create(Texture2D *texture, Vector2 pos) {
    Dino dino;

    dino.Speed = 1;
    dino.Texture = *texture;

    dino.FrameSpeed = 8;
    dino.CurrentFrame = 0;
    dino.FramesCounter = 0;

    int spriteFrames = 24;
    dino.Width = (float) texture->width / (float) spriteFrames;
    dino.Height = (float) texture->height;

    Rectangle frameRec = {0.0f, 0.0f, dino.Width, dino.Height};
    dino.FrameRec = frameRec;

    dino.IsGrounded = true;

    dino_set_idle_animation(&dino);

    Vector2 vel = {0, 0};

    dino.Position = pos;
    dino.Velocity = vel;

    return dino;
}

void dino_update(Dino *dino, AABB *bounds) {
    dino->Position.x += dino->Velocity.x;
    dino->Position.y += dino->Velocity.y;

    if (dino->Position.x + dino->Width * 2 < bounds->Position.x) {
        dino->Velocity.x = dino->Speed;
    }

    if (dino->Position.x - dino->Width * 2 > bounds->Width) {
        dino->Velocity.x = -dino->Speed;
    }

    if (dino->Position.y - dino->Height > bounds->Height) {
        dino->Position.y = bounds->Height - dino->Height;
    }

    // Animation
    dino->FramesCounter++;

    if (dino->FramesCounter >= (60 / dino->FrameSpeed)) {
        dino->FramesCounter = 0;
        dino->CurrentFrame++;

        if (dino->CurrentFrame >
            dino->FrameOffset + dino->CurrentAnimationFrames) {
            dino->CurrentFrame = dino->FrameOffset;
        }

        dino->FrameRec.x = (float) dino->CurrentFrame * (float) dino->Width;
    }

    if (dino->Velocity.x != 0 && !dino->IsRunning && dino->IsGrounded) {
        dino_set_running_animation(dino);
    }

    if (dino->Velocity.x == 0 && !dino->IsIdle && dino->IsGrounded) {
        dino_set_idle_animation(dino);
    }

    if (dino->Velocity.x < 0) {
        dino->FrameRec.width = -dino->Width;
    }

    if (dino->Velocity.x > 0) {
        dino->FrameRec.width = dino->Width;
    }
}

void dino_draw(Dino *dino) {
    Rectangle destRec = {dino->Position.x, dino->Position.y, dino->Width * 2.0f,
                         dino->Height * 2.0f};
    Vector2 origin = {(float) dino->FrameRec.width,
                      (float) dino->FrameRec.height};
    DrawTexturePro(dino->Texture, dino->FrameRec, destRec, origin, 0, WHITE);
//    DrawTextureRec(dino->Texture, dino->FrameRec, dino->Position, WHITE);
}