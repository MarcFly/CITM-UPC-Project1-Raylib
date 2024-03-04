#include "libraries/raylib/include/raylib.h"
#include "raylib.h"
#include <stdio.h>

#define EXPLOSION_SIZE 16

Sound soundArray[10];
Music musicArray[10];
Texture2D ship;
Texture2D background;
Texture2D explosion;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib Handout 2");

    //Audio
    InitAudioDevice();

    //Sound
    soundArray[0] = LoadSound("resources/raylib_audio_resources/sound.wav");

    //Music
    musicArray[0] = LoadMusicStream("resources/raylib_audio_resources/country.mp3");
    musicArray[0].looping = true;
    float pitch = 0.5f;

    PlayMusicStream(musicArray[0]);

    //Ship
    ship = LoadTexture("resources/sprites/Ship_1.png");

    //Background
    background = LoadTexture("resources/sprites/space_background.png");

    //Explosion
    explosion = LoadTexture("resources/sprites/explosion_set.png");
    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 8;            // Number of spritesheet frames shown by second
    int explosionColor = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    static double x = 400, y = 400;
    static double speed_x = 2, speed_y = 2;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Update your variables here
        if (IsKeyDown(KEY_RIGHT)) x += speed_x;
        if (IsKeyDown(KEY_LEFT)) x -= speed_x;
        if (IsKeyDown(KEY_DOWN)) y += speed_y;
        if (IsKeyDown(KEY_UP)) y -= speed_y;

        if (y > screenHeight - ship.height*2) y = screenHeight - ship.height*2;
        if (y < 0) y = 0;
        if (x > screenWidth - ship.width*2) x = screenWidth - ship.width * 2;
        if (x < 0) x = 0;

        if (IsKeyPressed(KEY_SPACE))
            PlaySound(soundArray[0]);

        if (IsKeyPressed(KEY_E))
        {
            explosionColor++;
            if (explosionColor >= 5)
            {
                explosionColor = 0;
            }
        }

        framesCounter++;

        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 9) currentFrame = 0;
        }

        UpdateMusicStream(musicArray[0]);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(background, 0, 0, WHITE);

        DrawTextureEx(ship, (Vector2) { x, y }, 0, 2.0f, WHITE);

        Rectangle source = (Rectangle){ currentFrame * EXPLOSION_SIZE, explosionColor * EXPLOSION_SIZE, EXPLOSION_SIZE, EXPLOSION_SIZE };
        Rectangle dest = (Rectangle){ screenWidth / 2, screenHeight / 2, EXPLOSION_SIZE * 2, EXPLOSION_SIZE * 2 };
        DrawTexturePro(explosion, source, dest, (Vector2) { dest.width/2, dest.height/2 }, 0, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseAudioDevice();

    UnloadTexture(ship);
    UnloadTexture(background);
    UnloadTexture(explosion);

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}