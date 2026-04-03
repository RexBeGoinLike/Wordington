#include <string>
#include "Direction.h"

using namespace std;
class IncomingData {
    private:
        string data;
        Direction direction;
    public:
        IncomingData(string data, Direction direction) : data(data), direction(direction) {}

        IncomingData() : data(""), direction(Direction::UP) {}
        string getData() {
            return data;
        }  

        Direction getDirection() {
            return direction;
        }

        void setData(string newData) {
            data = newData;
        }

        void setDirection(Direction newDirection) {
            direction = newDirection;
        }
        
    };