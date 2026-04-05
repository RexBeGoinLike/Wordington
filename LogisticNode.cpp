#include "LogisticNode.h"
#include "Grid.h"
#include <iostream>


void LogisticNode::update() {
    IncomingData data = getDataBuffer().empty() ? IncomingData() : getDataBuffer()[0];
    data.setDirection((Direction) getOutputDirection());
    sendData(data);
}

Node* LogisticNode::clone() {
    return new LogisticNode(*this);
}

void LogisticNode::onPlace(Grid *grid) {
    bool hasStraightConnection = false;

    for (Node* outputNode : grid->getAdjacentNodesInDirection(getRow(), getCol(), getOutputDirection())) {
        int expectedInputMask = getOppositeDirection(getOutputDirection());

        if (outputNode->getInputDirection() & expectedInputMask) {
            addOutputConnection(outputNode);
            outputNode->addInputConnection(this);
            hasStraightConnection = true;
        }
    }

        for (Node* inputNode : grid->getAdjacentNodesInDirection(getRow(), getCol(), getInputDirection())) {
        int expectedOutputMask = getOppositeDirection(getInputDirection());

        if (inputNode->getOutputDirection() & expectedOutputMask) {
            addInputConnection(inputNode);
            inputNode->addOutputConnection(this);
        }
    }

    cout << "Has Straight Connection: " << hasStraightConnection << endl;

    if (!hasStraightConnection) {
        int leftDir = rotateCounterClockwise(getOutputDirection());
        int rightDir = rotateClockwise(getOutputDirection());

        
        for (Node* node : grid->getAdjacentNodesInDirection(getRow(), getCol(), leftDir)) {
            if (node->getInputDirection() & getOppositeDirection(leftDir)) {
                setType(CORNERLOG);
                setOutputDirection(leftDir);

                addOutputConnection(node);
                node->addInputConnection(this);
                return;
            }
        }

        
        for (Node* node : grid->getAdjacentNodesInDirection(getRow(), getCol(), rightDir)) {
            if (node->getInputDirection() & getOppositeDirection(rightDir)) {
                setType(CORNERLOG);
                setOutputDirection(rightDir);

                addOutputConnection(node);
                node->addInputConnection(this);
                return;
            }
        }
    }
}

