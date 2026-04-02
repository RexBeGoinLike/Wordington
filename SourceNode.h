#include "Node.h"
#include <string>

class SourceNode : public Node
{
public:
    SourceNode(int id, int capacity, int speed, Direction inputDir, Direction outputDir, int inputCount, int outputCount)
        : Node(id, NodeType::SOURCE, capacity, speed, inputDir, outputDir, inputCount, outputCount) {}
    
    void processData() override;

    void update() override;

};

