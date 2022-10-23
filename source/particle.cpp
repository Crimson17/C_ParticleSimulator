#include "particle.h"


particle::particle()
{}

particle::particle(const ::material material)
	: material(material)
{}

kl::color particle::color() const
{
	return color(material);
}

kl::color particle::color(const ::material material) {
	switch (material) {
	case material::sand:
		return kl::colors::wheat;

	case material::water:
		return kl::colors::cyan;

	case material::rock:
		return {150, 150, 150};
	
	default:
		return kl::colors::gray;
	}
}
