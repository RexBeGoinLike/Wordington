#include "Node.h"
#include <string>

class MergeNode : public Node
{
public:
    MergeNode(int id, int capacity, int speed, int inputDir, int outputDir, int inputCount, int outputCount)
        : Node(id, NodeType::MERGE, capacity, speed, inputDir, outputDir, inputCount, outputCount) {}


    IncomingData processData() override;

    void update() override;    

    Node* clone() override;
};

