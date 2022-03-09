#include "Sim.h"


int main() {
	kl::timer timer;
	win.start = [&]() {
		timer.reset();
		timer.interval();
		particles.resize(size_t(frame.width()) * frame.height());
	};
	win.update = [&]() {
		// Time
		deltaT = timer.interval();
		elapsedT = timer.elapsed();

		// Input
		Input();

		// Physics
		Phys();

		// Drawing
		Draw();

		// Frame display
		win.drawImage(frame);

		// Title
		win.setTitle("FPS: " + std::to_string(int(1 / deltaT)) + " Brush size: " + std::to_string(brushSize));
	};
	win.startNew(frame.size(), "Particle Sim", false, true);
}
