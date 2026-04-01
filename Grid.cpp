#include "Grid.h"

Grid::Grid(int r, int c, int size) : rows(r), cols(c), cellSize(size) {
    grid.resize(rows, vector<Node*>(cols));
}

void drawNode(Node* node, int row, int col, int cellSize) {
    if (node == nullptr) return;

    if (node->getType() == NodeType::INPUT) {
        DrawCircle((float)col * cellSize + cellSize / 2, (float)row * cellSize + cellSize / 2, cellSize / 2, BLUE);
    } else if (node->getType() == NodeType::OUTPUT) {
        DrawRectangleRec({ (float)col * cellSize, (float)row * cellSize, (float)cellSize, (float)cellSize }, RED);
    } else if (node->getType() == NodeType::LOGISTICS) {
        DrawRectangle((float)col * cellSize, (float)row * cellSize, (float)cellSize, (float)cellSize, BLUE);
    } else if (node->getType() == NodeType::FILTER) {
        DrawTriangle((Vector2){ (float)col * cellSize + cellSize / 2, (float)row * cellSize }, 
                     (Vector2){ (float)col * cellSize, (float)row * cellSize + cellSize }, 
                     (Vector2){ (float)col * cellSize + cellSize, (float)row * cellSize + cellSize }, 
                     PURPLE);
    }
}


void Grid::drawGrid(Node* tempNode) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Rectangle cellRect = { (float)j * cellSize, (float)i * cellSize, (float)cellSize, (float)cellSize };
            DrawRectangleLinesEx(cellRect, 1, LIGHTGRAY);

            if(grid[i][j] != nullptr) {
                drawNode(grid[i][j], i, j, cellSize);
            }

            if (tempNode != nullptr) {
                Vector2 mousePos = GetMousePosition();
                int hoverRow = (int)(mousePos.y / cellSize);
                int hoverCol = (int)(mousePos.x / cellSize);

                // clamp to grid bounds
                hoverRow = (hoverRow < 0) ? 0 : (hoverRow > rows - 1) ? rows - 1 : hoverRow;
                hoverCol = (hoverCol < 0) ? 0 : (hoverCol > cols - 1) ? cols - 1 : hoverCol;

                drawNode(tempNode, hoverRow, hoverCol, cellSize);
            }
        }
    }
}


void Grid::updateCell(int row, int col, Node* node) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        Node* newNode = new Node(*node);
        grid[row][col] = newNode;
    }
}
