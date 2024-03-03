/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "libraries/raylib/include/raylib.h"
#include "raylib.h"
#include <stdio.h>

Sound soundArray[10];

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

    InitAudioDevice();
    soundArray[0] = LoadSound("resources/raylib_audio_resources/sound.wav");
    Music music = LoadMusicStream("resources/raylib_audio_resources/country.mp3");
    music.looping = true;
    float pitch = 0.5f;

    PlayMusicStream(music);

    Image image = LoadImage("resources/images/logo_citm.png");
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);

    Texture2D scarfy = LoadTexture("resources/sprites/scarfy.png");

    Vector2 position = { 350.0f, 280.0f };
    Rectangle frameRec = { 0.0f, 0.0f, (float)scarfy.width / 6, (float)scarfy.height };
    int currentFrame = 0;

    int framesCounter = 0;
    int framesSpeed = 8;            // Number of spritesheet frames shown by second

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    static double x= 120, y = 35;
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

        if (y > screenHeight) y = screenHeight;
        if (y < 0) y = 0;
        if (x > screenWidth) x = screenWidth;
        if (x < 0) x = 0;

        if (IsKeyPressed(KEY_SPACE))
            PlaySound(soundArray[0]);

        UpdateMusicStream(music);

        framesCounter++;

        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 5) currentFrame = 0;

            frameRec.x = (float)currentFrame * (float)scarfy.width / 6;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTextureRec(scarfy, frameRec, position, WHITE);  // Draw part of the texture

        DrawText("(c) Scarfy sprite by Eiden Marsal", screenWidth - 200, screenHeight - 20, 10, GRAY);

        DrawTexture(texture, 0, screenHeight -texture.height, WHITE);
               
        DrawCircle(x, y, 35, DARKBLUE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseAudioDevice();

    UnloadTexture(texture);
    UnloadTexture(scarfy);

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
// raylib example source code