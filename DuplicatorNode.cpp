#include "DuplicatorNode.h"
#include "Grid.h"
#include <iostream>


void DuplicatorNode::sendData(IncomingData data){
    for(Node* outputNode : getOutputConnections()) {
        Direction dir = UP;
            std::vector<Node*> upNodes = grid->getAdjacentNodesInDirection(getRow(), getCol(), UP);
            if (!upNodes.empty() && outputNode == upNodes[0]) {
                dir = UP;
            }

            std::vector<Node*> downNodes = grid->getAdjacentNodesInDirection(getRow(), getCol(), DOWN);
            if (!downNodes.empty() && outputNode == downNodes[0]) {
                dir = DOWN;
            }

            std::vector<Node*> leftNodes = grid->getAdjacentNodesInDirection(getRow(), getCol(), LEFT);
            if (!leftNodes.empty() && outputNode == leftNodes[0]) {
                dir = LEFT;
            }

            std::vector<Node*> rightNodes = grid->getAdjacentNodesInDirection(getRow(), getCol(), RIGHT);
            if (!rightNodes.empty() && outputNode == rightNodes[0]) {
                dir = RIGHT;
            }
        
        data.setDirection(dir);     
        
        if(!outputNode->isFull()){
            outputNode->receiveData(data);
            clearDataBuffer();
        }
    }   
}

void DuplicatorNode::update(){
    sendData(getDataBuffer().empty() ? IncomingData() : getDataBuffer()[0]);
}

Node* DuplicatorNode::clone(){                  
    return new DuplicatorNode(*this);
}
