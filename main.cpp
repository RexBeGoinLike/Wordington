#include <iostream>
#include <raylib.h>
#include "Grid.h"
#include "Node.h"

using namespace std;

int main () {

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const int gridRows = 20;
    const int gridCols = 20;
    const int cellSize = 50;
 
    Grid grid(gridRows, gridCols, cellSize);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Wordington");
    SetTargetFPS(60);
    
    
    Node* newNode = new Node(1, NodeType::INPUT, 10, 1, Direction::UP, Direction::DOWN, 1, 1);

    while (WindowShouldClose() == false){

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            int row = (int)(mousePos.y / cellSize);
            int col = (int)(mousePos.x / cellSize);
            grid.updateCell(row, col, newNode);
        }

        if (IsKeyDown(KEY_ONE)){
            newNode->setType(NodeType::INPUT);
        }else if (IsKeyDown(KEY_TWO)){
            newNode->setType(NodeType::LOGISTICS);
        }else if (IsKeyDown(KEY_THREE)){
            newNode->setType(NodeType::FILTER);
        }else if (IsKeyDown(KEY_FOUR)){                 
            newNode->setType(NodeType::OUTPUT);
        }

        BeginDrawing();
            ClearBackground(BLACK);
   
            grid.drawGrid(newNode);  
            
        EndDrawing();
    }

    CloseWindow();
}