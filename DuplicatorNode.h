#include "Node.h"
#include <string>

class DuplicatorNode : public Node
{
public:
    DuplicatorNode(int id, int capacity, int speed, int inputDir, int outputDir, int inputCount, int outputCount)
        : Node(id, NodeType::DUPLICATOR, capacity, speed, inputDir, outputDir, inputCount, outputCount) {}

    void update() override;

    void onPlace(int row, int col, Grid *grid) override;

    Node* clone() override;
};

