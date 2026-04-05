#include "Node.h"
#include <string>

class LogisticNode : public Node
{
public:
    LogisticNode(int id, int capacity, int speed, int inputDir, int outputDir, int inputCount, int outputCount, int row, int col)
        : Node(id, NodeType::LOGISTICS, capacity, speed, inputDir, outputDir, inputCount, outputCount, row, col) {}

    void update() override;

    void onPlace(Grid *grid);
    
    Node* clone() override;

};
    
