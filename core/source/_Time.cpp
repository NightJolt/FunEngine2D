#include "_Time.h"

sf::Clock _delta_clock_;
sf::Time _delta_time_;

float _time_elapsed_ = 0;
float _unscaled_delta_time_ = 0;
float _scaled_delta_time_ = 0;
float _time_scale_ = 1;
float _fps_ = 0;

std::map <fun::UniqueKey, float> _clocks_;

void fun::time::recalculate() {
    _delta_time_ = _delta_clock_.restart();
    _unscaled_delta_time_ = _delta_time_.asSeconds();
    _scaled_delta_time_ = _unscaled_delta_time_ * _time_scale_;
    _time_elapsed_ += _unscaled_delta_time_;

    _fps_ = 1.f / _unscaled_delta_time_;

    for (auto& clock : _clocks_) {
        if (clock.second > 0) clock.second -= _scaled_delta_time_;
    }
}

float fun::time::unscaled_delta_time() {
    return _unscaled_delta_time_;
}

float fun::time::delta_time() {
    return _scaled_delta_time_;
}

sf::Time fun::time::delta_time_object() {
    return _delta_time_;
}

float fun::time::time_elapsed() {
    return _time_elapsed_;
}

float fun::time::fps() {
    return _fps_;
}

void fun::time::set_time_scale(float val) {
    _time_scale_ = val;
}

void fun::time::get_time_scale(float val) {
    _time_scale_ *= val;
}

void fun::time::register_clock(void* ptr, const std::string& str, float val) {
    _clocks_[UniqueKey(ptr, str.c_str())] = val;
}

float fun::time::get_clock(void* ptr, const std::string& str) {
    UniqueKey key = UniqueKey(ptr, str.c_str());

    return _clocks_[key];
}

void fun::time::remove_clock(void* p, const std::string& k) {
    UniqueKey key = UniqueKey(p, k.c_str());

    _clocks_.erase(key);
}