#ifndef EVILBOSS_HPP
#define EVILBOSS_HPP

#include "Weapon.hpp"
#include "Game.hpp"
#include "Ennemy.hpp"

/*
 * Il est tr�s m�chant, et il en veut!
 */
class EvilBoss: public Ennemy
{
public:
    EvilBoss(const sf::Vector2f& offset, Entity* target);
    
    void Move(float frametime);
	void Collide(Entity& ent);
	void Action();
	void Hit(int damage);
private:
	enum Phase
	{
		EVIL, MORE_EVIL
	};
	Phase phase_;
	bool left_;
	Weapon eye_left_;
	Weapon eye_right_;
	Weapon canon_;
	Game& game_;
	float frametime_;	//frametime du dernier Move. Utilisi� par Action
};

#endif /* guard EVILBOSS_HPP */

