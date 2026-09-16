#include "game.h"

#include "paddle.h"
#include "ball.h"

void GAME::Init(){
    PDL::Init();
    BLL::Init();
}

void GAME::GetInput(){
    PDL::GetInput();
}

void GAME::Update(const double& dt, const double& game_clock){
    PDL::Update(dt);
    BLL::Update(dt);
}

void GAME::Draw(){
    PDL::Draw();
    BLL::Draw();
}

void GAME::Free(){
    PDL::Free();
    BLL::Free();
}