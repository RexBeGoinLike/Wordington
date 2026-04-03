#include "LogisticNode.h"

void LogisticNode::update() {
    sendData();
}

Node* LogisticNode::clone() {
    return new LogisticNode(*this);
}

