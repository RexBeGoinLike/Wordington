#include "Node.h"
#include <string>

class SourceNode : public Node
{
private:
    char data;
public:
    SourceNode(int id, int capacity, int speed, Direction inputDir, Direction outputDir, int inputCount, int outputCount, char data = 'A')
        : Node(id, NodeType::SOURCE, capacity, speed, inputDir, outputDir, inputCount, outputCount), data(data) {}
    
    string processData() override;

    void update() override;

    void onPlace(int row, int col, Grid *grid) override;

    Node* clone() override;

    void setData(char newData);

    char getData() const;
};

