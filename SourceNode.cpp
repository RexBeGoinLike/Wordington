#include "SourceNode.h"
#include "Grid.h"

string SourceNode::processData(){
   string data = "A";
   return data;
}

void SourceNode::update(){
    sendData(processData());
}

Node* SourceNode::clone(){                  
    return new SourceNode(*this);
}

void SourceNode::onPlace(int row, int col, Grid *grid){

    for(Node* outputNode : grid->getAdjacentNodesInDirection(row, col, getOutputDirection())) {
        addOutputConnection(outputNode);
        outputNode->addInputConnection(this);
    }
}