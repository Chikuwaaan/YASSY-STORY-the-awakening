#include "Particle.h"
#include "Textures.h"

Particle::Particle(double X, double Y, std::string Type) {
    x = X;
    y = Y;
    w = 6;
    h = 6;
    
    type = particle::assy;
    if (Type == "splash") type = particle::splash;
    if (Type == "mud") type = particle::mud;
    if (Type == "assy") type = particle::assy;

    if (type == particle::splash) {
        vector.push_back({ x, y, 0.5, 200, random.frandom(0,360) });
    }
    if (type == particle::mud) {
        vector.push_back({ x, y, 0.5, 100, random.frandom(0,360) });
    }
    if (type == particle::assy) {
        double j = random.frandom(0, 360);
        for (int i = 0; i < 4; i++) {
            j += random.frandom(70, 110);
            vector.push_back({ x, y, 0.4, 400, j});
        }
    }
}

void Particle::Update() {
    for (auto& p : vector) {
        p.x += cos(utilities::DegreetoRadian(p.angle)) * p.v * settings::timeScale;
        p.y += sin(utilities::DegreetoRadian(p.angle)) * p.v * settings::timeScale;
        if (timer.GetTime() > p.span) dead = 1;
    }
}

void Particle::Draw() {
    if (type == particle::splash) {
        for (auto& p : vector) {
            texturesP->DrawRect({ 0,0,255,255 }, { p.x, p.y, 6, 6, 1 }, 1);
        }
    }
    if (type == particle::mud) {
        for (auto& p : vector) {
            texturesP->DrawRect({ 80,50,0,255 }, { p.x, p.y, 12, 12, 1 }, 1);
        }
    }
    if (type == particle::assy) {
        for (auto& p : vector) {
            texturesP->DrawImage("assy", {p.x, p.y, 24, 24, 1}, 1, {});
        }
    }
}