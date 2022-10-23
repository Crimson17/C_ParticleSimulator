#pragma once

#include "particle.h"


inline int brush_size = 25;
inline material selected_material = material::sand;

int get_index(const kl::image& frame, const kl::int2& position);
bool is_in_frame(const kl::image& frame, const kl::int2& position);

void input(kl::window& window, const kl::image& frame, std::vector<particle>& particles);
void physics(const kl::image& frame, std::vector<particle>& particles);
void draw(kl::image& frame, std::vector<particle>& particles, const kl::int2& mouse_position);
