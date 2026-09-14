#include "paddle.h"

#include <stdio.h>
#include <stdlib.h>

#include <esat\math.h>
#include <esat\input.h>
#include <esat\draw.h>

#include "config.h"

struct TPaddle{
    bool is_player_one, is_going_up, is_moving;
    esat::Vec2 pos ;
};

static constexpr unsigned char kNumOfPlayers = 2, kPaddleHeight = 20;

static TPaddle* g_paddles = nullptr;

static void InitPaddle(TPaddle* const paddle, bool is_player_one, esat::Vec2 paddle_pos){
    (*paddle).is_player_one = is_player_one;
    (*paddle).is_going_up = false;
    (*paddle).is_moving = false;
    (*paddle).pos = paddle_pos;
}

void PDL::Init(){
    g_paddles = (TPaddle*)malloc(sizeof(TPaddle) * kNumOfPlayers);
    InitPaddle(g_paddles, true, {CFG::kScreenX / 4.0f, CFG::kScreenY / 2.0f});
    InitPaddle(g_paddles + 1, false, {CFG::kScreenX / 4.0f * 3, CFG::kScreenY / 2.0f});
}

void PDL::GetInput(){
    (*g_paddles).is_going_up = esat::IsKeyPressed('w') || esat::IsKeyPressed('W');
    (*g_paddles).is_moving = esat::IsKeyPressed('s') || esat::IsKeyPressed('S') || (*g_paddles).is_going_up;
    (*(g_paddles + 1)).is_going_up = esat::IsSpecialKeyPressed(esat::SpecialKey::kSpecialKey_Up);
    (*(g_paddles + 1)).is_moving = esat::IsSpecialKeyPressed(esat::SpecialKey::kSpecialKey_Down) || (*(g_paddles + 1)).is_going_up;
}

static bool IsMovementValid(float y_pos, bool is_going_up){
    bool doesnt_cross_limit = is_going_up ? y_pos - kPaddleHeight/2 >= 0 : y_pos + kPaddleHeight/2 <= CFG::kScreenY;

    return doesnt_cross_limit;
}

static void MovePaddle(TPaddle* const paddle, const double& dt){
    const unsigned char PADDLE_SPEED = 255;

    (*paddle).pos.y += (*paddle).is_going_up ? -PADDLE_SPEED * dt : PADDLE_SPEED * dt; 
}

static void CheckMovement(TPaddle* const paddle, const double& dt){
    if((*paddle).is_moving && IsMovementValid(paddle->pos.y, paddle->is_going_up)) MovePaddle(paddle, dt);
}

void PDL::Update(const double& dt){
    for(int i = 0; i < kNumOfPlayers; ++i){
        CheckMovement(g_paddles + i, dt);
    }
}

static void FillRectanglePoints(esat::Vec2 rect[4], const esat::Vec2& center){
    constexpr unsigned char PADDLE_WIDTH = 7;
    
    rect[0] = {center.x - PADDLE_WIDTH / 2.0f, center.y - kPaddleHeight / 2.0f};
    rect[1] = {center.x + PADDLE_WIDTH / 2.0f, center.y - kPaddleHeight / 2.0f};
    rect[2] = {center.x + PADDLE_WIDTH / 2.0f, center.y + kPaddleHeight / 2.0f};
    rect[3] = {center.x - PADDLE_WIDTH / 2.0f, center.y + kPaddleHeight / 2.0f};
}

static void DrawPaddle(const esat::Vec2& paddle_pos){
    esat::Vec2 rect_points[4];
    
    FillRectanglePoints(rect_points, paddle_pos);
    esat::DrawSetFillColor(255,255,255);
    esat::DrawSolidPath(&rect_points->x, 4);
}

void PDL::Draw(){
    for(int i = 0; i < kNumOfPlayers; ++i)
        DrawPaddle((g_paddles + i)->pos);
}

static void FreePaddles(){
    free(g_paddles);
    g_paddles = nullptr;
}

void PDL::Free(){
    FreePaddles();
}