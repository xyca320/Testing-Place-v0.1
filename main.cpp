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
        
        SetTargetFPS(FPS);

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
            if (CheckCollisionPointRec(MousePos, FPSButton)) {
                ClickedFPS = true;
                ClickedWindowMode = false;
                ClickedColor = false;
                ClickedResolution = false;
            } else if (CheckCollisionPointRec(MousePos, Choices1)) {
                FPS = 30;
            } else if (CheckCollisionPointRec(MousePos, Choices2)) {
                FPS = 60;
            } else if (CheckCollisionPointRec(MousePos, Choices3)) {
                FPS = 75;
            } else if (CheckCollisionPointRec(MousePos, Choices4)) {
                FPS = 120;
            } else if (CheckCollisionPointRec(MousePos, Choices5)) {
                FPS = 144;
            } else if (CheckCollisionPointRec(MousePos, Choices6)) {
                FPS = 165;
            } else if (CheckCollisionPointRec(MousePos, Choices7)  /*67676767676767676767676767676767676767676767*/) {
                FPS = 180;
            } else if (CheckCollisionPointRec(MousePos, Choices8)) {
                FPS = 200;
            } else if (CheckCollisionPointRec(MousePos, Choices9)) {
                FPS = 240;
            } else if (CheckCollisionPointRec(MousePos, Choices10)) {
                FPS = 300;
            } else if (CheckCollisionPointRec(MousePos, Choices11)) {
                FPS = 360;
            } else if (CheckCollisionPointRec(MousePos, Choices12)) {
                FPS = 520;
            } else if (CheckCollisionPointRec(MousePos, Choices13)) {
                FPS = 600;
            } else if (CheckCollisionPointRec(MousePos, Choices14)) {
                FPS = 720;
            }
            if (CheckCollisionPointRec(MousePos, ResButton)) {
                ClickedResolution = true;
                ClickedWindowMode = false;
                ClickedColor = false;
                ClickedFPS = false;
            } else if (CheckCollisionPointRec(MousePos, Choices1)) {
                Width = 620;
                Height = 480;
                CloseWindow();
                InitWindow(Width, Height, "Testing v0.1");
            } else if (CheckCollisionPointRec(MousePos, Choices2)) {
                Width = 1280;
                Height = 720;
                CloseWindow();
                InitWindow(Width, Height, "Testing v0.1");
            } else if (CheckCollisionPointRec(MousePos, Choices3)) {
                Width = 1366;
                Height = 768;
                CloseWindow();
                InitWindow(Width, Height, "Testing v0.1");
            } else if (CheckCollisionPointRec(MousePos, Choices4)) {
                Width = 1600;
                Height = 900;
                CloseWindow();
                InitWindow(Width, Height, "Testing v0.1");
            } else if (CheckCollisionPointRec(MousePos, Choices5)) {
                Width = 1920;
                Height = 1080;
                CloseWindow();
                InitWindow(Width, Height, "Testing v0.1");InitWindow(Width, Height, "Testing v0.1");
            } else if (CheckCollisionPointRec(MousePos, Choices6)) {
                Width = 2560;
                Height = 1080;
                CloseWindow();
                InitWindow(Width, Height, "Testing v0.1");
            } else if (CheckCollisionPointRec(MousePos, Choices7)  /*67676767676767676767676767676767676767676767*/) {
                Width = 2560;
                Height = 1440;
                CloseWindow();
                InitWindow(Width, Height, "Testing v0.1");
            } else if (CheckCollisionPointRec(MousePos, Choices8)) {
                Width = 2560;
                Height = 1600;
                CloseWindow();
                InitWindow(Width, Height, "Testing v0.1");
            } else if (CheckCollisionPointRec(MousePos, Choices9)) {
                Width = 3440;
                Height = 1440;
                CloseWindow();
                InitWindow(Width, Height, "Testing v0.1");
            } else if (CheckCollisionPointRec(MousePos, Choices10)) {
                Width = 2880;
                Height = 1620;
                CloseWindow();
                InitWindow(Width, Height, "Testing v0.1");InitWindow(Width, Height, "Testing v0.1");
            } else if (CheckCollisionPointRec(MousePos, Choices11)) {
                Width = 3200;
                Height = 1800;
                CloseWindow();
                InitWindow(Width, Height, "Testing v0.1");InitWindow(Width, Height, "Testing v0.1");
            } else if (CheckCollisionPointRec(MousePos, Choices12)) {
                Width = 3456;
                Height = 2160;
                CloseWindow();
                InitWindow(Width, Height, "Testing v0.1");
            } else if (CheckCollisionPointRec(MousePos, Choices13)) {
                Width = 2840;
                Height = 2160;
                CloseWindow();
                InitWindow(Width, Height, "Testing v0.1");
            } else if (CheckCollisionPointRec(MousePos, Choices14)) {
                Width = 7680;
                Height = 4320;
                CloseWindow();
                InitWindow(Width, Height, "Testing v0.1");
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
            } else if (ClickedFPS) {
                DrawButton(Choices1, "30 FPS", MousePos, 30);
                DrawButton(Choices2, "60 FPS", MousePos, 30);
                DrawButton(Choices3, "75 FPS", MousePos, 30);
                DrawButton(Choices4, "120 FPS", MousePos, 30);
                DrawButton(Choices5, "144 FPS", MousePos, 30);
                DrawButton(Choices6, "165 FPS", MousePos, 30);
                DrawButton(Choices7, "180 FPS", MousePos, 30);
                DrawButton(Choices8, "240 FPS", MousePos, 30);
                DrawButton(Choices9, "300 FPS", MousePos, 30);
                DrawButton(Choices10, "360 FPS", MousePos, 30);
                DrawButton(Choices11, "520 FPS", MousePos, 30);
                DrawButton(Choices12, "600 FPS", MousePos, 30);
                DrawButton(Choices13, "720 FPS", MousePos, 30);
            } else if (ClickedResolution) {
                DrawButton(Choices1, "640 x 480p", MousePos, 30);
                DrawButton(Choices2, "1280 x 720p", MousePos, 30);
                DrawButton(Choices3, "1366 x 768p", MousePos, 30);
                DrawButton(Choices4, "1600 x 900p", MousePos, 30);
                DrawButton(Choices5, "1920 x 1080p", MousePos, 30);
                DrawButton(Choices6, "2560 x 1080p", MousePos, 30);
                DrawButton(Choices7, "2560 x 1440p", MousePos, 30);
                DrawButton(Choices8, "2560 x 1600p", MousePos, 30);
                DrawButton(Choices9, "3440 x 1440p", MousePos, 30);
                DrawButton(Choices10, "2880 x 1620p", MousePos, 30);
                DrawButton(Choices11, "3200 x 1800p", MousePos, 30);
                DrawButton(Choices12, "3456 x 2160p", MousePos, 30);
                DrawButton(Choices13, "3840 x 2160p", MousePos, 30);
                DrawButton(Choices14, "7680 x 4320p", MousePos, 30);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}