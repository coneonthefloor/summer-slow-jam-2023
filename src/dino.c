//
// Created by brian on 18/06/2023.
//

#include "dino.h"
#include "aabb.h"

Dino dino_create(Texture2D *texture) {
    Dino dino;

    dino.Speed = 4;
    dino.IsGrounded = true;
    dino.Texture = *texture;

    dino.Width = (float) texture->width;
    dino.Height = (float) texture->height;

    Vector2 pos = {0, 0};
    Vector2 vel = {0, 0};

    dino.Position = pos;
    dino.Velocity = vel;

    return dino;
}

void dino_update(Dino *dino, AABB *bounds) {
//    dino->Position.x += dino->Velocity.x;
//    dino->Position.y += dino->Velocity.y;

//    if (dino->Position.x - dino->Width / 2 < bounds->Position.x) {
//        dino->Velocity.x = dino->Speed;
//    }
//
//    if (dino->Position.x + dino->Width / 2 > bounds->Width) {
//        dino->Velocity.x = dino->Speed;
//    }
//
//    if (dino->Position.y - dino->Height > bounds->Height) {
//        dino->Position.y = bounds->Height - dino->Height;
//    }
}

void dino_draw(Dino *dino) {
    DrawTexture(dino->Texture,
                (int) dino->Position.x,
                (int) dino->Position.y,
                WHITE);
}