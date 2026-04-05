#include "Node.h"
#include <string>

class SourceNode : public Node
{
private:
    char data;
public:
    SourceNode(int id, int capacity, int speed, int inputDir, int outputDir, int inputCount, int outputCount, int row, int col, char data = 'A')
        : Node(id, NodeType::SOURCE, capacity, speed, inputDir, outputDir, inputCount, outputCount, row, col), data(data) {}
    
    IncomingData processData() override;

    void update() override;

    void onPlace(Grid *grid) override;

    Node* clone() override;

    void setData(char newData);

    char getData() const;
};

