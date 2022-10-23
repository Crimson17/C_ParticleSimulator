#include "simulator.h"


void draw(kl::image& frame, std::vector<particle>& particles, const kl::int2& mouse_position)
{
	for (kl::uint2 position; position.y < frame.height(); position.y++) {
		for (position.x = 0; position.x < frame.width(); position.x++) {
			const int index = get_index(frame, kl::int2(position));
			frame.set_pixel(position, particles[index].color());
			particles[index].updated = false;
		}
	}
	
	frame.draw_circle(mouse_position, static_cast<float>(brush_size), particle::color(selected_material));
}
