#include "Snake.hpp"
#include <algorithm>

namespace Game {
    bool Snake::is_opposite_direction(const Direction dir) const {
        switch (direction) {
            case Direction::UP: return dir == Direction::DOWN;
            case Direction::DOWN: return dir == Direction::UP;
            case Direction::LEFT: return dir == Direction::RIGHT;
            case Direction::RIGHT: return dir == Direction::LEFT;
        }
    }

    void Snake::set_current_direction(const Direction dir) {
        if (!is_opposite_direction(dir))
            direction = dir;
    }

    bool Snake::tick() {
        // Propagate new velocities and positions
        auto current_dir = direction;
        for (auto & [position, velocity] : nodes) {
            std::swap(current_dir, velocity);
            switch (velocity) {
                case Direction::UP: position.y = position.y > 0 ? position.y - 1 : BOUNDS.y; break;
                case Direction::DOWN:
                    position.y = position.y < BOUNDS.y ? position.y + 1 : 0;
                    break;
                case Direction::LEFT:
                    position.x = position.x > 0 ? position.x - 1 : BOUNDS.x;
                    break;
                case Direction::RIGHT:
                    position.x = position.x < BOUNDS.x ? position.x + 1 : 0;
                    break;
            }
        }

        // Check for any collisions with the head
        const auto & head = nodes.front().position;
        const auto end = nodes.cend();
        return std::find_if(nodes.cbegin() + 1, end, [&head](auto const & node) {
                   return node.position.x == head.x && node.position.y == head.y;
               }) == end;
    }

    void Snake::draw(SDL::Renderer const & renderer) const {
        renderer.set_render_draw_color(0, 255, 0, 255);
        const auto [width, height] = renderer.get_viewport_dimensions();
        const SDL_Point tile_size{width / BOUNDS.x, height / BOUNDS.y};
        for (auto const & [position, _] : nodes)
            renderer.fill_rect(
                {position.x * tile_size.x, position.y * tile_size.y, tile_size.x, tile_size.y});
    }

    void Snake::reset() {
        direction = Direction::RIGHT;
        nodes.clear();
        nodes.push_front({});
    }
} // namespace Game