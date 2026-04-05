#include "Node.h"
#include "Grid.h"
#include <algorithm>
#include <iostream>

Node::Node(int id, NodeType type, int capacity, int speed, int inputDir, int outputDir, int inputCount, int outputCount, int row, int col)
    : id(id), type(type), capacity(capacity), speed(speed), inputDirection(inputDir), outputDirection(outputDir), inputCount(inputCount), outputCount(outputCount), row(row), col(col) {}

Node* Node::clone(){
    return new Node(*this);
}

//Getters and Setters
int Node::getId() {
    return id;
}

NodeType Node::getType() {
    return type;
}

void Node::setType(NodeType newType) {
    type = newType;
}

int Node::getCapacity() {
    return capacity;
}

int Node::getSpeed() {
    return speed;
}

int Node::getInputCount() {
    return inputCount;
}

int Node::getOutputCount() {
    return outputCount;
}

int Node::getInputDirection() {
    return inputDirection;
}

int Node::getOutputDirection() {
    return outputDirection;
}

void Node::setInputDirection(int dir) {
    inputDirection = dir;
}

void Node::setOutputDirection(int dir) {
    outputDirection = dir;
}

vector<Node*>& Node::getInputConnections() {
    return inputConnections;
}

vector<Node*>& Node::getOutputConnections() {
    return outputConnections;
}

vector<IncomingData>& Node::getDataBuffer() {
    return dataBuffer;
}

void Node::addInputConnection(Node* node) {
    if(inputConnections.size() < inputCount) {
        inputConnections.push_back(node);
    }   
}

void Node::addOutputConnection(Node* node) {
    if(outputConnections.size() < outputCount) {
        outputConnections.push_back(node);
    }
}

int Node::getRow() {
    return row;
}

int Node::getCol() {
    return col;
}

void Node::setRow(int row) {
    this->row = row;
}

void Node::setCol(int col) {
    this->col = col;
}

void Node::removeInputConnection(Node* node) {
    inputConnections.erase(remove(inputConnections.begin(), inputConnections.end(), node), inputConnections.end());
}

void Node::removeOutputConnection(Node* node) {
    outputConnections.erase(remove(outputConnections.begin(), outputConnections.end(), node), outputConnections.end());
}

void Node::clearDataBuffer() {
    dataBuffer.clear();
}

bool Node::isFull() {
    return dataBuffer.size() >= capacity;
}


void Node::receiveData(IncomingData& data) {

    for (IncomingData& existing : dataBuffer) {
        if (existing.getDirection() == data.getDirection()) {
            return; 
        }
    }

    
    if (dataBuffer.size() < capacity) {
        dataBuffer.push_back(data);
    }
}

IncomingData Node::processData() {
    return IncomingData();
}

void Node::sendData(IncomingData data) {
    for(Node* outputNode : outputConnections) {
        if(!outputNode->isFull()){
            outputNode->receiveData(data);
            clearDataBuffer();
        }
    }   
}

void Node::onPlace(Grid *grid) {
    for (Node* outputNode : grid->getAdjacentNodesInDirection(row, col, getOutputDirection())) {
        int expectedInputMask = getOppositeDirection(getOutputDirection());

        if (outputNode->getInputDirection() & expectedInputMask) {
            addOutputConnection(outputNode);
            outputNode->addInputConnection(this);
        }
    }


    for (Node* inputNode : grid->getAdjacentNodesInDirection(row, col, getInputDirection())) {
        int expectedOutputMask = getOppositeDirection(getInputDirection());

        if (inputNode->getOutputDirection() & expectedOutputMask) {
            addInputConnection(inputNode);
            inputNode->addOutputConnection(this);
        }
    }
}

void Node::update() {
    
}
