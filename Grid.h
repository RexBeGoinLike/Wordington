#pragma once

#include "raylib.h"
#include <vector>
#include "Node.h"

using namespace std;
class Grid
{
    public:
        Grid(int r, int c, int size);    
        void drawGrid(Node* tempNode);
        void updateCell(int row, int col, Node* node);
        static void LoadGridAssets();
        
    private:
        int rows;
        int cols;
        int cellSize;
        vector<vector<Node*>> grid;

};
