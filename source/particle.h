#pragma once

#include "klib.h"


enum class material
{
	none = 0,
	sand,
	water,
	rock
};

class particle
{
public:
	material material = ::material::none;
	bool updated = false;

	particle();
	explicit particle(::material material);
	
	kl::color color() const;
	static kl::color color(::material material);
};
