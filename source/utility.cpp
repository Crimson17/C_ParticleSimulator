#include "simulator.h"


int get_index(const kl::image& frame, const kl::int2& position)
{
	return static_cast<int>(position.y) * frame.width() + position.x;
}

bool is_in_frame(const kl::image& frame, const kl::int2& position)
{
	if (position.x >= 0 && position.x < static_cast<int>(frame.width()) && position.y >= 0 && position.y < static_cast<int>(frame.height())) {
		return true;
	}
	return false;
}
