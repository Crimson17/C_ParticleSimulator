#include "Sim.h"


int ToI(const kl::int2& pos) {
	return pos.y * frame.width() + pos.x;
}

bool InFrame(const kl::int2& pos) {
	if (pos.x >= 0 && pos.x < frame.width() && pos.y >= 0 && pos.y < frame.height()) {
		return true;
	}
	return false;
}
