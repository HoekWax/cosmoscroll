#include "Asteroid.hpp"
#include "MediaManager.hpp"
#include "ParticleSystem.hpp"
#include "Game.hpp"
#include "Math.hpp"

#include <SFML/System.hpp>
#include <sstream>

// division en morceaux de taille moindre
#define BIG_SPLIT_INTO     2
#define MEDIUM_SPLIT_INTO  6


inline const sf::Image& select_image(Asteroid::Size size)
{
    const int NB = 3;
    static const char* image_bases[] = {
        "asteroid-small",
        "asteroid-medium",
        "asteroid-big"
    };
    std::ostringstream key;
    key << image_bases[size] << '-' << sf::Randomizer::Random(1, NB);
    return GET_IMG(key.str().c_str());
}


Asteroid::Asteroid(const sf::Vector2f& offset, Size size, float angle) :
    Entity(select_image(size), offset, size + 1)
{
    size_ = size;
    speed_ = 100;
    angle_ = DEG_TO_RAD(angle);
}


void Asteroid::Move(float frametime)
{
    sprite_.Move(-50 * frametime, 0); // mouvement latéral
/*
TODO
(00:08:43) Alexandre: manque un ajustement sur le facteur de ralentissement 0.99 appliqué à chaque frame
(00:09:21) Alexandre: donc l'astéro se prend N frames par seconde * 0.99 de ralentissement
(00:09:31) Alexandre: faut impliquer frametime dans le calcul pour que ce soit indépendant des FPS
(sinon plus on a de FPS plus l'astéro ralentit vite)
*/
    speed_ *= 0.99;
    float framespeed = frametime * speed_;
    sf::Vector2f offset = sprite_.GetPosition();
    offset.x = offset.x + framespeed * quick_cos(angle_);
    offset.y = offset.y - framespeed * quick_sin(angle_);
    sprite_.SetPosition(offset);
    KillIfOut();
}


void Asteroid::Hit(int damage)
{
	sf::Vector2f offset = sprite_.GetPosition();
	
    Entity::Hit(damage);
    if (IsDead())
    {
        Game& game = Game::GetInstance();
        switch (size_)
        {
            case BIG:
                for (int i = 0; i < BIG_SPLIT_INTO; ++i)
                {
                    game.AddEntity(new Asteroid(offset, MEDIUM,
                        sf::Randomizer::Random(0, 360)));
                };
                break;
            case MEDIUM:
                for (int i = 0; i < MEDIUM_SPLIT_INTO; ++i)
                {
                    game.AddEntity(new Asteroid(offset, SMALL,
                        sf::Randomizer::Random(0, 360)));
                }
                break;
            default:
                break;
        }
    }
}

