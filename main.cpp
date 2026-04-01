#include <iostream>
#include <raylib.h>
#include <vector>
#include "Classes/InputNode.h"
using namespace std;

int main () {

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const int gridRows = 20;
    const int gridCols = 20;
    const int cellSize = 50;
    Color color = GREEN;
    vector<vector<InputNode>> grid(gridRows, vector<InputNode>(gridCols));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Wordington");
    SetTargetFPS(60);

    while (WindowShouldClose() == false){
        auto mousePos = GetMousePosition();
        int hoveredRow = (int)(mousePos.y / cellSize);
        int hoveredCol = (int)(mousePos.x / cellSize);

        //Change Color
        if (IsKeyDown(KEY_ONE))
        {
            color = GREEN;
        }
        else if (IsKeyDown(KEY_TWO))
        {
            color = RED;
        }
        else if (IsKeyDown(KEY_THREE))
        {
            color = BLUE;
        }

        //Place Items in Grid
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            grid[hoveredRow][hoveredCol].setColor(color);
            grid[hoveredRow][hoveredCol].setFlag(1);
        }


        BeginDrawing();
            ClearBackground(BLACK);
            //Draw the grid
            for (int i = 0; i < gridRows; i++) {
                for (int j = 0; j < gridCols; j++) {
                    Rectangle cellRect = { (float)j * cellSize, (float)i * cellSize, (float)cellSize, (float)cellSize };
                    DrawRectangleLinesEx(cellRect, 1, LIGHTGRAY);
                    if(hoveredRow == i && hoveredCol == j) {
                        DrawCircle(cellRect.x + cellSize / 2, cellRect.y + cellSize / 2, cellSize / 4, color);
                    }

                    if (grid[i][j].getFlag() == 1) {
                        DrawCircle(cellRect.x + cellSize / 2, cellRect.y + cellSize / 2, cellSize / 4, grid[i][j].getColor());
                    }
                }
            }

  
     
            
        EndDrawing();
    }

    CloseWindow();
}