#pragma once

#include <cstdlib>
#include <string>
#include <functional>

namespace tail {
    enum class VarType {
        INTEGER,
        UNSIGNED_INTEGER,
        FLOAT,
        VECTOR_2,
        VECTOR_3,
        VECTOR_4,
        COLOR_3,
        COLOR_4,
        BOOL,
        STRING,
        CUSTOM
    };

    struct Variable {
        void* var;
        size_t size;
        VarType type;
        std::string name;
        std::function<void()>custom;
    };
}
