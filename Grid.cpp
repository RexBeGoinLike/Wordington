#include "Grid.h"
#include <iostream>

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

Texture2D* getTexture(NodeType type)
{
    switch (type)
    {
        case NodeType::SOURCE: return &sourceTexture;
        case NodeType::RECEIVER: return &receiverTexture;
        case NodeType::LOGISTICS: return &logisticsTexture;
        case NodeType::FILTER: return &filterTexture;
        default: return nullptr;
    }
}

Grid::Grid(int r, int c, int size) : rows(r), cols(c), cellSize(size) {
    grid.resize(rows, vector<Node*>(cols));
}

void drawNode(Node* node, int row, int col, int cellSize)
{
    if (!node) return;

    int rotation = 0;

    switch (node->getOutputDirection())
    {
        case Direction::UP: rotation = 0; break;
        case Direction::RIGHT: rotation = 90; break;
        case Direction::DOWN: rotation = 180; break;
        case Direction::LEFT: rotation = 270; break;
    }

    Texture2D* texture = getTexture(node->getType());
    if (!texture) return;

    Rectangle sourceRec = { 0, 0, (float)texture->width, (float)texture->height };

    Rectangle destRec =
    {
        (float)col * cellSize + cellSize/2.0f,
        (float)row * cellSize + cellSize/2.0f,
        (float)cellSize,
        (float)cellSize
    };

    Vector2 origin = { cellSize/2.0f, cellSize/2.0f };

    DrawTexturePro(*texture, sourceRec, destRec, origin, rotation, WHITE);
}

void Grid::drawGrid(Node* tempNode) {
    Vector2 mousePos = GetMousePosition();
    int hoverRow = (int)(mousePos.y / cellSize);
    int hoverCol = (int)(mousePos.x / cellSize);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Rectangle cellRect = { (float)j * cellSize, (float)i * cellSize, (float)cellSize, (float)cellSize };
            DrawRectangleLinesEx(cellRect, 1, LIGHTGRAY);

            if(grid[i][j] != nullptr) {
                drawNode(grid[i][j], i, j, cellSize);

                if(grid[i][j]->getDataBuffer().size() > 0) {
                    DrawText(grid[i][j]->getDataBuffer()[0].c_str(), j * cellSize, i * cellSize, 10, RED);
                }

            }

            if (tempNode != nullptr) {
                // clamp to grid bounds
                hoverRow = (hoverRow < 0) ? 0 : (hoverRow > rows - 1) ? rows - 1 : hoverRow;
                hoverCol = (hoverCol < 0) ? 0 : (hoverCol > cols - 1) ? cols - 1 : hoverCol;

                drawNode(tempNode, hoverRow, hoverCol, cellSize);
            }
        }
    }
}


Node* Grid::updateCell(int row, int col, Node* node) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        Node* newNode = node->clone();
        grid[row][col] = newNode;

        newNode->onPlace(row, col, this);
        newNode->update();

        return newNode;
    }
    return nullptr;
}

vector<Node*> Grid::getAdjacentNodesInDirection(int row, int col, Direction dir) {
    vector<Node*> adjacentNodes;

    std::cout << "Checking adjacent nodes for (" << row << ", " << col << ") in direction " << dir << std::endl;

    switch (dir) {
        case Direction::UP:
            if (row > 0 && grid[row - 1][col]) adjacentNodes.push_back(grid[row - 1][col]);
            break;
        case Direction::DOWN:
            if (row < rows - 1 && grid[row + 1][col]) adjacentNodes.push_back(grid[row + 1][col]);
            break;
        case Direction::LEFT:
            if (col > 0 && grid[row][col - 1]) adjacentNodes.push_back(grid[row][col - 1]);
            break;
        case Direction::RIGHT:
            if (col < cols - 1 && grid[row][col + 1]) adjacentNodes.push_back(grid[row][col + 1]);
            break;
    }
    
    return adjacentNodes;
}