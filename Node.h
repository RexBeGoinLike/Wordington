#pragma once

#include "Direction.h"
#include "NodeType.h" 
#include "IncomingData.h"
#include <vector>
#include <string>

using namespace std;

class Grid;

class Node
{
private:
    int id;
    int inputCount;
    int outputCount;
    int capacity;
    int speed;

    NodeType type;

    int inputDirection;
    int outputDirection;
    vector<Node*> inputConnections;
    vector<Node*> outputConnections;


    vector<IncomingData> dataBuffer;
    int x, y;

public:
    Node(int id, NodeType type, int capacity, int speed, int inputDir, int outputDir, int inputCount, int outputCount);
    virtual Node* clone();

    int getId();
    NodeType getType();
    void setType(NodeType newType);
    int getCapacity();
    int getSpeed();

    int getInputCount();
    int getOutputCount();

    int getInputDirection();
    int getOutputDirection();
    void setInputDirection(int dir);
    void setOutputDirection(int dir);

    vector<Node*>& getInputConnections();
    vector<Node*>& getOutputConnections();
    vector<IncomingData>& getDataBuffer();
    
    void addInputConnection(Node* node);
    void addOutputConnection(Node* node);
    void removeInputConnection(Node* node);
    void removeOutputConnection(Node* node);
    void clearDataBuffer();

    void receiveData(const IncomingData& data);
    virtual IncomingData processData();
    void sendData(IncomingData data = IncomingData());

    virtual void update();
    virtual void onPlace(int row, int col, Grid *grid);
    
    bool isFull();
};
