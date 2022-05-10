#include "Particle.h"


Particle::Particle() {
	material = Material::None;
	updated = false;
}

Particle::Particle(Material material) {
	this->material = material;
	updated = false;
}

// Returns color
kl::color Particle::color(Material mat) {
	switch (mat) {
	case Particle::Material::Sand:
		return kl::colors::wheat;
		break;

	case Particle::Material::Water:
		return kl::colors::cyan;
		break;

	case Particle::Material::Rock:
		return kl::colors::lgray;
		break;

	default:
		return kl::colors::gray;
	}
}
kl::color Particle::color() {
	return Particle::color(this->material);
}
