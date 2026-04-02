#include "SourceNode.h"

void SourceNode::processData(){
   string data = "give me dat clit baby";
   receiveData(data);
}

void SourceNode::update(){
    processData();
    sendData();
}


