#include "ball.h"

#include <esat\math.h>

struct TBall{
    esat::Vec2 pos, prev_pos;
};

constexpr unsigned char kBallNumVertices = 4;