#ifndef GAME_H
#define GAME_H

namespace GAME{
    void Init();
    void GetInput();
    void Update(const double& dt, const double& game_clock);
    void Draw();
    void Free();
}

#endif