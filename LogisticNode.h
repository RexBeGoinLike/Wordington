#include "Node.h"
#include <string>

class LogisticNode : public Node
{
public:
    LogisticNode(int id, int capacity, int speed, int inputDir, int outputDir, int inputCount, int outputCount)
        : Node(id, NodeType::LOGISTICS, capacity, speed, inputDir, outputDir, inputCount, outputCount) {}

    void update() override;

    Node* clone() override;

};
    
