#include "raylib.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int screenWidth = 800;
int screenHeight = 450;
const int imageScale = 4;
int WALK_FRAMES[3] = {48 * imageScale, 32 * imageScale, 16 * imageScale};
//----------------------------------------------------------------------------------
// Main Entry Point
//----------------------------------------------------------------------------------
int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib");
    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    Image image = LoadImage(ASSETS_PATH"./mario.png");
    ImageResizeNN(&image, image.width * imageScale, image.height * imageScale);
    const Texture mario_texture = LoadTextureFromImage(image);
    UnloadImage(image);

    Rectangle mario_rect = {
        .height = (float) (16 * imageScale),
        .width = (float) (16 * imageScale),
        .x = 0,
        .y = 0
    };

    const Vector2 mario_pos = {
        .x = (float) screenWidth / 2 - (float) mario_texture.width / 2,
        .y = (float) screenHeight / 2 - (float) mario_texture.height / 2
    };

    int currentFrame = 1;
    int dt = 0;
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing(); {
            if (dt >= 6) {
                dt = 0;
                currentFrame++;
                if (currentFrame >= 4) currentFrame = 1;
            }

            ClearBackground(GRAY);
            if (IsKeyDown(KEY_D) || IsKeyDown(KEY_A)) {
                mario_rect.x = (float) WALK_FRAMES[currentFrame - 1];
            } else {
                mario_rect.x = 0;
                currentFrame = 0;
            }

            if ((IsKeyPressed(KEY_A) && mario_rect.width > 0) || (IsKeyPressed(KEY_D) && mario_rect.width < 0))
                mario_rect.width = -mario_rect.width;

            DrawTextureRec(mario_texture, mario_rect, mario_pos, WHITE);
        }
        EndDrawing();

        dt++;
    }


    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
