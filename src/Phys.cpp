#include "Sim.h"


void SandPhys(const kl::int2& pos) {
    // Sand color check
    static const std::function<bool(const kl::int2&)> MatCheck = [](const kl::int2& p) {
        switch (particles[ToI(p)].material) {
        case Particle::Material::None:
        case Particle::Material::Water:
            return true;

        default:
            return false;
        }
    };

    // Getting the positions
    const kl::int2 posDown = pos + kl::int2(0, 1);
    const kl::int2 posDownL = pos + kl::int2(-1, 1);
    const kl::int2 posDownR = pos + kl::int2(1, 1);

    // Down
    if (pos.y < (frame.height() - 1) && MatCheck(posDown)) {
        std::swap(particles[ToI(pos)], particles[ToI(posDown)]);
    }

    // Down left
    else if (pos.y < (frame.height() - 1) && pos.x > 0 && MatCheck(posDownL)) {
        std::swap(particles[ToI(pos)], particles[ToI(posDownL)]);
    }

    // Down right
    else if (pos.y < (frame.height() - 1) && pos.x < (frame.width() - 1) && MatCheck(posDownR)) {
        std::swap(particles[ToI(pos)], particles[ToI(posDownR)]);
    }
}

void WaterPhys(const kl::int2& pos) {
    // Sand color check
    static const std::function<bool(const kl::int2&)> MatCheck = [](const kl::int2& p) {
        switch (particles[ToI(p)].material) {
        case Particle::Material::None:
            return true;

        default:
            return false;
        }
    };

    // Getting the positions
    const kl::int2 posDown = pos + kl::int2(0, 1);
    const kl::int2 posDownL = pos + kl::int2(-1, 1);
    const kl::int2 posDownR = pos + kl::int2(1, 1);
    const kl::int2 posLeft = pos + kl::int2(-1, 0);
    const kl::int2 posRight = pos + kl::int2(1, 0);

    // Down
    if (pos.y < (frame.height() - 1) && MatCheck(posDown)) {
        std::swap(particles[ToI(pos)], particles[ToI(posDown)]);
    }

    // Down left
    else if (pos.y < (frame.height() - 1) && pos.x > 0 && MatCheck(posDownL)) {
        std::swap(particles[ToI(pos)], particles[ToI(posDownL)]);
    }

    // Down right
    else if (pos.y < (frame.height() - 1) && pos.x < (frame.width() - 1) && MatCheck(posDownR)) {
        std::swap(particles[ToI(pos)], particles[ToI(posDownR)]);
    }

    // Left
    else if (pos.x > 0 && MatCheck(posLeft)) {
        std::swap(particles[ToI(pos)], particles[ToI(posLeft)]);
    }

    // Right
    else if (pos.x < (frame.width() - 1) && MatCheck(posRight)) {
        std::swap(particles[ToI(pos)], particles[ToI(posRight)]);
    }
}

void RockPhys(const kl::int2& pos) {

}

void MaterialPhys(const kl::int2& pos) {
    const int index = ToI(pos);
    if (!particles[index].updated) {
        switch (particles[index].material) {
        case Particle::Material::Sand:
            SandPhys(pos);
            break;

        case Particle::Material::Water:
            WaterPhys(pos);
            break;

        case Particle::Material::Rock:
            RockPhys(pos);
            break;
        }
        particles[index].updated = true;
    }
}

void Phys() {
    bool leftToRight = kl::random::BOOL();
    for (kl::int2 pos = frame.height() - 1; pos.y >= 0; pos.y--) {
        if (leftToRight) {
            for (pos.x = 0; pos.x < frame.width(); pos.x++) {
                MaterialPhys(pos);
            }
        }
        else {
            for (pos.x = frame.width() - 1; pos.x >= 0; pos.x--) {
                MaterialPhys(pos);
            }
        }
        leftToRight = !leftToRight;
    }
}
