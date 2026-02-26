#include <raylib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Color BUTTON_HOVER = LIGHTGRAY;
Color BUTTON_COLOR = GRAY;

int FPS = 60, Width = 1280, Height = 720;

void DrawButton(Rectangle rec, const char* text, Vector2 MousePos, int FontSize) {
    Color color = BUTTON_COLOR;
    if (CheckCollisionPointRec(MousePos, rec)) {
        color = BUTTON_HOVER;
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    DrawRectangleRec(rec, color);

    int textWidth = MeasureText(text, FontSize);
    DrawText(text,
            rec.x + rec.width/2 - textWidth/2,
            rec.y + rec.height/2 - 15,
            30,
            BLACK);
};

Rectangle MakeChoiceRow(int row) {
    float ScreenW = GetScreenWidth();
    float ScreenH = GetScreenHeight();

    float LeftBoxWidth  = ScreenW * 0.18f;
    float RightBoxWidth = ScreenW * 0.55f;
    float Gap           = ScreenW * 0.03f;

    float BoxHeight = ScreenH * 0.06f;
    float RowGap    = ScreenH * 0.025f;

    float TotalWidth = LeftBoxWidth + Gap + RightBoxWidth;
    float StartX = ScreenW/2 - TotalWidth/2;

    float BaseY = ScreenH * 0.03f;

    float Y = BaseY + row * (BoxHeight + RowGap);

    return {
        StartX + LeftBoxWidth + Gap,
        Y,
        RightBoxWidth,
        BoxHeight
    };
}
// CREDIT TO AI FOR THESE IDEAS (void AND Rectangle FUNCTIONS)

int main() {
    InitWindow(Width, Height, "Testing v0.1");
    SetExitKey(KEY_NULL);
    SetTargetFPS(FPS);
    InitAudioDevice();

    int PlayerX = GetScreenWidth() / 2 - 80, PlayerY = GetScreenHeight() / 2;
    bool IsTouchingBorder = false, IsWalking = false, IsTryingToReset = false, IsTryingToFullScreen = false, InGame = false, InMenu = true, InSetting = false, InLogs = false, ClickedColor = false, ClickedFPS = false, ClickedWindowMode = false, ClickedResolution = false, IsBorderless = false, IsFullScreen = false;

    const float BUTTON_WIDTH = 260;
    const float BUTTON_HEIGHT = 70;
    const float BUTTON_SPACING = 20;

    float CenterX = GetScreenWidth() / 2.0f - BUTTON_WIDTH / 2.0f;
    float StartY = GetScreenHeight() / 2.0f - (BUTTON_HEIGHT * 1.5 + BUTTON_SPACING);

    Color SKIN = { 255, 224, 189, 255 };

    //Presets
    Color BUTTON_HOVER_BLUE = { 40, 90, 220, 255 };
    Color BUTTON_COLOR_BLUE = { 60, 120, 255, 255 };
    Color BUTTON_HOVER_ORANGE = { 240, 120, 40, 255 };
    Color BUTTON_COLOR_ORANGE = { 255, 150, 60, 255 };
    Color BUTTON_HOVER_GREEN = { 100, 210, 160, 255 };
    Color BUTTON_COLOR_GREEN = { 120, 230, 180, 255 };
    Color BUTTON_COLOR_PURPLE = { 160, 110, 255, 255 };
    Color BUTTON_HOVER_PURPLE = { 140, 80, 240, 255 };

    Sound Walking = LoadSound("assets/SFX/Walking.mp3");

    Texture2D Wall = LoadTexture("assets/texture/Wall.jpg");
    Texture2D Door_Closed = LoadTexture("assets/texture/Door_Close.jpg");
    Texture2D Door_Opened = LoadTexture("assets/texture/Door_Open.jpg");
    Texture2D White_Car = LoadTexture("assets/texture/White_Car.png");

    Rectangle PlayButton = { CenterX, StartY, BUTTON_WIDTH, BUTTON_HEIGHT };
    Rectangle SettingsButton = { CenterX, StartY + BUTTON_HEIGHT + BUTTON_SPACING, BUTTON_WIDTH, BUTTON_HEIGHT };
    Rectangle LogsButton = { CenterX, StartY + (BUTTON_HEIGHT + BUTTON_SPACING) * 2, BUTTON_WIDTH, BUTTON_HEIGHT };
    Rectangle QuitButton = { CenterX, StartY + (BUTTON_HEIGHT + BUTTON_SPACING) * 3, BUTTON_WIDTH, BUTTON_HEIGHT };

    Rectangle ColorButton = {
        GetScreenWidth() / 2.0f - (GetScreenWidth() * 0.18f + GetScreenWidth() * 0.03f + GetScreenWidth() * 0.55f) / 2.0f,
        GetScreenHeight() * 0.03f,
        GetScreenWidth() * 0.18f,
        GetScreenHeight() * 0.06f
    };

    Rectangle WindowModeButton = {
        GetScreenWidth() / 2.0f - (GetScreenWidth() * 0.18f + GetScreenWidth() * 0.03f + GetScreenWidth() * 0.55f) / 2.0f,
        GetScreenHeight() * 0.115f,
        GetScreenWidth() * 0.18f,
        GetScreenHeight() * 0.06f
    };

    Rectangle FPSButton = {
        GetScreenWidth() / 2.0f - (GetScreenWidth() * 0.18f + GetScreenWidth() * 0.03f + GetScreenWidth() * 0.55f) / 2.0f,
        GetScreenHeight() * 0.2f,
        GetScreenWidth() * 0.18f,
        GetScreenHeight() * 0.06f
    };

    Rectangle ResButton = {
        GetScreenWidth() / 2.0f - (GetScreenWidth() * 0.18f + GetScreenWidth() * 0.03f + GetScreenWidth() * 0.55f) / 2.0f,
        GetScreenHeight() * 0.285f,
        GetScreenWidth() * 0.18f,
        GetScreenHeight() * 0.06f
    };

    Rectangle Choices1 = MakeChoiceRow(0);
    Rectangle Choices2 = MakeChoiceRow(1);
    Rectangle Choices3 = MakeChoiceRow(2);
    Rectangle Choices4 = MakeChoiceRow(3);
    Rectangle Choices5 = MakeChoiceRow(4);
    Rectangle Choices6 = MakeChoiceRow(5);
    Rectangle Choices7 = MakeChoiceRow(6);
    Rectangle Choices8 = MakeChoiceRow(7);
    Rectangle Choices9 = MakeChoiceRow(8);
    Rectangle Choices10 = MakeChoiceRow(9);
    Rectangle Choices11 = MakeChoiceRow(10);
    Rectangle Choices12 = MakeChoiceRow(11);
    Rectangle Choices13 = MakeChoiceRow(12);
    Rectangle Choices14 = MakeChoiceRow(13);

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

    vector<const char*> ColorSelections = {
        "BLUE",
        "ORANGE",
        "GREEN",
        "PURPLE"
    };

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

        if (InMenu && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(MousePos, PlayButton)) {
                InGame = true;
                InMenu = false;
            } else if (CheckCollisionPointRec(MousePos, SettingsButton)) {
                InMenu = false;
                InSetting = true;
            } else if (CheckCollisionPointRec(MousePos, LogsButton)) {
                InMenu = false;
                InLogs = true;
            } else if (CheckCollisionPointRec(MousePos, QuitButton)) {
                break;
            }
        } else if (InSetting && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(MousePos, ColorButton)) {
                ClickedColor = true;
                ClickedWindowMode = false;
                ClickedFPS = false;
                ClickedResolution = false;
            } else if (ClickedColor && CheckCollisionPointRec(MousePos, Choices1)) {
                BUTTON_COLOR = BUTTON_COLOR_BLUE;
                BUTTON_HOVER = BUTTON_HOVER_BLUE;
            } else if (ClickedColor && CheckCollisionPointRec(MousePos, Choices2)) {
                BUTTON_COLOR = BUTTON_COLOR_ORANGE;
                BUTTON_HOVER = BUTTON_HOVER_ORANGE;
            } else if (ClickedColor && CheckCollisionPointRec(MousePos, Choices3)) {
                BUTTON_COLOR = BUTTON_COLOR_GREEN;
                BUTTON_HOVER = BUTTON_HOVER_GREEN;
            } else if (ClickedColor && CheckCollisionPointRec(MousePos, Choices4)) {
                BUTTON_COLOR = BUTTON_COLOR_PURPLE;
                BUTTON_HOVER = BUTTON_HOVER_PURPLE;
            }
            if (CheckCollisionPointRec(MousePos, WindowModeButton)) {
                ClickedWindowMode = true;
                ClickedColor = false;
                ClickedFPS = false;
                ClickedResolution = false;
            } else if (ClickedWindowMode && CheckCollisionPointRec(MousePos, Choices1)) {
                ToggleBorderlessWindowed();
                IsBorderless = true;
            } else if (ClickedWindowMode && CheckCollisionPointRec(MousePos, Choices2)) {
                ToggleFullscreen();
                IsFullScreen = true;
            } else if (ClickedWindowMode && CheckCollisionPointRec(MousePos, Choices3)) {
                if (IsBorderless) {
                    ToggleBorderlessWindowed();
                } else if (IsFullScreen) {
                    ToggleFullscreen();
                }
            }
        }


        if (InGame && IsKeyPressed(KEY_ESCAPE)) {
            InGame = false;
            InMenu = true;
        } else if (InSetting && IsKeyPressed(KEY_ESCAPE)) {
            InMenu = true;
            InSetting = false;
        } else if (InMenu && IsKeyPressed(KEY_ESCAPE)) {
            if (IsKeyPressedRepeat(KEY_ESCAPE)) {
                break;
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

            SetMouseCursor(MOUSE_CURSOR_DEFAULT);

            DrawButton(PlayButton, "PLAY", MousePos, 30);
            DrawButton(SettingsButton, "SETTINGS", MousePos, 30);
            DrawButton(LogsButton, "CHANGELOGS", MousePos, 30);
            DrawButton(QuitButton, "QUIT", MousePos, 30);
        } else if (InSetting) {
            ClearBackground(WHITE);

            SetMouseCursor(MOUSE_CURSOR_DEFAULT);

            DrawButton(ColorButton, "STYLE", MousePos, 30);
            DrawButton(WindowModeButton, "WINDOW MODE", MousePos, 30);
            DrawButton(FPSButton, "FPS", MousePos, 30);
            DrawButton(ResButton, "RESOLUTION", MousePos, 30);
            
            if (ClickedColor) {
                DrawButton(Choices1, ColorSelections[0], MousePos, 30);
                DrawButton(Choices2, ColorSelections[1], MousePos, 30);
                DrawButton(Choices3, ColorSelections[2], MousePos, 30);
                DrawButton(Choices4, ColorSelections[3], MousePos, 30);
            } else if (ClickedWindowMode) {
                DrawButton(Choices1, "Borderless Windowed", MousePos, 30);
                DrawButton(Choices2, "Full Screen", MousePos, 30);
                DrawButton(Choices3, "Windowed", MousePos, 30);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}