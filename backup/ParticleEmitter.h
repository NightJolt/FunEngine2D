#include "globals.h"

#include "Math.h"
#include "FTime.h"

class ParticleEmitter {
public:

    void Draw(sf::RenderWindow&);
    void Update();

private:

    void PushTexture(sf::Texture*);
    void PushTextureRect(sf::FloatRect);
};