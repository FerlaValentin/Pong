#include "game.h"

#include "paddle.h"

void GAME::Init(){
    PDL::Init();
}

void GAME::GetInput(){
    PDL::GetInput();
}

void GAME::Update(const double& dt, const double& game_clock){
    PDL::Update(dt);
}

void GAME::Draw(){
    PDL::Draw();
}

void GAME::Free(){
    PDL::Free();
}