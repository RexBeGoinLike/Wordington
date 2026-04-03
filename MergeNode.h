#include "Node.h"
#include <string>

class MergeNode : public Node
{
public:
    MergeNode(int id, int capacity, int speed, Direction inputDir, Direction outputDir, int inputCount, int outputCount)
        : Node(id, NodeType::MERGE, capacity, speed, inputDir, outputDir, inputCount, outputCount) {}


    IncomingData processData() override;

    void update() override;

    void onPlace(int row, int col, Grid *grid) override;
    

    Node* clone() override;
};

