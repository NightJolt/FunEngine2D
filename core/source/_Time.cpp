#include "_Time.h"

static sf::Clock _delta_clock_;
static sf::Time _delta_time_;

static float _time_elapsed_ = 0;
static float _unscaled_delta_time_ = 0;
static float _scaled_delta_time_ = 0;
static float _time_scale_ = 1;
static float _fps_ = 0;

void fun::time::recalculate() {
    _delta_time_ = _delta_clock_.restart();
    _unscaled_delta_time_ = _delta_time_.asSeconds();
    _scaled_delta_time_ = _unscaled_delta_time_ * _time_scale_;
    _time_elapsed_ += _unscaled_delta_time_;

    _fps_ = 1.f / _unscaled_delta_time_;
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