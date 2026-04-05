#include "IntersectionNode.h"
#include "Grid.h"
#include "Direction.h"
#include <iostream>


void IntersectionNode::sendData(IncomingData data){
    for(Node* outputNode : getOutputConnections()) {
        std::vector<Node*> oppositeNode = grid->getAdjacentNodesInDirection(getRow(), getCol(), data.getDirection());
        cout << (Direction) data.getDirection();
        if (!oppositeNode.empty() && outputNode == oppositeNode[0]) {
            if(!outputNode->isFull()){
                outputNode->receiveData(data);
            }
        }
    }   
}

void IntersectionNode::update() {
    for(IncomingData data : getDataBuffer()){
        sendData(data);
    }
}

Node* IntersectionNode::clone() {
    return new IntersectionNode(*this);
}

