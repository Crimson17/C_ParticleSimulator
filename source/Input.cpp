#include "Sim.h"


void FillCircle(const kl::int2& pos, const Particle::Material& mat) {
    for (kl::int2 pxl = int(pos.y - brushSize); pxl.y <= int(pos.y + brushSize); pxl.y++) {
        const int xVal = int(pos.x + sqrt(brushSize * brushSize - float(pxl.y - pos.y) * float(pxl.y - pos.y)));

        int leftX = 2 * pos.x - xVal;
        int rightX = xVal;
        if (rightX < leftX) {
            std::swap(leftX, rightX);
        }

        for (pxl.x = leftX; pxl.x <= rightX; pxl.x++) {
            if (InFrame(pxl)) {
                particles[ToI(pxl)].material = mat;
            }
        }
    }
}

void Input() {
    // Material select
    if (win.keys.num1) selectedMat = Particle::Material::Sand;
    if (win.keys.num2) selectedMat = Particle::Material::Water;
    if (win.keys.num3) selectedMat = Particle::Material::Rock;

    // Brush size
    static int lastSize = 0;
    const int scrollDelta = win.mouse.scroll - lastSize;
    if (brushSize + scrollDelta > 0) {
        brushSize += scrollDelta;
    }
    lastSize = win.mouse.scroll;

    // Brush draw
    if (win.mouse.lmb && InFrame(win.mouse.position)) {
        FillCircle(win.mouse.position, selectedMat);
    }

    // Brush erase
    if (win.mouse.rmb && InFrame(win.mouse.position)) {
        FillCircle(win.mouse.position, Particle::Material::None);
    }

    // Buffer clear
    if (win.keys.r) {
        for (Particle& p : particles) {
            p.material = Particle::Material::None;
        }
    }
}
