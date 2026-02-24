#include <raylib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    InitWindow(1280, 720, "Testing v0.1");
    SetTargetFPS(60);
    InitAudioDevice();

    int PlayerX = GetScreenWidth() / 2, PlayerY = GetScreenHeight() / 2;
    bool IsTouchingBorder = false, IsWalking = false;

    Color SKIN = { 255, 224, 189, 255 };

    Sound Walking = LoadSound("assets/SFX/Walking.mp3");

    Texture2D Wall = LoadTexture("assets/texture/Wall.jpg");
    vector<vector<int>> Map = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1},
    {1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1},
    {1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1},
    {1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1},
    {1,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

    while(!WindowShouldClose()) {

        if (IsKeyDown(KEY_W) && !IsTouchingBorder) {
            PlayerY -= 2;
            IsWalking = true;
        }
        if (IsKeyDown(KEY_A) && !IsTouchingBorder) {
            PlayerX -= 2;
            IsWalking = true;
        } 
        if (IsKeyDown(KEY_S) && !IsTouchingBorder) {
            PlayerY += 2;
            IsWalking = true;
        } 
        if (IsKeyDown(KEY_D) && !IsTouchingBorder) {
            PlayerX += 2;
            IsWalking = true;
        } 

        if (IsKeyDown(KEY_LEFT_SHIFT) && !IsTouchingBorder) {
            if (IsKeyDown(KEY_W) && !IsTouchingBorder) PlayerY -= 5;
            if (IsKeyDown(KEY_A) && !IsTouchingBorder) PlayerX -= 5;
            if (IsKeyDown(KEY_S) && !IsTouchingBorder) PlayerY += 5;
            if (IsKeyDown(KEY_D) && !IsTouchingBorder) PlayerX += 5;
        }

        if (IsWalking) {
            PlaySound(Walking);
        } else {
            StopSound(Walking);
        }

        BeginDrawing();
        ClearBackground(WHITE);
        for (int y = 0; y < Map.size(); y++) {
            for (int x = 0; x < Map[y].size(); x++) {
                if (Map[y][x] == 1) {
                    DrawTexture(Wall, x * 75, y * 75, WHITE);
                }
            }
        }
        DrawCircle(PlayerX, PlayerY, 10, SKIN);
        DrawCircle(PlayerX, PlayerY + 30, 20, SKYBLUE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}