#include "Particle.h"


Particle::Particle() {
	material = Material::None;
	wasUpdated = false;
}

Particle::Particle(Material material) {
	this->material = material;
	wasUpdated = false;
}

// Returns color
kl::color Particle::color(Material mat) {
	switch (mat) {
	case Particle::Material::Sand:
		return kl::color(235, 215, 175);
		break;

	case Particle::Material::Water:
		return kl::color(25, 90, 220);
		break;

	case Particle::Material::Rock:
		return kl::color(60, 60, 90);
		break;

	default:
		return kl::colors::gray;
	}
}
kl::color Particle::color() {
	return Particle::color(this->material);
}
