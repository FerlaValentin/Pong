#include "game_utils.h"

#include <math.h>

#include <esat\math.h>

float UTL::GetMagnitude(const esat::Vec2& vec){
    return sqrtf(vec.x * vec.x + vec.y * vec.y);
}