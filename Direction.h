#pragma once

enum Direction {
    DOWN = 1 << 0,
    RIGHT = 1 << 1,
    UP = 1 << 2,
    LEFT = 1 << 3
};

inline int getOppositeDirection(int dirMask) {
    int result = 0;

    if (dirMask & UP)    result |= DOWN;
    if (dirMask & DOWN)  result |= UP;
    if (dirMask & LEFT)  result |= RIGHT;
    if (dirMask & RIGHT) result |= LEFT;

    return result;
}

inline int rotateClockwise(int dirMask) {
    int result = 0;
    if (dirMask & UP)    result |= RIGHT;
    if (dirMask & RIGHT) result |= DOWN;
    if (dirMask & DOWN)  result |= LEFT;
    if (dirMask & LEFT)  result |= UP;
    return result;
}

inline int rotateCounterClockwise(int dirMask) {
    int result = 0;
    if (dirMask & UP)    result |= LEFT;
    if (dirMask & LEFT)  result |= DOWN;
    if (dirMask & DOWN)  result |= RIGHT;
    if (dirMask & RIGHT) result |= UP;
    return result;
}