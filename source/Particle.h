#pragma once

#include "KrimzLib.h"


class Particle {
public:
	// Material types
	enum class Material {
		None = 0,
		Sand,
		Water,
		Rock
	};

	Material material;
	bool updated;

	Particle();
	Particle(Material material);

	// Returns color
	static kl::color color(Material mat);
	kl::color color();
};
