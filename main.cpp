#include <iostream>
#include <raylib.h>
#include <algorithm>
#include "Grid.h"
#include "Node.h"
#include "SourceNode.h"
#include "LogisticNode.h"
#include "MergeNode.h"
#include "DuplicatorNode.h"

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
            newNode = new SourceNode(1, 1, 1, DOWN, UP, 1, 1);
        }else if (IsKeyPressed(KEY_TWO)){
            newNode = new LogisticNode(2, 1, 1, DOWN, UP, 1, 1);
        }else if (IsKeyPressed(KEY_THREE)){
            newNode = new MergeNode(3, 3, 1, (DOWN | LEFT | RIGHT), UP, 3, 1);
        }else if (IsKeyPressed(KEY_FOUR)){                
  
        }
        
        //CHANGE THE SOURCE NODE OUTPUT BEFORE PLACING
        if(newNode->getType() == NodeType::SOURCE) {
            int key = GetCharPressed();
            char c = (char)key;
            if (key > 0 && isprint(c) && isalpha(c)) {
                ((SourceNode*)newNode)->setData(c);
            }
        }
        
       
        if (IsKeyPressed(KEY_TAB))
        {
            int newOutput = rotateClockwise(newNode->getOutputDirection());
            int newInput  = rotateClockwise(newNode->getInputDirection());

            newNode->setOutputDirection(newOutput);
            newNode->setInputDirection(newInput);
        }

        for(Node* node : nodeList) {        
            node->update();
        }

        BeginDrawing();
            ClearBackground(WHITE);
   
            grid.drawGrid(newNode);  
            
        EndDrawing();
    }

    CloseWindow();
}