#include "raylib.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int screenWidth = 800;
int screenHeight = 450;
const int imageScale = 4;
int WALK_FRAMES[3] = {48 * imageScale, 32 * imageScale, 16 * imageScale};
int JUMP_FRAMES[2]={80 * imageScale};


struct Mario {
    Vector2 position;
    Rectangle frame;
    Texture texture;
};

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
    Image image = LoadImage("./mario.png");
    ImageResizeNN(&image, image.width * imageScale, image.height * imageScale);


    struct Mario mario = {
        .frame = {
            .height = 16 * imageScale,
            .width = 16 * imageScale,
            .x = 0,
            .y = 0
        },
        .texture = LoadTextureFromImage(image)
    };

    mario.position = (Vector2){
        .x = (float) screenWidth / 2 - (float) mario.texture.width / 2,
        .y = (float) screenHeight / 2 - (float) mario.texture.height / 2
    };

    UnloadImage(image);

    const float floor = (float) screenHeight / 2 - (float) mario.texture.height / 2;
    int currentFrame = 1;
    int dt = 0;
    float accel = 0.0f;
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing(); {
            // Movement Begin
            // --------------------------------------------------------------------------------------------------------
            if (IsKeyDown(KEY_D)) {
                mario.position.x += 3.0f;
            }

            if (IsKeyDown(KEY_A)) {
                mario.position.x -= 3.0f;
            }

            if (accel == 0.0f ) {
                if (mario.position.y < floor) {
                    accel = -30.0f;
                }
            }

            if (mario.position.y > floor){
                if (accel < 0.0f) {
                    accel = 0.0f;
                }
                mario.position.y =floor;
            }


            if (IsKeyPressed(KEY_W)) {
                accel = 30.0f;
            }
            if (accel > 0.0f) {
                mario.position.y -= 4.0f;
                accel -= 1.0f;
            }
            if (accel < 0.0f) {
                mario.position.y += 4.0f;
                accel += 1.0f;
            }


            // --------------------------------------------------------------------------------------------------------
            // Movement End

            // Animation Begin
            // --------------------------------------------------------------------------------------------------------
            if (dt >= 6) {
                dt = 0;
                currentFrame++;
                if (currentFrame >= 4) currentFrame = 1;
            }

            if (IsKeyDown(KEY_D) || IsKeyDown(KEY_A)) {
                mario.frame.x = (float) WALK_FRAMES[currentFrame - 1];
            } else {
                mario.frame.x = 0;
                currentFrame = 0;
            }

            if ((IsKeyPressed(KEY_A) && mario.frame.width > 0) || (IsKeyPressed(KEY_D) && mario.frame.width < 0))
                mario.frame.width = -mario.frame.width;
            if (mario.position.y < floor) {
                mario.frame.x = (float) JUMP_FRAMES[0];
            }
            ClearBackground(GRAY);
            // --------------------------------------------------------------------------------------------------------
            // Animation End

            DrawTextureRec(mario.texture, mario.frame, mario.position, WHITE);
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
