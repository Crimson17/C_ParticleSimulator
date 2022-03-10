#include "Sim.h"


void Draw() {
	// Particle draw
	for (kl::int2 pos = 0; pos.y < frame.height(); pos.y++) {
		for (pos.x = 0; pos.x < frame.width(); pos.x++) {
			// Pixel draw
			frame.spixel(pos, particles[ToI(pos)].color());

			// Update clear
			particles[ToI(pos)].updated = false;
		}
	}

	// Cirlce draw
	frame.drawCircle(win.mouse.position, float(brushSize), Particle::color(selectedMat));
}
