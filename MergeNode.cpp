#include "MergeNode.h"
#include "Grid.h"
#include <iostream>
#include <algorithm>

IncomingData MergeNode::processData() {
    string mergedData;
    
    std::sort(getDataBuffer().begin(), getDataBuffer().end(), [](IncomingData& a, IncomingData& b) {
        return static_cast<int>(a.getDirection()) < static_cast<int>(b.getDirection());
    });

    for (IncomingData& data : getDataBuffer()) {
        mergedData += data.getData();
    }
    return IncomingData(mergedData, getOutputDirection());
}

void MergeNode::update() {
    sendData(processData());
}

Node* MergeNode::clone() {
    return new MergeNode(*this);
}