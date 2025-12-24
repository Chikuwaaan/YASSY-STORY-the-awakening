#include "Zako.h"

Zako::Zako() {
    type = entityType::Zako;
    x = 1000;
    y = 300;
}

void Zako::Update() {

}

void Zako::Damage() {
    dead = 1;
}