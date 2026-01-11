#include "Spikes.h"
#include "Level.h"

Spikes::Spikes(double x0, double y0, int direction, int length) {
    x = x0;
    y = y0;
    w = length * levelP->GetBlockSize();
    h = 80;
}