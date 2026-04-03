#include "LogisticNode.h"


void LogisticNode::update() {
    sendData(getDataBuffer().empty() ? IncomingData() : getDataBuffer()[0]);
}

Node* LogisticNode::clone() {
    return new LogisticNode(*this);
}

