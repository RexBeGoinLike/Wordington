#pragma once
#include "Node.h"

class IntersectionNode : public Node
{
public:
        IntersectionNode(int id, int capacity, int speed, int inputDir, int outputDir, int inputCount, int outputCount,  int row, int col, Grid *grid)
            : Node(id, NodeType::INTERSECTION, capacity, speed, inputDir, outputDir, inputCount, outputCount, row, col), grid(grid){}

        void update() override;
        Node* clone() override;
        void sendData(IncomingData data);
    private:
        Grid *grid;
};