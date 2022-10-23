#include "simulator.h"


int main()
{
	kl::window window = { kl::uint2(800, 800), "Particle simulator" };
	auto frame = kl::image(window.size());
	std::vector<particle> particles = {};
	kl::timer timer = {};
	
	window.set_icon("resource/sand.ico");
	window.mouse.set_hidden(true);
	particles.resize(static_cast<uint64_t>(frame.width()) * frame.height());
	
	timer.reset();
	while (window.process(false)) {
		timer.update_interval();

		input(window, frame, particles);
		physics(frame, particles);
		draw(frame, particles, window.mouse.position());
		
		window.draw_image(frame);
		window.set_title(kl::format("FPS: ", static_cast<int>(1 / timer.get_interval()), " Brush size: ", brush_size));
	}
}
