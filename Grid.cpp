#include "Grid.h"
#include <iostream>
Texture2D sourceTexture;
Texture2D logisticsTexture;
Texture2D cornerLogTexture;
Texture2D filterTexture;
Texture2D tileTexture;
Texture2D duplicatorTexture;
Texture2D intersectionTexture;
Texture2D receiverTexture;

void Grid::LoadGridAssets() {

    int cellsize = 67;
    Image sourceNodeImage = LoadImage("assets/source.png");
    Image logisticsNodeImage = LoadImage("assets/logistics.png");
    Image cornerLogImage = LoadImage("assets/logisticscorner.png");
    Image filterNodeImage = LoadImage("assets/filter.png");
    Image tileImage = LoadImage("assets/tile.png");
    Image duplicatorImage = LoadImage("assets/duplicator.png");
    Image intersectionImage = LoadImage("assets/intersection.png");
    Image receiverImage = LoadImage("assets/receiver.png");

    ImageResize(&sourceNodeImage, cellsize, cellsize);
    ImageResize(&logisticsNodeImage, cellsize, cellsize);
    ImageResize(&cornerLogImage, cellsize, cellsize);
    ImageResize(&filterNodeImage, cellsize, cellsize);
    ImageResize(&tileImage, cellsize, cellsize);
    ImageResize(&duplicatorImage, cellsize, cellsize);
    ImageResize(&intersectionImage, cellsize, cellsize);
    ImageResize(&receiverImage, cellsize, cellsize);

    sourceTexture = LoadTextureFromImage(sourceNodeImage);
    logisticsTexture = LoadTextureFromImage(logisticsNodeImage);
    cornerLogTexture = LoadTextureFromImage(cornerLogImage);
    filterTexture = LoadTextureFromImage(filterNodeImage);
    tileTexture = LoadTextureFromImage(tileImage);
    duplicatorTexture = LoadTextureFromImage(duplicatorImage);
    intersectionTexture = LoadTextureFromImage(intersectionImage);
    receiverTexture = LoadTextureFromImage(receiverImage);
}

Texture2D* getTexture(NodeType type)
{
    switch (type)
    {
        case NodeType::SOURCE: return &sourceTexture;
        case NodeType::RECEIVER: return &receiverTexture;
        case NodeType::LOGISTICS: return &logisticsTexture;
        case NodeType::CORNERLOG: return &cornerLogTexture;
        case NodeType::MERGE: return &filterTexture;
        case NodeType::DUPLICATOR: return &duplicatorTexture;
        case NodeType::INTERSECTION: return &intersectionTexture;
        default: return nullptr;
    }
}

Grid::Grid(int r, int c, int size, int offset) : rows(r), cols(c), cellSize(size), offset(offset) {
    grid.resize(rows, vector<Node*>(cols));
}

void Grid::drawNode(Node* node, int row, int col, int cellSize, int offset, int temp)
{
    int rotation = 0;
    int mask = node->getOutputDirection();

    if (mask & UP) rotation = 0;
    else if (mask & RIGHT) rotation = 90;
    else if (mask & DOWN) rotation = 180;
    else if (mask & LEFT) rotation = 270;

    Texture2D* texture = getTexture(node->getType());
    if (!texture) return;

    Rectangle sourceRec = { 0, 0, (float)texture->width, (float)texture->height };

    Rectangle destRec =
    {
        (float)col * cellSize + cellSize/2.0f + offset, 
        (float)row * cellSize + cellSize/2.0f + offset,
        (float)cellSize,
        (float)cellSize
    };

    Vector2 origin = { cellSize/2.0f, cellSize/2.0f };
    
    if(temp){
        if(!grid[row][col]){
            Color color = { 0, 255, 0, 128 };
            DrawTexturePro(*texture, sourceRec, destRec, origin, rotation, color);
        }else{
            Color color = { 255, 0, 0, 128 };
            DrawTexturePro(*texture, sourceRec, destRec, origin, rotation, color);  
        }          
    }else{
            DrawTexturePro(*texture, sourceRec, destRec, origin, rotation, WHITE);       
    }
    
}

void Grid::drawGrid(Node* tempNode) {
    Vector2 mousePos = GetMousePosition();


    int hoverRow = (int)((mousePos.y - offset) / cellSize);
    int hoverCol = (int)((mousePos.x - offset) / cellSize);

    hoverRow = (hoverRow < 0) ? 0 : (hoverRow >= rows) ? rows - 1 : hoverRow;
    hoverCol = (hoverCol < 0) ? 0 : (hoverCol >= cols) ? cols - 1 : hoverCol;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
      
            Rectangle cellRect = { 
                (float)j * cellSize + offset, 
                (float)i * cellSize + offset, 
                (float)cellSize, 
                (float)cellSize 
            };
            DrawRectangleLinesEx(cellRect, 1, LIGHTGRAY);

            if (grid[i][j] != nullptr) {
                drawNode(grid[i][j], i, j, cellSize, offset, false); 
        
                if (grid[i][j]->getDataBuffer().size() > 0) {
                    std::string buffer = "";
                    for (IncomingData& data : grid[i][j]->getDataBuffer()) {
                        buffer += data.getData();
                    }

                    DrawText(buffer.c_str(), 
                             (int)(j * cellSize + offset), 
                             (int)(i * cellSize + offset), 
                             20, BLACK);
                }
            }


            if (tempNode != nullptr && i == hoverRow && j == hoverCol) {
                drawNode(tempNode, hoverRow, hoverCol, cellSize, offset);

                std::string buffer = "";
                for (IncomingData& data : tempNode->getDataBuffer()) {
                    buffer += data.getData();
                }

                buffer = (buffer == " ") ? "' '" : buffer;
                DrawText(buffer.c_str(), 
                            (int)(j * cellSize + offset), 
                            (int)(i * cellSize + offset), 
                            20, BLACK);
        }
        }
    }
}


Node* Grid::updateCell(int row, int col, Node* node) {

    if (row < 0 || row >= rows || col < 0 || col >= cols)
        return nullptr;

    if (grid[row][col] != nullptr) {
        std::cout << "Cannot place node at (" << row << ", " << col << ") — cell already occupied." << std::endl;
        return nullptr;
    }

    Node* newNode = node->clone();
    grid[row][col] = newNode;
    newNode->setRow(row);
    newNode->setCol(col);
    newNode->onPlace(this);

    std::cout << "Placed at: " << row << " " << col << std::endl;
    std::cout << "Node Placed at: " << newNode->getRow() << " " << newNode->getCol() << std::endl;
    std::cout << "Node Type: " << newNode->getType() << std::endl;
    std::cout << newNode->getInputConnections().size() << " " << newNode->getOutputConnections().size() << std::endl;

    return newNode;
}

vector<Node*> Grid::getAdjacentNodesInDirection(int row, int col, int dirMask) {
    vector<Node*> adjacentNodes;

    if (dirMask & UP && row > 0 && grid[row-1][col])

        adjacentNodes.push_back(grid[row-1][col]);

    if (dirMask & DOWN && row < rows-1 && grid[row+1][col])

        adjacentNodes.push_back(grid[row+1][col]);

    if (dirMask & LEFT && col > 0 && grid[row][col-1])

        adjacentNodes.push_back(grid[row][col-1]);

    if (dirMask & RIGHT && col < cols-1 && grid[row][col+1])

        adjacentNodes.push_back(grid[row][col+1]);

    return adjacentNodes;
}

Node* Grid::removeNode(int row, int col){
    if (row < 0 || row >= rows || col < 0 || col >= cols) return nullptr;

    Node* node = grid[row][col];
    if (!node) return nullptr;

    for (Node* outputNode : node->getOutputConnections()){
        outputNode->removeInputConnection(node);
    }

    for (Node* inputNode : node->getInputConnections()){
        inputNode->removeOutputConnection(node);
    }

    grid[row][col] = nullptr;

    return node; 
}

void Grid::drawPalette(int offset, int selected)
{
    const int startX = (offset - cellSize)/2;
    int startY = offset;
    const int cellSize = 67;
    const int padding = 20;

    for (int i = 0; i < COUNT; i++)
    {
        NodeType type = static_cast<NodeType>(i);

        if (type == CORNERLOG) continue;

        Texture2D* tex = getTexture(type);
        if (!tex) continue;

        int opacity = (i + 1 == selected) ? 64 : 255;
        Color color = {255, 255, 255, opacity};
        Rectangle box = { (float)startX, (float)startY, (float)cellSize, (float)cellSize };
        DrawRectangleLinesEx(box, 2, color);

        Rectangle srcRec = { 0, 0, (float)tex->width, (float)tex->height };
        Rectangle destRec = { startX + cellSize/2.0f, startY + cellSize/2.0f, (float)cellSize, (float)cellSize };
        Vector2 origin = { (float)cellSize/2.0f, (float)cellSize/2.0f };
        DrawTexturePro(*tex, srcRec, destRec, origin, 0, color);

        DrawText(TextFormat("%d", i+1), startX + 5, startY + 5, 23, BLACK);

        startY += cellSize + padding;
    }
}
