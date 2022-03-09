#pragma once

#include "KrimzLib/KrimzLib.hpp"

#include "Particle.h"


// Window
inline kl::window win;

// Buffers
inline kl::image frame(kl::int2(900));
inline std::vector<Particle> particles;

// Time
inline float deltaT = 0.0f;
inline float elapsedT = 0.0f;

// Brush
inline int brushSize = 25;
inline Particle::Material selectedMat = Particle::Material::Sand;

// Callbacks
void Input();
void Phys();
void Draw();
