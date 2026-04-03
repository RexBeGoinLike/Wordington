#include "MergeNode.h"
#include "Grid.h"
#include <iostream>

string MergeNode::processData() {
    string mergedData;
    for (const string& data : getDataBuffer()) {
        mergedData += data;
    }
    return mergedData;
}

void MergeNode::update() {
    sendData(processData());
}

void MergeNode::onPlace(int row, int col, Grid *grid) {
    for (Node* outputNode : grid->getAdjacentNodesInDirection(row, col, getOutputDirection())) {
        addOutputConnection(outputNode);
        outputNode->addInputConnection(this);
    }
    
    for (int d = 0; d < 4; d++) {
        Direction dir = static_cast<Direction>(d);

        if (dir == getOutputDirection()) continue; // skip output side

        for (Node* inputNode : grid->getAdjacentNodesInDirection(row, col, dir)) {
            addInputConnection(inputNode);
            inputNode->addOutputConnection(this);
        }
    }

    cout << "MergeNode placed at (" << row << ", " << col << ") with " << getInputConnections().size() << " inputs and " << getOutputConnections().size() << " outputs." << endl;
}

Node* MergeNode::clone() {
    return new MergeNode(*this);
}