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

    const int SCREEN_WIDTH = 900;
    const int SCREEN_HEIGHT = 900;
    const int gridRows = 8;
    const int gridCols = 8;
    const int cellSize = 67;
    const int offset = (SCREEN_WIDTH - (gridCols * cellSize)) / 2;
    vector<string> tooltips = {
        "Outputs the indicated character at the top left towards the direction of the green arrow.\nChange the output by pressing a LETTER or the SPACE key on your keyboard",
        "Transports a letter from one node to another in the indicated direction.",
        "Merges the inputs into the indicated output.\nCharacters are merged in the order UP | LEFT | RIGHT | DOWN, ignoring the output side.",
        "Duplicates an input towards the three indicated output directions.",
        "Allows connections to intersect by directing inputs towards their opposite direction.",
        "Checks if the input matches the target sentence (REQUIRED TO COMPLETE A SENTENCE)."
    };

    int selected = 1;

    Grid grid(gridRows, gridCols, cellSize, offset);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Wordington");
    SetTargetFPS(60);

    Grid::LoadGridAssets();
    
    vector<Node*> nodeList;
    
    Node* newNode = new SourceNode(1, 10, 1, Direction::DOWN, Direction::UP, 1, 1, 1, 1);
    
    srand((unsigned)time(nullptr));

    SentenceReader reader("sentences.txt");
    char selectedChar = 'A';

    string generatedText = reader.getRandomSentence();

    while (WindowShouldClose() == false){

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();

            int row = (int)((mousePos.y - offset) / cellSize);
            int col = (int)((mousePos.x - offset) / cellSize);

            Node* node = grid.updateCell(row, col, newNode);
            if (node)
                nodeList.push_back(node);
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            Vector2 mousePos = GetMousePosition();

            int row = (int)((mousePos.y - offset) / cellSize);
            int col = (int)((mousePos.x - offset) / cellSize);

            Node* node = grid.removeNode(row, col);

            if (node != nullptr) {
                auto it = std::find(nodeList.begin(), nodeList.end(), node);
                if (it != nodeList.end()) {
                    nodeList.erase(it);
                }
            }

            node = nullptr;
        }
    

        if (IsKeyPressed(KEY_ONE)){
            newNode = new SourceNode(1, 1, 1, NULL, UP, 0, 1, 1, 1);
            selected = 1;
        }else if (IsKeyPressed(KEY_TWO)){
            newNode = new LogisticNode(2, 1, 1, DOWN, UP, 1, 1, 1, 1);
            selected = 2;
        }else if (IsKeyPressed(KEY_THREE)){
            newNode = new MergeNode(3, 3, 1, (DOWN | LEFT | RIGHT), UP, 3, 1, 1, 1);
            selected = 3;
        }else if (IsKeyPressed(KEY_FOUR)){                
            newNode = new DuplicatorNode(4, 1, 1, DOWN, (UP | LEFT | RIGHT), 1, 3, 1, 1, &grid);
            selected = 4;
        }else if (IsKeyPressed(KEY_FIVE)){
            newNode = new IntersectionNode(5, 2, 1, (LEFT | DOWN | UP | RIGHT), (LEFT | DOWN | UP | RIGHT), 4, 4, 1, 1, &grid);
            selected = 5;
        }else if (IsKeyPressed(KEY_SIX)){
            newNode = new OutputNode (6, 1, 1, DOWN, NULL, 1, 0, 1, 1, &generatedText, &reader);
            selected = 6;
        }
        
        
        //CHANGE THE SOURCE NODE OUTPUT BEFORE PLACING
        if(newNode->getType() == NodeType::SOURCE) {
            int key = GetCharPressed();
            char c = (char)key;
            selectedChar = c;
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
            grid.drawPalette(offset, selected);

            //Top Label
            string label = "Build the sentence:";
            int labelsize = 20;
            DrawText(label.c_str(), (SCREEN_WIDTH - ((int) MeasureText(label.c_str(), labelsize)))/2, (offset - labelsize)/2 - (labelsize*1.5), labelsize, BLACK);
            int fontsize = 30; 
            DrawText((generatedText).c_str(), (SCREEN_WIDTH - ((int) MeasureText(generatedText.c_str(), fontsize)))/2, (offset - fontsize)/2, fontsize, BLACK);
            label = "Press RIGHT MOUSE BUTTON to remove a component";
            DrawText(label.c_str(), (SCREEN_WIDTH - ((int) MeasureText(label.c_str(), labelsize)))/2, (offset - labelsize)/2 + (labelsize*1.7), labelsize, BLACK);
            label = "Press TAB to rotate a component";
            DrawText(label.c_str(), (SCREEN_WIDTH - ((int) MeasureText(label.c_str(), labelsize)))/2, (offset - labelsize)/2 + (labelsize*2.9), labelsize, BLACK);

            labelsize = 18;
            DrawText(tooltips[selected - 1].c_str(), (SCREEN_WIDTH - ((int) MeasureText(tooltips[selected - 1].c_str(), labelsize)))/2, (SCREEN_HEIGHT - offset) + labelsize*2, labelsize, BLACK);
            
        EndDrawing();
    }

    CloseWindow();
}