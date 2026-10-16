#ifndef GALAGA_H
#define GALAGA_H

#include "GameObject.h"
#include "MathUtil.h"

class Galaga : public CMPUT350::GameObject {
public:
    Galaga(int width, int height) : windowSize{float(width), float(height)} {}

    void Initialize(CMPUT350::GameContext *context) override;
    void Update(CMPUT350::GameContext *context) override;
    void LateUpdate(CMPUT350::GameContext *context) override;
    bool IsAlive() const override;
    void Kill() override {};

private:
    CMPUT350::Point2D windowSize;
    bool alive = true;
};
#endif  // GALAGA_H
