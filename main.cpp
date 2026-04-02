#include <iostream>
#include <raylib.h>
#include "Grid.h"
#include "Node.h"
#include "SourceNode.h"

using namespace std;

int main () {

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const int gridRows = 20;
    const int gridCols = 20;
    const int cellSize = 50;
    
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
            grid.updateCell(row, col, newNode);
            nodeList.push_back(newNode);
        }

        if (IsKeyPressed(KEY_ONE)){
            newNode = new SourceNode(1, 10, 1, Direction::DOWN, Direction::UP, 1, 1);
        }else if (IsKeyPressed(KEY_TWO)){
            newNode->setType(NodeType::LOGISTICS);
        }else if (IsKeyPressed(KEY_THREE)){
            newNode->setType(NodeType::FILTER);
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
            cout << "Node ID: " << node->getId() << " Type: " << node->getType() << " Buffer Size: " << node->getDataBuffer().size() << endl;
        }

        BeginDrawing();
            ClearBackground(BLACK);
   
            grid.drawGrid(newNode);  
            
        EndDrawing();
    }

    CloseWindow();
}