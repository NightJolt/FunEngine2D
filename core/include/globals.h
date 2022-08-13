#pragma once

#pragma region BUILD_FLAGS
#define DEBUG_BUILD
#pragma endregion

#pragma region TARGET_PLATFORM
#define WIN
// #define LINUX
// #define APPLE
#pragma endregion

#pragma region LIBS
#define USES_SFML
#define USES_IMGUI
// #define USES_CUDA
// #define USES_LUA
#define USES_BOX2D
#pragma endregion

#pragma region LIBS_IMPORTS
#if defined(USES_SFML)
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#endif

#if defined(USES_IMGUI)
#include <imgui.h>
#include <imgui-SFML.h>
#endif

#if defined(USES_BOX2D)
#include <box2d/box2d.h>
#endif
#pragma endregion

#pragma region STD_LIBS_IMPORT
#if defined(DEBUG_BUILD)
#include <iostream>

#define print(body) std::cout << body
#define printsp(body) print(body) << " "
#define println(body) print(body) << std::endl
#define printbr() std::cout << std::endl
#endif

#include <fstream>
#include <cstdint>
#include <memory>
#include <cstring>
#include <sstream>
#include <string_view>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <cmath>
#include <vector>
#include <array>
#include <queue>
#include <random>
// #include <xhash>
#include <utility>
#include <functional>
#include <algorithm>
#include <tuple>

#include <any>
#include <variant>
#include <optional>

#include <thread>
#include <future>
#include <mutex>
#include <condition_variable>
#include <semaphore>
#pragma endregion

/*
#pragma region tilemap

#define CHUNK_SIZE 16
#define TILE_SIZE 8.f
#define TILE_TEXTURE_SIZE 8
#define TILE_ATLAS_SIZE 256
#define RAND_TEXTURE_COUNT 2

#pragma endregion
*/

#pragma region MACROS
#define BITS(expr) (sizeof(expr) << 3)
#define STR(str) (#str)
#pragma endregion

namespace fun {
    typedef uint64_t mask64_t;
    typedef uint32_t mask32_t;
    typedef uint16_t mask16_t;
    typedef uint8_t mask8_t;

    typedef int32_t layer_t;

    typedef std::array <uint32_t, 4> uint32_t4;
    typedef std::array <float, 4> float4;
}

namespace fun {
    void glob_init();
}

// namespace std {
//     template <>
//     struct hash <fun::UniqueKey> {
//         std::size_t operator()(const fun::UniqueKey& ukey) const {
//             size_t h = 5381;
//             int c;
//             const char* s = ukey.key;

// 			while ((c = *s++))
// 				h = ((h << 5) + h) + c;

//             return hash <uint64_t> ()(ukey) + h;
//         }
//     };
// }

// namespace std {
//     template <typename T>
//     inline std::string to_string(const std::vector<T>& v, function <std::string(size_t, const T&)> converter = [](size_t i, const T& t) -> std::string { return std::to_string(t); }) {
//         size_t size = v.size();

//         std::string result;

//         result.reserve(size * (sizeof(v) + 2));

//         result.append("[");

//         for (int i = 0; i < size - 1; i++) {
//             result.append(converter(i, v[i]));
//             result.append(", ");
//         }

//         if (!v.empty()) result.append(converter(v.size() - 1, v[v.size() - 1]));
        
//         result.append("]");

//         return result;
//     }
// }