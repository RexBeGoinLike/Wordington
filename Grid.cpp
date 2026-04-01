#include "Grid.h"

Texture2D sourceTexture;
Texture2D receiverTexture;
Texture2D logisticsTexture;
Texture2D filterTexture;

void Grid::LoadGridAssets() {
    Image sourceNodeImage = LoadImage("assets/source.png");
    Image receiverNodeImage = LoadImage("assets/receiver.png");
    Image logisticsNodeImage = LoadImage("assets/logistics.png");
    Image filterNodeImage = LoadImage("assets/filter.png");

    ImageResize(&sourceNodeImage, 50, 50);
    ImageResize(&receiverNodeImage, 50, 50);
    ImageResize(&logisticsNodeImage, 50, 50);
    ImageResize(&filterNodeImage, 50, 50);

    sourceTexture = LoadTextureFromImage(sourceNodeImage);
    receiverTexture = LoadTextureFromImage(receiverNodeImage);
    logisticsTexture = LoadTextureFromImage(logisticsNodeImage);
    filterTexture = LoadTextureFromImage(filterNodeImage);
}

Grid::Grid(int r, int c, int size) : rows(r), cols(c), cellSize(size) {
    grid.resize(rows, vector<Node*>(cols));
}

void drawNode(Node* node, int row, int col, int cellSize) {
    if (node == nullptr) return;

    if (node->getType() == NodeType::SOURCE) {
        DrawTexture(sourceTexture, (float)col * cellSize, (float)row * cellSize, WHITE);
    } else if (node->getType() == NodeType::RECEIVER) {
        DrawTexture(receiverTexture, (float)col * cellSize, (float)row * cellSize, WHITE);
    } else if (node->getType() == NodeType::LOGISTICS) {
        DrawTexture(logisticsTexture, (float)col * cellSize, (float)row * cellSize, WHITE);
    } else if (node->getType() == NodeType::FILTER) {
        DrawTexture(filterTexture, (float)col * cellSize, (float)row * cellSize, WHITE);
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
