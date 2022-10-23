#include "simulator.h"


static void fill_circle(const kl::image& frame, const kl::int2& position, const material& material, std::vector<particle>& particles)
{
    for (kl::int2 pixel = kl::int2::splash(position.y - brush_size); pixel.y <= position.y + brush_size; pixel.y++) {
        const int x_val = static_cast<int>(position.x + sqrt(brush_size * brush_size - static_cast<float>(pixel.y - position.y) * static_cast<float>(pixel.y - position.y)));

        int left_x = 2 * position.x - x_val;
        int right_x = x_val;
        if (right_x < left_x) {
            std::swap(left_x, right_x);
        }

        for (pixel.x = left_x; pixel.x <= right_x; pixel.x++) {
            if (is_in_frame(frame, pixel)) {
                particles[get_index(frame, pixel)].material = material;
            }
        }
    }
}

void input(kl::window& window, const kl::image& frame, std::vector<particle>& particles)
{
    if (window.keyboard.num1.state()) {
        selected_material = material::sand;
    }
    if (window.keyboard.num2.state()) {
        selected_material = material::water;
    }
    if (window.keyboard.num3.state()) {
        selected_material = material::rock;
    }

    static int last_size = 0;
    if (const int scroll_delta = window.mouse.scroll() - last_size; brush_size + scroll_delta > 0) {
        brush_size += scroll_delta;
    }
    last_size = window.mouse.scroll();

    if (window.mouse.left.state() && is_in_frame(frame, window.mouse.position())) {
        fill_circle(frame, window.mouse.position(), selected_material, particles);
    }

    if (window.mouse.right.state() && is_in_frame(frame, window.mouse.position())) {
        fill_circle(frame, window.mouse.position(), material::none, particles);
    }

    if (window.keyboard.r.state()) {
        for (particle& p : particles) {
            p.material = material::none;
        }
    }
}
