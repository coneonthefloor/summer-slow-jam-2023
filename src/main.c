#include <stdio.h>
#include <stdlib.h>

#include "main.h"

void drawGoldCount(int goldCount, AABB *bounds) {
    int textPad = 10;
    int fontSize = 20;

    const char *gold = TextFormat("$ %d", goldCount);
    int goldTextSize = MeasureText(gold, fontSize);
    DrawText(gold, (int) (bounds->Width / 2) - goldTextSize / 2,
             textPad, fontSize, LIGHTGRAY);
}

void Update(GameData *data) {
    paddle_update(&data->RightPaddle, &data->PongBounds);
    paddle_update(&data->LeftPaddle, &data->PongBounds);
    ball_update(&data->Ball, &data->PongBounds);

    if (ball_out_to_left(&data->Ball, &data->PongBounds)) {
        data->RightPaddle.Score++;
        data->Ball.Active = false;
    }

    if (ball_out_to_right(&data->Ball, &data->PongBounds)) {
        data->LeftPaddle.Score++;
        data->Ball.Active = false;
    }

    if (data->Ball.Active) {
        if (data->Ball.Velocity.x > 0) {
            paddle_move_to_center(&data->LeftPaddle, &data->PongBounds);
            paddle_chase_ball(&data->RightPaddle, &data->Ball);
        }

        if (data->Ball.Velocity.x < 0) {
            paddle_move_to_center(&data->RightPaddle, &data->PongBounds);
            paddle_chase_ball(&data->LeftPaddle, &data->Ball);
        }

        if (ball_hits_paddle(&data->Ball, &data->LeftPaddle)) {
            data->Gold++;
            data->Ball.Velocity.x = data->Ball.Speed;
            data->Ball.Velocity.y = (float) GetRandomValue(
                    (int) data->Ball.Speed / 2,
                    (int) data->Ball.Speed);
        }

        if (ball_hits_paddle(&data->Ball, &data->RightPaddle)) {
            data->Gold++;
            data->Ball.Velocity.x = -data->Ball.Speed;
            data->Ball.Velocity.y = (float) GetRandomValue(
                    (int) data->Ball.Speed / 2,
                    (int) data->Ball.Speed);
        }
    }

    if (!data->Ball.Active) {
        ball_set_default_values(&data->Ball, &data->PongBounds);
    }

    for (int i = 0; i < data->DinoCount; i++) {
        dino_update(&data->Dinos[i], &data->PongBounds);
    }
}

void Draw(GameData *data) {
    BeginDrawing();

    ClearBackground(BLACK);

    aabb_draw(&data->PongBounds);
    drawGoldCount(data->Gold, &data->PongBounds);
    paddle_draw(&data->RightPaddle);
    paddle_draw(&data->LeftPaddle);
    ball_draw(&data->Ball);

    for (int i = 0; i < data->DinoCount; i++) {
        dino_draw(&data->Dinos[i]);
    }

    EndDrawing();
}

Texture2D getTextureFromImageFile(const char *fileName) {
    Image image = LoadImage(fileName);
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);

    return texture;
}

GameData init() {
    GameData data;

    data.Gold = 0;
    Vector2 pongBoundsPosition = {.x = 0, .y = 0};
    data.PongBounds = aabb_create((float) GetScreenWidth(), 480.0f,
                                  pongBoundsPosition);

    data.LeftPaddle = paddle_create();
    data.RightPaddle = paddle_create();
    data.Ball = ball_create(&data.PongBounds);

    Vector2 left_paddle_pos = paddle_initial_left_position(&data.LeftPaddle,
                                                           &data.PongBounds);
    Vector2 right_paddle_pos = paddle_initial_right_position(&data.RightPaddle,
                                                             &data.PongBounds);

    data.LeftPaddle.Position = left_paddle_pos;
    data.RightPaddle.Position = right_paddle_pos;

    return data;
}

int main(void) {
    const int screenWidth = 640;
    const int screenHeight = 800;
    const char title[] = "SummerSlowJams2023";

    InitWindow(screenWidth, screenHeight, title);

    SetTargetFPS(60);

    GameData data = init();

    Texture2D pardTexture = getTextureFromImageFile(ASSETS_PATH"/pard.png");
    Texture2D vitaTexture = getTextureFromImageFile(ASSETS_PATH"/vita.png");
    Texture2D douxTexture = getTextureFromImageFile(ASSETS_PATH"/doux.png");
    Texture2D mortTexture = getTextureFromImageFile(ASSETS_PATH"/mort.png");

    float floor = data.PongBounds.Height - (float) pardTexture.height;
    Dino pard = dino_create(&pardTexture, (Vector2) {
            (float) GetRandomValue((int) data.PongBounds.Position.x,
                                   (int) data.PongBounds.Width),
            floor});
    Dino vita = dino_create(&vitaTexture, (Vector2) {
            (float) GetRandomValue((int) data.PongBounds.Position.x,
                                   (int) data.PongBounds.Width),
            floor});
    Dino doux = dino_create(&douxTexture, (Vector2) {
            (float) GetRandomValue((int) data.PongBounds.Position.x,
                                   (int) data.PongBounds.Width),
            floor});
    Dino mort = dino_create(&mortTexture, (Vector2) {
            (float) GetRandomValue((int) data.PongBounds.Position.x,
                                   (int) data.PongBounds.Width),
            floor});

    pard.Speed = 1;
    pard.Velocity.x = GetRandomValue(0, 1) ? pard.Speed : -pard.Speed;
    doux.Speed = 1.5f;
    doux.Velocity.x = GetRandomValue(0, 1) ? doux.Speed : -doux.Speed;
    vita.Speed = 3;
    vita.Velocity.x = GetRandomValue(0, 1) ? vita.Speed : -vita.Speed;
    mort.Speed = 2;
    mort.Velocity.x = GetRandomValue(0, 1) ? mort.Speed : -mort.Speed;

    data.Dinos[0] = pard;
    data.Dinos[1] = vita;
    data.Dinos[2] = doux;
    data.Dinos[3] = mort;

    data.DinoCount = 4;

    while (!WindowShouldClose()) {
        Update(&data);
        Draw(&data);
    }

    UnloadTexture(pardTexture);
    UnloadTexture(vitaTexture);
    UnloadTexture(douxTexture);
    UnloadTexture(mortTexture);
    CloseWindow();
    return 0;
}
