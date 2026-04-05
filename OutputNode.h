#include "Node.h"
#include "SentenceReader.h"
#include <string>

class OutputNode : public Node
{
private:
    string *requiredText;
    SentenceReader *reader;
public:
    OutputNode(int id, int capacity, int speed, int inputDir, int outputDir, int inputCount, int outputCount, int row, int col, string *requiredText, SentenceReader *reader)
        : Node(id, NodeType::RECEIVER, capacity, speed, inputDir, outputDir, inputCount, outputCount, row, col), requiredText(requiredText), reader(reader) {}
    
    void update() override;

    void onPlace(Grid *grid) override;

    void receiveData(IncomingData& data) override;

    Node* clone() override;

    void setText(string *requiredText);

    string* getText();
};

