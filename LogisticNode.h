#include "Node.h"
#include <string>

class LogisticNode : public Node
{
public:
    LogisticNode(int id, int capacity, int speed, Direction inputDir, Direction outputDir, int inputCount, int outputCount)
        : Node(id, NodeType::LOGISTICS, capacity, speed, inputDir, outputDir, inputCount, outputCount) {}

    void update() override;

};
    
