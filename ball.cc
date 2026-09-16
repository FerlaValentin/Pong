#include "ball.h"

#include <stdio.h>
#include <stdlib.h>

#include <esat\math.h>
#include <esat\draw.h>

#include "config.h"
#include "game_utils.h"
struct TBall{
    esat::Vec2 pos, prev_pos, fwd;
};

static constexpr unsigned char kBallSide = 3;

static TBall* g_ball = nullptr;

static esat::Vec2 GetValidFwd(){
    esat::Vec2 tmp;

    do{
        tmp = {(float)(rand()%3 - 1), (float)(rand()%3 - 1)};
    }while(UTL::GetMagnitude(tmp) == 0.0f);

    return tmp;
}

void BLL::Init(){
    g_ball = (TBall*)malloc(sizeof(TBall));
    g_ball->pos = {CFG::kScreenX / 5 * 2, CFG::kScreenY / 2};
    g_ball->prev_pos = g_ball->pos;
    g_ball->fwd = GetValidFwd();
}

static void UpdatePrevPos(){
    g_ball->prev_pos = g_ball->pos;
}

static void Move(const double& dt){
    constexpr unsigned char BALL_SPEED = 255;

    g_ball->pos.x += g_ball->fwd.x * BALL_SPEED * dt;
    g_ball->pos.y += g_ball->fwd.y * BALL_SPEED * dt;
}

static bool HasCollidedAWall(float ball_Y_pos){
    bool has_collided_top = ball_Y_pos - kBallSide/2.0f <= 0
        ,has_collided_bottom = ball_Y_pos + kBallSide/2.0f >= CFG::kScreenY;

    return has_collided_top || has_collided_bottom;
}

static void Bounce(){
    if(HasCollidedAWall(g_ball->pos.y))    g_ball->pos.y *= -1;
}

void BLL::Update(const double& dt){
    UpdatePrevPos();
    Move(dt);
    Bounce();
}

static void FillPoints(const esat::Vec2& ball_center, esat::Vec2 points[4]){
    points[0] = {ball_center.x - kBallSide, ball_center.y - kBallSide};
    points[1] = {ball_center.x + kBallSide, ball_center.y - kBallSide};
    points[2] = {ball_center.x + kBallSide, ball_center.y + kBallSide};
    points[3] = {ball_center.x - kBallSide, ball_center.y + kBallSide};
}

static void DrawBall(){
    esat::Vec2 ball_points[4];

    FillPoints(g_ball->pos, ball_points);
    esat::DrawSolidPath(&ball_points->x, 4);
    FillPoints(g_ball->prev_pos, ball_points);
    esat::DrawSolidPath(&ball_points->x, 4);
    
}

void BLL::Draw(){
    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(255,255,255,0);
    DrawBall();
}

static void FreeBall(){
    free(g_ball);
    g_ball = nullptr;
}

void BLL::Free(){
    FreeBall();
}