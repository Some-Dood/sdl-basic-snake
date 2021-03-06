#include "Context.hpp"

#include <SDL_error.h>
#include <SDL_ttf.h>
#include <stdexcept>

namespace TTF {
    Context::Context() {
        const int result = TTF_Init();
        if (result != 0) throw std::runtime_error{SDL_GetError()};
    }

    Context::~Context() { TTF_Quit(); }
} // namespace TTF
