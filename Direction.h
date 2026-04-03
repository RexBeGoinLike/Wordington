#pragma once

enum Direction {
    DOWN,
    RIGHT,
    UP,
    LEFT
};

inline Direction getOppositeDirection(Direction dir) {
    switch(dir) {
        case Direction::UP:    return Direction::DOWN;
        case Direction::DOWN:  return Direction::UP;
        case Direction::LEFT:  return Direction::RIGHT;
        case Direction::RIGHT: return Direction::LEFT;
    }
    return Direction::UP;
}