#include "MergeNode.h"
#include "Grid.h"
#include <iostream>
#include <algorithm>

IncomingData MergeNode::processData() {
    string mergedData;
    
    std::sort(getDataBuffer().begin(), getDataBuffer().end(), [](IncomingData& a, IncomingData& b) {
        return static_cast<int>(a.getDirection()) < static_cast<int>(b.getDirection());
    });

    for (IncomingData& data : getDataBuffer()) {
        mergedData += data.getData();
    }
    return IncomingData(mergedData, getOutputDirection());
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
}

Node* MergeNode::clone() {
    return new MergeNode(*this);
}