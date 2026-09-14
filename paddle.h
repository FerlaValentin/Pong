#ifndef PADDLE_H
#define PADDLE_H

namespace PDL{
    void Init();
    void GetInput();
    void Update(const double& dt);
    void Draw();
    void Free();
}

#endif