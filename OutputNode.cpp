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

void OutputNode::receiveData(IncomingData& data){
    if(data.getData() == *requiredText)
        *requiredText = reader->getRandomSentence();
}

void OutputNode::onPlace(Grid *grid){

    for (Node* inputNode : grid->getAdjacentNodesInDirection(getRow(), getCol(), getInputDirection())) {
        int expectedInputMask = getOppositeDirection(getInputDirection());

        if (inputNode->getOutputDirection() & expectedInputMask) {
            addInputConnection(inputNode);
            inputNode->addOutputConnection(this);
        }
    }
}

void OutputNode::setText(string *requiredText) {
    this->requiredText = requiredText;
}

string* OutputNode::getText(){
    return requiredText;
}

