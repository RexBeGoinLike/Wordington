#include "Node.h"
#include <string>

class OutputNode : public Node
{
private:
    string *requiredText;
public:
    OutputNode(int id, int capacity, int speed, int inputDir, int outputDir, int inputCount, int outputCount, int row, int col, string *requiredText)
        : Node(id, NodeType::SOURCE, capacity, speed, inputDir, outputDir, inputCount, outputCount, row, col), requiredText(requiredText) {}
    
    void update() override;

    void onPlace(Grid *grid) override;

    Node* clone() override;

    void setText(string *requiredText);
};

