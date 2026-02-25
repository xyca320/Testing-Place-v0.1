#include <raylib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    InitWindow(1280, 720, "Testing v0.1");
    SetExitKey(KEY_MINUS);
    SetTargetFPS(60);
    InitAudioDevice();

    int PlayerX = GetScreenWidth() / 2 - 80, PlayerY = GetScreenHeight() / 2;
    bool IsTouchingBorder = false, IsWalking = false, IsTryingToReset = false, IsTryingToFullScreen = false, InGame = false, InMenu = true, InSetting = false, InLogs = false;

    Color SKIN = { 255, 224, 189, 255 };

    Sound Walking = LoadSound("assets/SFX/Walking.mp3");

    Texture2D Wall = LoadTexture("assets/texture/Wall.jpg");
    Texture2D Door_Closed = LoadTexture("assets/texture/Door_Close.jpg");
    Texture2D Door_Opened = LoadTexture("assets/texture/Door_Open.jpg");
    Texture2D White_Car = LoadTexture("assets/texture/White_Car.png");

    Rectangle StartButtonHitbox = {GetScreenWidth() / 2.0f - 200 / 2.0f, GetScreenHeight() / 2.0f - (60 * 2 + 20) / 2.0f, 200, 60};
    Rectangle SettingButton = {GetScreenWidth() / 2 - 75, GetScreenHeight() / 2 - 37.5f, 200, 60};

    vector<vector<int>> Map = {
    {1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,101,1,1,0,0,2,0,0,1,100,1,1,1,0,0,0,2,0,0,0,1,1,1,0,0,0,0,1},
    {1,0,1,0,0,0,1,0,0,2,0,0,1,0,0,0,1,0,0,0,2,0,0,0,1,0,1,0,0,0,0,1},
    {1,0,1,0,0,0,1,0,0,2,0,0,1,0,0,0,1,0,0,0,2,0,0,0,1,0,1,0,0,0,0,1},
    {1,0,1,0,0,0,1,0,0,2,0,0,1,0,0,0,1,0,0,0,2,0,0,0,1,0,1,0,0,0,0,1},
    {1,0,1,1,1,1,1,0,0,2,0,0,1,1,1,1,1,0,0,0,2,0,0,0,1,1,1,0,0,0,0,1},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {1,0,1,1,101,1,1,1,1,1,1,1,101,1,1,1,1,1,1,1,1,1,1,1,1,1,1,101,1,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    /*
    1 - Brown Brick Wall
    100 - Door Closed
    101 - Door Opened
    */
    // BEFORE MAIN LOOP
    vector<Rectangle> Hitboxes;

    // Build hitboxes ONCE
    for (int y = 0; y < Map.size(); y++) {
        for (int x = 0; x < Map[y].size(); x++) {
            if (Map[y][x] == 1 || Map[y][x] == 100) {
                Hitboxes.push_back({ x * 75.0f, y * 75.0f, 75.0f, 75.0f });
            }
        }
    }

    while (!WindowShouldClose()) {
        Vector2 MousePos = GetMousePosition();

        bool IsWalking = false;  // RESET

        int OldPlayerX = PlayerX, OldPlayerY = PlayerY;

        if (InMenu && IsKeyPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointRec(MousePos, StartButtonHitbox) {
                InGame = true;
            }
        }

        // Movement
        if (IsKeyDown(KEY_W)) { PlayerY -= 2; IsWalking = true; }
        if (IsKeyDown(KEY_A)) { PlayerX -= 2; IsWalking = true; }
        if (IsKeyDown(KEY_S)) { PlayerY += 2; IsWalking = true; }
        if (IsKeyDown(KEY_D)) { PlayerX += 2; IsWalking = true; }

        Vector2 PlayerPos = { PlayerX, PlayerY };

        // Sprint
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            if (IsKeyDown(KEY_W)) PlayerY -= 4;
            if (IsKeyDown(KEY_A)) PlayerX -= 4;
            if (IsKeyDown(KEY_S)) PlayerY += 4;
            if (IsKeyDown(KEY_D)) PlayerX += 4;
        }

        // Collision
        bool IsTouchingBorder = false;
        for (auto &Hitbox : Hitboxes) {
            if (CheckCollisionCircleRec(PlayerPos, 20, Hitbox)) {
                IsTouchingBorder = true;
                break;
            }
        }

        if (IsTouchingBorder) {
            PlayerX = OldPlayerX;
            PlayerY = OldPlayerY;
        }

        // Unstuck
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            if (IsKeyDown(KEY_R)) {
                IsTryingToReset = true;
            }
        }
        if (IsTryingToReset && IsKeyDown(KEY_Y)) {
            IsTryingToReset = false;
            PlayerX = GetScreenWidth() / 2 - 80;
            PlayerY = GetScreenHeight() / 2;
        } else if (IsTryingToReset && IsKeyDown(KEY_N)) {
            IsTryingToReset = false;
        }

        //Full Screen / Borderless Windowed
        if (IsKeyDown(KEY_F11)) {
            IsTryingToFullScreen = true;
        }
        if (IsTryingToFullScreen) {
            if (IsKeyDown(KEY_F)) {
                ToggleFullscreen();
                IsTryingToFullScreen = false;
            } else if (IsKeyDown(KEY_B)) {
                ToggleBorderlessWindowed();
                IsTryingToFullScreen = false;
            } else if (IsKeyDown(KEY_N)){
                IsTryingToFullScreen = false;
            }
        }

        BeginDrawing();
        if (InGame) {
            ClearBackground(WHITE);

            // Draw Map
            for (int y = 0; y < Map.size(); y++) {
                for (int x = 0; x < Map[y].size(); x++) {
                    if (Map[y][x] == 1) {
                        DrawTexture(Wall, x * 75, y * 75, WHITE);
                    }
                    else if (Map[y][x] == 100) {
                        DrawTexture(Door_Closed, x * 75, y * 75, WHITE);
                    } else if (Map[y][x] == 101){
                        DrawTexture(Door_Opened, x * 75, y * 75, WHITE);
                    } else if (Map[y][x] == 2) {
                        DrawRectangle(x * 75, y * 75, 75, 75, GRAY);
                    }
                }
            }
            DrawCircle(PlayerX, PlayerY, 10, SKIN);
            DrawCircle(PlayerX, PlayerY + 30, 20, SKYBLUE);

            DrawTexture(White_Car, 0, 8 * 75, WHITE);

            if (IsTryingToReset) {
                DrawRectangle(0, 0, 640, 45, LIGHTGRAY);
                DrawText("Do you want to reset? (Y - yes   N - no)", 5, 8.5f, 30, RED);
            }
            if (IsTryingToFullScreen) {
                DrawRectangle(0, 0, 1000, 45, LIGHTGRAY);
                DrawText("Which Windowed Mode would you like? (F - FullScreen  B - Borderless  N - Nevermind)", 5, 9.5f, 23, RED);
            }
        } else if (InMenu) {
            ClearBackground(WHITE);
            if (CheckCollisionPointRec(MousePos, StartButtonHitbox)) {
                DrawRectangle(StartButtonHitbox.x - 5, GetScreenHeight() / 2 - 5 - 22.5f, 160, 55, LIGHTGRAY);
                DrawRectangleRec(StartButtonHitbox, GRAY);
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
                DrawRectangleRec(SettingButton, GRAY);
            } else if (CheckCollisionPointRec(MousePos, SettingButton)) { 
                DrawRectangle(GetScreenWidth() / 2 - 5 - 75, GetScreenHeight() / 2 - 5 - 37.5, 160, 55, LIGHTGRAY);
                DrawRectangleRec(SettingButton, GRAY);
                DrawRectangleRec(StartButtonHitbox, GRAY);
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            } else {
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                DrawRectangleRec(StartButtonHitbox, GRAY);
                DrawRectangleRec(SettingButton, GRAY);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}