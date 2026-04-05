#include "Node.h"
#include <string>

class DuplicatorNode : public Node
{
private:
    Grid *grid;
public:
    DuplicatorNode(int id, int capacity, int speed, int inputDir, int outputDir, int inputCount, int outputCount, int row, int col, Grid *grid)
        : Node(id, NodeType::DUPLICATOR, capacity, speed, inputDir, outputDir, inputCount, outputCount, row, col), grid(grid) {}

    void update() override;

    void sendData(IncomingData data = IncomingData()) override;

    Node* clone() override;
};

