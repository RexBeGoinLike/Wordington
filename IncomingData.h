#include <string>
#include "Direction.h"

using namespace std;
class IncomingData {
    private:
        string data;
        int direction;
    public:
        IncomingData(string data, int direction) : data(data), direction(direction) {}

        IncomingData() : data(""), direction(Direction::UP) {}
        string getData() {
            return data;
        }  

        int getDirection() {
            return direction;
        }

        void setData(string newData) {
            data = newData;
        }

        void setDirection(Direction newDirection) {
            direction = newDirection;
        }
        
    };