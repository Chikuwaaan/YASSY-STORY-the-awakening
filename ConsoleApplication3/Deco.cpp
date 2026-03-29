#include "Deco.h"

Deco::Deco(double X, double Y, double W, double H, double Layer, std::string tex) {
    x = X;
    y = Y;
    w = W;
    h = H;
    layer = (int)Layer;
    texName = tex;
}