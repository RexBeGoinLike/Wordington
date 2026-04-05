#include <iostream>
#include <raylib.h>
#include <algorithm>
#include "SentenceReader.h"
#include "Grid.h"
#include "Node.h"
#include "SourceNode.h"
#include "LogisticNode.h"
#include "MergeNode.h"
#include "DuplicatorNode.h"
#include "IntersectionNode.h"
#include "OutputNode.h"

using namespace std;

int main () {

    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;
    const int gridRows = 18;
    const int gridCols = 35;
    const int cellSize = 50;
    const int offset(100);

    Grid grid(gridRows, gridCols, cellSize, offset);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Wordington");
    SetTargetFPS(60);

    Grid::LoadGridAssets();
    
    vector<Node*> nodeList;
    
    Node* newNode = new SourceNode(1, 10, 1, Direction::DOWN, Direction::UP, 1, 1, 1, 1);
    
    srand((unsigned)time(nullptr));

    SentenceReader reader("sentences.txt");

    string generatedText = reader.getRandomSentence();

    while (WindowShouldClose() == false){

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();

        int row = (int)((mousePos.y - offset) / cellSize);
        int col = (int)((mousePos.x - offset) / cellSize);

        nodeList.push_back(grid.updateCell(row, col, newNode));
    }

        if (IsKeyPressed(KEY_ONE)){
            newNode = new SourceNode(1, 1, 1, DOWN, UP, 0, 1, 1, 1);
        }else if (IsKeyPressed(KEY_TWO)){
            newNode = new LogisticNode(2, 1, 1, DOWN, UP, 1, 1, 1, 1);
        }else if (IsKeyPressed(KEY_THREE)){
            newNode = new MergeNode(3, 3, 1, (DOWN | LEFT | RIGHT), UP, 3, 1, 1, 1);
        }else if (IsKeyPressed(KEY_FOUR)){                
            newNode = new DuplicatorNode(4, 1, 1, DOWN, (UP | LEFT | RIGHT), 1, 3, 1, 1, &grid);
        }else if (IsKeyPressed(KEY_FIVE)){
            newNode = new IntersectionNode(5, 2, 1, (LEFT | DOWN), (UP | RIGHT), 2, 2, 1, 1, &grid);
        }else if (IsKeyPressed(KEY_SIX)){
            newNode = new OutputNode (6, 1, 1, DOWN, UP, 1, 0, 1, 1, &generatedText, &reader);
        }
        
        
        //CHANGE THE SOURCE NODE OUTPUT BEFORE PLACING
        if(newNode->getType() == NodeType::SOURCE) {
            int key = GetCharPressed();
            char c = (char)key;
            if (key > 0 && isprint(c) && (isalpha(c) || c == ' ')) {
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
            int fontsize = 40; 
            DrawText(("Build The Sentence: " + generatedText).c_str(), offset, offset - fontsize - (fontsize/2), fontsize, BLACK);
            
        EndDrawing();
    }

    CloseWindow();
}