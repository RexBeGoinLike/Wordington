#include "Node.h"
#include <string>

class SourceNode : public Node
{
public:
    SourceNode(int id, int capacity, int speed, Direction inputDir, Direction outputDir, int inputCount, int outputCount)
        : Node(id, NodeType::SOURCE, capacity, speed, inputDir, outputDir, inputCount, outputCount) {}
    
    string processData() override;

    void update() override;

    void onPlace(int row, int col, Grid *grid) override;

    Node* clone() override;
};

