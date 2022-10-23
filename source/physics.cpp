#include "simulator.h"


static void sand_physics(const kl::image& frame, std::vector<particle>& particles, const kl::int2& position)
{
    const std::function material_check = [&](const kl::int2& p) {
        switch (particles[get_index(frame, p)].material) {
        case material::none:
        case material::water:
            return true;

        default:
            return false;
        }
    };

    const kl::int2 position_down = position + kl::int2(0, 1);
    const kl::int2 position_down_left = position + kl::int2(-1, 1);
    const kl::int2 position_down_right = position + kl::int2(1, 1);

    if (position.y < (frame.height() - 1) && material_check(position_down)) {
        std::swap(particles[get_index(frame, position)], particles[get_index(frame, position_down)]);
    }
    else if (position.y < (frame.height() - 1) && position.x > 0 && material_check(position_down_left)) {
        std::swap(particles[get_index(frame, position)], particles[get_index(frame, position_down_left)]);
    }
    else if (position.y < (frame.height() - 1) && position.x < (frame.width() - 1) && material_check(position_down_right)) {
        std::swap(particles[get_index(frame, position)], particles[get_index(frame, position_down_right)]);
    }
}

static void water_physics(const kl::image& frame, std::vector<particle>& particles, const kl::int2& position)
{
    const std::function mat_check = [&](const kl::int2& p) {
        switch (particles[get_index(frame, p)].material) {
        case material::none:
            return true;

        default:
            return false;
        }
    };

    const kl::int2 pos_down = position + kl::int2(0, 1);
    const kl::int2 pos_down_l = position + kl::int2(-1, 1);
    const kl::int2 pos_down_r = position + kl::int2(1, 1);
    const kl::int2 pos_left = position + kl::int2(-1, 0);
    const kl::int2 pos_right = position + kl::int2(1, 0);

    if (position.y < (frame.height() - 1) && mat_check(pos_down)) {
        std::swap(particles[get_index(frame, position)], particles[get_index(frame, pos_down)]);
    }
    else if (position.y < (frame.height() - 1) && position.x > 0 && mat_check(pos_down_l)) {
        std::swap(particles[get_index(frame, position)], particles[get_index(frame, pos_down_l)]);
    }
    else if (position.y < (frame.height() - 1) && position.x < (frame.width() - 1) && mat_check(pos_down_r)) {
        std::swap(particles[get_index(frame, position)], particles[get_index(frame, pos_down_r)]);
    }
    else {
        if (const bool left = kl::random::get_bool(); left && position.x > 0 && mat_check(pos_left)) {
            std::swap(particles[get_index(frame, position)], particles[get_index(frame, pos_left)]);
        }
        else if (position.x < (frame.width() - 1) && mat_check(pos_right)) {
            std::swap(particles[get_index(frame, position)], particles[get_index(frame, pos_right)]);
        }
        else if (position.x > 0 && mat_check(pos_left)) {
            std::swap(particles[get_index(frame, position)], particles[get_index(frame, pos_left)]);
        }
    }
}

static void material_physics(const kl::image& frame, std::vector<particle>& particles, const kl::int2& position)
{
    if (const int index = get_index(frame, position); !particles[index].updated) {
        switch (particles[index].material) {
        case material::sand:
            sand_physics(frame, particles, position);
            break;

        case material::water:
            water_physics(frame, particles, position);
            break;
        }
        
        particles[index].updated = true;
    }
}

void physics(const kl::image& frame, std::vector<particle>& particles)
{
    bool left_to_right = kl::random::get_bool();
    for (kl::int2 position = kl::int2::splash(frame.height() - 1); position.y >= 0; position.y--) {
        if (left_to_right) {
            for (position.x = 0; position.x < static_cast<int>(frame.width()); position.x++) {
                material_physics(frame, particles, position);
            }
        }
        else {
            for (position.x = static_cast<int>(frame.width()) - 1; position.x >= 0; position.x--) {
                material_physics(frame, particles, position);
            }
        }
        left_to_right = !left_to_right;
    }
}
