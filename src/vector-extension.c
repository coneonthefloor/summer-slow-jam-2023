//
// Created by brian on 15/06/2023.
//

#include <math.h>
#include "vector-extension.h"

Vector2 MoveTowards(Vector2 current, Vector2 target, float maxDistanceDelta) {
    float toVector_x = target.x - current.x;
    float toVector_y = target.y - current.y;

    double sqDist = toVector_x * toVector_x + toVector_y * toVector_y;

    if (sqDist == 0 || (maxDistanceDelta >= 0 &&
                        sqDist <= maxDistanceDelta * maxDistanceDelta))
        return target;

    float dist = (float) sqrt(sqDist);
    float x = current.x + toVector_x / dist * maxDistanceDelta;
    float y = current.y + toVector_y / dist * maxDistanceDelta;
    Vector2 new_position = {.x = x, .y = y};
    return new_position;
}