#include <stdio.h>
#include <stdlib.h>

#include "main.h"

void buy_dino(Dino *dino, int cost, GameData *data) {
    data->Gold = data->Gold - cost;
    Vector2 pos = {data->PongBounds.Width / 2,
                   data->PongBounds.Height - dino->Texture.height};
    Dino newDino = dino_create(&dino->Texture, pos);
    newDino.Velocity = (Vector2) {
            GetRandomValue(0, 1) ? dino->Speed : -dino->Speed, 0};
    data->Dinos[data->DinoCount] = newDino;
    data->DinoCount += 1;
}

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
            data->Gold += 400;
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

    if (data->DinoCount > 0) {
        for (int i = 0; i < data->DinoCount; i++) {
            dino_update(&data->Dinos[i], &data->PongBounds);
        }
    }
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

    data.DinoCount = 0;

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
    Dino pard = dino_create(&pardTexture, (Vector2) {0, 0});
    Dino vita = dino_create(&vitaTexture, (Vector2) {0, 0});
    Dino doux = dino_create(&douxTexture, (Vector2) {0, 0});
    Dino mort = dino_create(&mortTexture, (Vector2) {0, 0});

    pard.Speed = .5f;
    doux.Speed = 1.5f;
    vita.Speed = 2;
    mort.Speed = 1;

    int pardCost = 5;
    int douxCost = 6;
    int mortCost = 7;
    int vitaCost = 8;

    int defaultOutline = 8;
    int redLineThickness = defaultOutline;
    int blueLineThickness = defaultOutline;
    int greenLineThickness = defaultOutline;
    int yellowLineThickness = defaultOutline;

    Vector2 mousePoint = {0.0f, 0.0f};

    float xPad = 10.0f;
    float yPad = 20.0f;
    float btnHeight = 132.0f;
    float btnWidth = data.PongBounds.Width / 2 - xPad * 2;
    Rectangle redBtnRec = {xPad, data.PongBounds.Height + yPad, btnWidth,
                           btnHeight};
    Rectangle yellowBtnRec = {xPad * 3 + btnWidth,
                              data.PongBounds.Height + yPad,
                              btnWidth, btnHeight};
    Rectangle greenBtnRec = {xPad * 3 + btnWidth,
                             data.PongBounds.Height + yPad * 2 + btnHeight,
                             btnWidth,
                             btnHeight};
    Rectangle blueBtnRec = {xPad, data.PongBounds.Height + yPad * 2 + btnHeight,
                            btnWidth,
                            btnHeight};

    while (!WindowShouldClose()) {
        mousePoint = GetMousePosition();

        if (CheckCollisionPointRec(mousePoint, redBtnRec)) {
            redLineThickness = defaultOutline * 1.5f;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) &&
                data.Gold >= mortCost) {
                buy_dino(&mort, mortCost, &data);
            }
        } else {
            redLineThickness = defaultOutline;
        }

        if (CheckCollisionPointRec(mousePoint, yellowBtnRec)) {
            yellowLineThickness = defaultOutline * 1.5f;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) &&
                data.Gold >= pardCost) {
                buy_dino(&pard, pardCost, &data);
            }
        } else {
            yellowLineThickness = defaultOutline;
        }

        if (CheckCollisionPointRec(mousePoint, greenBtnRec)) {
            greenLineThickness = defaultOutline * 1.5f;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) &&
                data.Gold >= vitaCost) {
                buy_dino(&vita, vitaCost, &data);
            }
        } else {
            greenLineThickness = defaultOutline;
        }

        if (CheckCollisionPointRec(mousePoint, blueBtnRec)) {
            blueLineThickness = defaultOutline * 1.5f;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) &&
                data.Gold >= douxCost) {
                buy_dino(&doux, douxCost, &data);
            }
        } else {
            blueLineThickness = defaultOutline;
        }

        Update(&data);


        BeginDrawing();

        ClearBackground(BLACK);

        aabb_draw(&data.PongBounds);
        drawGoldCount(data.Gold, &data.PongBounds);
        paddle_draw(&data.RightPaddle);
        paddle_draw(&data.LeftPaddle);
        ball_draw(&data.Ball);

        if (data.DinoCount > 0) {
            for (int i = 0; i < data.DinoCount; i++) {
                dino_draw(&data.Dinos[i]);
            }
        }

        DrawRectangle(redBtnRec.x, redBtnRec.y, redBtnRec.width,
                      redBtnRec.height, RED);
        DrawRectangleLinesEx(redBtnRec, redLineThickness, MAROON);
        DrawRectangle(yellowBtnRec.x, yellowBtnRec.y, yellowBtnRec.width,
                      yellowBtnRec.height, YELLOW);
        DrawRectangleLinesEx(yellowBtnRec, yellowLineThickness, ORANGE);
        DrawRectangle(greenBtnRec.x, greenBtnRec.y, greenBtnRec.width,
                      greenBtnRec.height, GREEN);
        DrawRectangleLinesEx(greenBtnRec, greenLineThickness, DARKGREEN);
        DrawRectangle(blueBtnRec.x, blueBtnRec.y, blueBtnRec.width,
                      blueBtnRec.height, BLUE);
        DrawRectangleLinesEx(blueBtnRec, blueLineThickness, DARKBLUE);

        EndDrawing();
    }

    UnloadTexture(pardTexture);
    UnloadTexture(vitaTexture);
    UnloadTexture(douxTexture);
    UnloadTexture(mortTexture);
    CloseWindow();
    return 0;
}
