#pragma once

#include "raylib.h"
#include <vector>
#include "Node.h"

using namespace std;
class Grid
{
    public:
        Grid(int r, int c, int size, int offset);    
        void drawGrid(Node* tempNode);
        Node* updateCell(int row, int col, Node* node);
        static void LoadGridAssets();
        Node* removeNode(int row, int col);
        vector<Node*> getAdjacentNodesInDirection(int row, int col, int dirMask);
        void drawNode(Node* node, int row, int col, int cellSize, int offset, int temp = true);
        void drawPalette(int offset, int selected);
        
    private:
        int rows;
        int cols;
        int cellSize;
        int offset;
        vector<vector<Node*>> grid;

};
