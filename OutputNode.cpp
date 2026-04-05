#include "OutputNode.h"
#include "Grid.h"
#include <iostream>
#include <algorithm>
#include <cctype>  

void OutputNode::update(){
    getDataBuffer().clear();
}

Node* OutputNode::clone(){                  
    return new OutputNode(*this);
}

void OutputNode::onPlace(Grid *grid){

    for (Node* inputNode : grid->getAdjacentNodesInDirection(getRow(), getCol(), getInputDirection())) {
        int expectedInputMask = getOppositeDirection(getInputDirection());

        if (inputNode->getInputDirection() & expectedInputMask) {
            addOutputConnection(inputNode);
            inputNode->addInputConnection(this);
        }
    }
}

void OutputNode::setText(string *requiredText) {
    this->requiredText = requiredText;
}

