#pragma once

#include "KrimzLib/KrimzLib.hpp"


class Particle {
public:
	// Material types
	enum class Material {
		None = 0,
		Sand,
		Water,
		Rock
	};

public:
	Material material;
	kl::float2 velocity;
	bool wasUpdated;

	Particle();
	Particle(Material material);

	// Returns color
	static kl::color color(Material mat);
	kl::color color();
};
