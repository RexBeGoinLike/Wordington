#include "SourceNode.h"
#include "Grid.h"
#include <iostream>
#include <algorithm>
#include <cctype>  

IncomingData SourceNode::processData(){
   string data(1, this->data);
   std::transform(data.begin(), data.end(), data.begin(), ::toupper);
   return IncomingData(data, getOutputDirection());
}

void SourceNode::update(){
    sendData(processData());
}

Node* SourceNode::clone(){                  
    return new SourceNode(*this);
}

void SourceNode::onPlace(Grid *grid){

    for (Node* outputNode : grid->getAdjacentNodesInDirection(getRow(), getCol(), getOutputDirection())) {
        int expectedInputMask = getOppositeDirection(getOutputDirection());

        if (outputNode->getInputDirection() & expectedInputMask) {
            addOutputConnection(outputNode);
            outputNode->addInputConnection(this);
        }
    }
}

void SourceNode::setData(char newData) {
    data = newData;
}

