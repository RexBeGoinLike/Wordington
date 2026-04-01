#include "raylib.h"

class InputNode
{
public:
    InputNode() : color(GREEN), flag(0) {}
    InputNode(Color val) : color(val), flag(0) {}

    Color getColor() const { return color; }
    void setColor(Color col) { color = col; }
    int getFlag() const { return flag; }
    void setFlag(int f) { flag = f; }
private:
    Color color;
    int flag;
};