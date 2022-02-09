#include "../Core/Globals.h"
#include "../Core/Math.h"
#include "../Core/Time.h"

class ParticleEmitter {
public:

    void Draw(sf::RenderWindow&);
    void Update();

private:

    void PushTexture(sf::Texture*);
    void PushTextureRect(sf::FloatRect);
};