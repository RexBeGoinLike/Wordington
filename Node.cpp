#include "Node.h"
#include <algorithm>

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

void Node::receiveData(const string& data) {
    if (dataBuffer.size() < capacity) {
        dataBuffer.push_back(data);
    }
}

bool Node::isFull() {
    return dataBuffer.size() >= capacity;
}


// Data Processing
string Node::processData() {
    return "";
}

string Node::sendData() {
    return "";
}



void Node::update() {
    
}
