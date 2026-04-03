#include "DuplicatorNode.h"
#include "Grid.h"
#include <iostream>

void DuplicatorNode::onPlace(int row, int col, Grid *grid){
    for (Node* inputNode : grid->getAdjacentNodesInDirection(row, col, getInputDirection())) {
        if(inputNode->getInputDirection() == getOppositeDirection(getInputDirection())) {
            addInputConnection(inputNode);
            inputNode->addOutputConnection(this);
        }
    }
    
    for (int d = 0; d < 4; d++) {
        Direction dir = static_cast<Direction>(d);

        if (dir == getInputDirection()) continue; // skip output side

        for (Node* inputNode : grid->getAdjacentNodesInDirection(row, col, dir)) {
            if(inputNode->getOutputDirection() == getOppositeDirection(getInputDirection())){
                addInputConnection(inputNode);
                inputNode->addOutputConnection(this);
            }
        }
    }
}

void DuplicatorNode::update(){
    sendData(getDataBuffer().empty() ? IncomingData() : getDataBuffer()[0]);
}

Node* DuplicatorNode::clone(){                  
    return new DuplicatorNode(*this);
}
