#pragma once;
#include <vector>

enum ParamType { InitialRotation, InitialTranslation, InitialColor, Rotation, Translation, Color, FactorRotation, FactorTranslation, FactorColor };

struct Cube {
    std::vector<float>params = std::vector<float>(27, 0.0f);
};