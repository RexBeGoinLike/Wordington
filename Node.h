#pragma once

#include "Direction.h"
#include "NodeType.h" 
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

    Direction inputDirection;
    Direction outputDirection;
    vector<Node*> inputConnections;
    vector<Node*> outputConnections;


    vector<string> dataBuffer;
    int x, y;

public:
    Node(int id, NodeType type, int capacity, int speed, Direction inputDir, Direction outputDir, int inputCount, int outputCount);
    virtual Node* clone();

    int getId();
    NodeType getType();
    void setType(NodeType newType);
    int getCapacity();
    int getSpeed();

    int getInputCount();
    int getOutputCount();

    Direction getInputDirection();
    Direction getOutputDirection();
    void setInputDirection(Direction dir);
    void setOutputDirection(Direction dir);

    const vector<Node*>& getInputConnections();
    const vector<Node*>& getOutputConnections();
    const vector<string>& getDataBuffer();
    
    void addInputConnection(Node* node);
    void addOutputConnection(Node* node);
    void removeInputConnection(Node* node);
    void removeOutputConnection(Node* node);


    void receiveData(const string& data);
    virtual void processData();
    void sendData();

    virtual void update();
    void onPlace(int row, int col, Grid *grid);
    
    bool isFull();


};
