#include "Sim.h"


void Draw() {
	// Particle draw
	for (kl::int2 pos = 0; pos.y < frame.height(); pos.y++) {
		for (pos.x = 0; pos.x < frame.width(); pos.x++) {
			frame.spixel(pos, particles[size_t(pos.y * frame.width() + pos.x)].color());
		}
	}

	// Cirlce draw
	frame.drawCircle(win.mouse.position, float(brushSize), Particle::color(selectedMat));
}
