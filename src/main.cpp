#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(500, 620, "raylib Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/monogram.tif", 64, 0, 0);

    Game game = Game();

    while (!WindowShouldClose())
    {
        UpdateMusicStream(game.music);
        game.HandleInput();
        float dropInterval = 0.25f;
        if (EventTriggered(dropInterval)) 
        {
            game.MoveBlockDown();
        }

        BeginDrawing();
        ClearBackground(BLACK);
        
        // Draw the normal game UI
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);
        
        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
        
        game.Draw();
        
        // Game over popup
        if (game.gameOver)
{
    // กำหนดขนาด Popup
    float popupWidth = 360;
    float popupHeight = 280;
    
    // คำนวณตำแหน่งให้อยู่กลางจอ
    Rectangle popupRect = {
        (GetScreenWidth() - popupWidth) / 2,
        (GetScreenHeight() - popupHeight) / 2,
        popupWidth,
        popupHeight
    };

    // วาดพื้นหลัง Popup
    DrawRectangleRounded(popupRect, 0.3, 6, BLACK);
    DrawRectangleRoundedLinesEx(popupRect, 0.3, 6, 3, WHITE);

    // ข้อความ "GAME OVER"
    const char* gameOverText = "GAME OVER";
    Vector2 gameOverSize = MeasureTextEx(font, gameOverText, 42, 2);
    DrawTextEx(font, gameOverText,
        (Vector2){
            popupRect.x + 20, // ระยะห่างจากขอบซ้าย 20 พิกเซล
            popupRect.y + 40  // ระยะห่างจากขอบบน 40 พิกเซล
        },
        42, 2, GREEN);

    // ข้อความคะแนน
    char scoreText[20];
    sprintf(scoreText, "Score: %d", game.score);
    Vector2 scoreSize = MeasureTextEx(font, scoreText, 34, 2);
    DrawTextEx(font, scoreText,
        (Vector2){
            popupRect.x + 20, // ระยะห่างจากขอบซ้ายเท่ากัน
            popupRect.y + 100 // ระยะห่างจากขอบบนมากขึ้น
        },
        34, 2, PURPLE);

    // ข้อความ restart
    const char* restartText = "Press Enter to Restart";
    Vector2 restartSize = MeasureTextEx(font, restartText, 28, 2);
    DrawTextEx(font, restartText,
        (Vector2){
            popupRect.x + 20, // ระยะห่างจากขอบซ้ายเท่ากัน
            popupRect.y + 160 // ระยะห่างจากขอบบนมากขึ้นอีก
        },
        28, 2, BLUE);
}
        EndDrawing();
    }
    CloseWindow();
    return 0;
}