#include "Node.h"
#include <algorithm>

Node::Node(int id, NodeType type, int capacity, int speed, Direction inputDir, Direction outputDir, int inputCount, int outputCount)
    : id(id), type(type), capacity(capacity), speed(speed), inputDirection(inputDir), outputDirection(outputDir), inputCount(inputCount), outputCount(outputCount) {}

Node::Node(Node* other)
    : id(other->id), type(other->type), capacity(other->capacity), speed(other->speed), inputDirection(other->inputDirection), outputDirection(other->outputDirection), inputCount(other->inputCount), outputCount(other->outputCount) {}

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

Direction Node::getInputDirection() {
    return inputDirection;
}

Direction Node::getOutputDirection() {
    return outputDirection;
}

void Node::setInputDirection(Direction dir) {
    inputDirection = dir;
}

void Node::setOutputDirection(Direction dir) {
    outputDirection = dir;
}

const vector<Node*>& Node::getInputConnections() {
    return inputConnections;
}

const vector<string>& Node::getDataBuffer() {
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

void Node::removeInputConnection(Node* node) {
    inputConnections.erase(remove(inputConnections.begin(), inputConnections.end(), node), inputConnections.end());
}

void Node::removeOutputConnection(Node* node) {
    outputConnections.erase(remove(outputConnections.begin(), outputConnections.end(), node), outputConnections.end());
}

bool Node::isFull() {
    return dataBuffer.size() >= capacity;
}


// Data Processing
void Node::receiveData(const string& data) {
    if (dataBuffer.size() < capacity) {
        dataBuffer.push_back(data);
    }
}

string Node::processData() {
    return "";
}

string Node::sendData() {
    return "";
}

void Node::onPlace(Grid *grid) {
    for (auto* node : grid->getAdjacentNodesInDirection(x, y, inputDirection)) {
        if(node->getOutputDirection() == inputDirection) {
            addInputConnection(node);
        }
    }
    
    for (auto* node : grid->getAdjacentNodesInDirection(x, y, outputDirection)) {
        if(node->getInputDirection() == outputDirection) {
            addOutputConnection(node);
        }
    }
}

void Node::update() {
    
}
