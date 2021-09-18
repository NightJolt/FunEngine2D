#pragma once

namespace fun {
    class StaticObject {
    public:

        StaticObject() = default;
        virtual ~StaticObject() = default;

        virtual void Init() = 0;
        virtual void Dispose() = 0;

    private:
    };
}