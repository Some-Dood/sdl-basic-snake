#include "../SDL/Renderer.hpp"

#include <deque>
#include <optional>
#include <utility>
#include <SDL_rect.h>

namespace Game {
    class Snake {
      public:
        enum class Direction : std::uint8_t { UP, DOWN, LEFT, RIGHT };
        enum class TurnOutcome : std::uint8_t { LOST, WON, PROCEED, SCORED };

        std::size_t get_score() const;

        /**
         * Controls the upcoming direction in the next tick.
         * Ignore invalid inputs, such as when trying to send
         * the snake into a 180-degree turn.
         */
        void set_current_direction(Direction dir);

        /** Returns `true` if tick was successful. Otherwise, the game is over. */
        TurnOutcome tick();
        /** Render the snake on the screen. */
        void draw(const SDL::Renderer & renderer, int width, int height) const;

        /** Resets the snake's state. */
        void reset();

      private:
        using Coords = std::pair<std::size_t, std::size_t>;
        static constexpr Coords BOUNDS{10, 10};

        /** Generates a random index from 0 to `max`. */
        static std::ptrdiff_t gen_index(std::ptrdiff_t max);

        /** Determines whether the user's latest input conflicts with the current velocity. */
        bool is_input_opposite_dir() const;

        /**
         * Generate possible coordinates for the apple.
         * May return `null` if there is no more space.
         */
        std::optional<Coords> gen_apple();

        /** The previous velocity of the snake head. By default, it goes right. */
        Direction direction = Direction::RIGHT;
        /** The latest input of the user. */
        Direction input = direction;
        /** Current location of the apple. */
        Coords apple{gen_apple().value()};
        /** Velocity and grid position of each snake node. */
        std::deque<SDL_Point> nodes{{2, 0}, {1, 0}, {}};
    };
} // namespace Game
