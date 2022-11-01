#pragma once

#pragma region LIBS_IMPORTS
#if defined(FE2D_SFML)
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#endif

#if defined(FE2D_IMGUI)
#include <imgui.h>
#include <imgui-SFML.h>
#endif

#if defined(FE2D_BOX2D)
#include <box2d/box2d.h>
#endif
#pragma endregion

#pragma region STD_LIBS_IMPORT
#if defined(FE2D_DEBUG)
#include <iostream>

#define print(body) std::cout << body
#define printsp(body) print(body) << " "
#define println(body) print(body) << std::endl
#define printbr() std::cout << std::endl
#endif

// todo: filter out unused includes
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
#include <filesystem>

#include <any>
#include <variant>
#include <optional>

#include <thread>
#include <future>
#include <mutex>
#include <shared_mutex>
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

    typedef float float32_t;
    typedef double float64_t;

    typedef char* ptr_t;

    typedef void async;

    typedef std::array <uint32_t, 4> uint32_t4;
    typedef std::array <float32_t, 4> float32_t4;

    typedef std::string str_t; // to be replaced by own implementation
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

namespace fun {
    struct transform_t;

    struct rgb_t;
    struct rgba_t;

    struct command_t;

    namespace render {
        struct texture_t;
        struct shader_t;
        
        struct sprite_t;
        struct sprite_animator_t;

        struct render_item_t;
        struct render_queue_t;

        struct window_t;
        struct window_data_t;

        struct curve_t;
        struct curved_line_t;
        struct primitive_t;
        struct rounded_rect_t;

        struct tilemap_t;
        struct tilechunk_t;
    }

    namespace network {
        struct packet_t;
        struct packet_storage_t;
        struct threadsafe_packet_storage_t;

        struct connection_info_t;
        struct connection_t;

        struct server_t;
        struct client_t;
    }

    namespace interaction {
        struct interactable;
    }
}

namespace fun {
    namespace render {
#if defined(FE2D_SFML)
        typedef sf::Vertex vertex_t;
#endif
    }
}
