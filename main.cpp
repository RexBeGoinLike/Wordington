#include <iostream>
#include <raylib.h>
#include "Grid.h"
#include "Node.h"
#include "SourceNode.h"
#include "LogisticNode.h"
#include "MergeNode.h"

using namespace std;

int main () {

    const int SCREEN_WIDTH = 1600;
    const int SCREEN_HEIGHT = 900;
    const int gridRows = 25;
    const int gridCols = 25;
    const int cellSize = 64;

    int rotation = 0;
    Grid grid(gridRows, gridCols, cellSize);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Wordington");
    SetTargetFPS(60);

    Grid::LoadGridAssets();
    
    vector<Node*> nodeList;
    
    Node* newNode = new SourceNode(1, 10, 1, Direction::DOWN, Direction::UP, 1, 1);

    while (WindowShouldClose() == false){

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            int row = (int)(mousePos.y / cellSize);
            int col = (int)(mousePos.x / cellSize);
            nodeList.push_back(grid.updateCell(row, col, newNode));
        }

        if (IsKeyPressed(KEY_ONE)){
            newNode = new SourceNode(1, 1, 1, Direction::DOWN, Direction::UP, 1, 1);
        }else if (IsKeyPressed(KEY_TWO)){
            newNode = new LogisticNode(2, 1, 1, Direction::DOWN, Direction::UP, 1, 1);
        }else if (IsKeyPressed(KEY_THREE)){
            newNode = new MergeNode(3, 3, 1, Direction::DOWN, Direction::UP, 1, 1);
        }else if (IsKeyPressed(KEY_FOUR)){                 
            newNode->setType(NodeType::RECEIVER);
        }

        if (IsKeyPressed(KEY_R))
        {
            rotation = (rotation + 1) % 4;
            switch (rotation)
            {
            case 0:
                newNode->setOutputDirection(Direction::UP);
                newNode->setInputDirection(Direction::DOWN);
                break;
            
            case 1:
                
                newNode->setOutputDirection(Direction::RIGHT);
                newNode->setInputDirection(Direction::LEFT);
                break;  

            case 2:
                newNode->setOutputDirection(Direction::DOWN);
                newNode->setInputDirection(Direction::UP);
                break;      

            case 3:
                newNode->setOutputDirection(Direction::LEFT);
                newNode->setInputDirection(Direction::RIGHT);
                break;

            default:
                break;
            }
        }

        for(Node* node : nodeList) {        
            node->update();
        }


        BeginDrawing();
            ClearBackground(BLACK);
   
            grid.drawGrid(newNode);  
            
        EndDrawing();
    }

    CloseWindow();
}