#include "Sim.h"


void Input() {
    // Material select
    if (win.keys.num1) selectedMat = Particle::Material::Sand;
    if (win.keys.num2) selectedMat = Particle::Material::Water;
    if (win.keys.num3) selectedMat = Particle::Material::Rock;

    // Brush draw
    if (win.mouse.lmb) {
        particles[size_t(win.mouse.position.y * frame.width() + win.mouse.position.x)].material = selectedMat;
    }

    // Brush erase
    if (win.mouse.rmb) {
        particles[size_t(win.mouse.position.y * frame.width() + win.mouse.position.x)].material = Particle::Material::None;
    }

    // Buffer clear
    if (win.keys.r) {
        for (Particle& p : particles) {
            p.material = Particle::Material::None;
        }
    }
}
