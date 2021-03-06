﻿//  _____________________________________
// | Monster.cpp - class implementation  |
// | Jack Flower - January 2014          |
// |_____________________________________|
//


#include "Monster.h"
#include "../Physical/PhysicalInfo/PhysicalInfo.h"
#include "../../Rendering/Displayable/Displayable.h"
#include "../../Rendering/Animations/AnimationState.h"
#include "../../Rendering/Animations/Animation.h"
#include "../../Game/Game.h"
#include <SFML/Window.hpp>

using namespace rendering::displayable;
using namespace rendering::animation;
using namespace game;

namespace logic
{
	//Chroniony konstruktor domyślny
	Monster::Monster(const std::wstring& uniqueId)
		:
		Actor{ uniqueId },//konstruktor klasy bazowej
		m_time_do_death{ 0.0f }
	{
	}

	//Chroniony konstruktor kopiujący
	Monster::Monster(const Monster & MonsterCopy)
	:
		Actor(MonsterCopy),//konstruktor kopiujący klasy bazowej
		m_time_do_death{ MonsterCopy.m_time_do_death }
	{
	}

	//Destruktor wirtualny
	Monster::~Monster()
	{
		m_time_do_death = 0.0f;
	}

	//Metoda zwraca typ obiektu /RTTI/
	const std::string Monster::getType() const
	{
		return rtti.getNameClass();
	}

	//Wirtualna metoda aktualizująca obiekt
	void Monster::update(float dt)
	{
		Physical::update(dt);
		Actor::updateComponents(dt);

		////////na razie testy..., bo w Actor będzie już opakowana metoda...
		//////if (p_physical_info)
		//////	p_physical_info->SetPosition(this->GetPosition());


		sf::Vector2i position = sf::Mouse::getPosition(*gGame.getRenderWindow());
		//zamiana koordynatów na współrzędne świata używającego kamery
		position.x = (int)gGame.getRenderWindow()->mapPixelToCoords(position).x;
		position.y = (int)gGame.getRenderWindow()->mapPixelToCoords(position).y;

		if (position.x >= getPosition().x - getDisplayableBody()->getLocalBounds().width * getDisplayableBody()->getScale().x * 0.5f &&
			position.x <= getPosition().x + getDisplayableBody()->getLocalBounds().width * getDisplayableBody()->getScale().x * 0.5f &&
			position.y >= getPosition().y - getDisplayableBody()->getLocalBounds().height * getDisplayableBody()->getScale().y * 0.5f &&
			position.y <= getPosition().y + getDisplayableBody()->getLocalBounds().height * getDisplayableBody()->getScale().y * 0.5f)
		{
			//rotateHead(0.62f);	//2019-02-11 jest -> brakuje wrappera w tej klasie dla metody void RotateHead(float angle) - equipment
			//rotateBody(-0.62f);	//2019-02-11 jest -> brakuje wrappera w tej klasie dla metody void RotateBody(float angle) - equipment
			setRotationHead(this->getRotationHead() + 0.62f);
			setRotationBody(this->getRotationBody() - 0.62f);
			//tutaj obsługa klawiatury...
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
				fprintf(stderr, "Test key pressed...\n");
		}

		//atrapa odroczonej śmierci...
		//if(p_animation_body)
		//{
		//	m_time_do_death = m_time_do_death + 0.01f;//kumuluję...
		//	if(m_time_do_death > p_animation_body->TotalLength())
		//		kill();
		//}

		//
		//float anim_spped_body = GetAnimSpeedBody();

		//jest ok, speed factor = 1
		//int demo = 0;


		//Obsługiwane klawisze: RGBTY
		//to działa...
		//uwaga, z racji tego, że jestemm w update, tak wszystko co testuję
		//odbywa się w pętli czasu rzeczywistego...
		//zatem, należy pamiętać, aby obsługa odbywała się "jeden raz",
		//czyli obługa zdarzeń...
		//////sf::Event::KeyEvent &e  = gGame.GetGameEvent().key;
		//////if (e.code == sf::Keyboard::T)
		//////{
		//////	GetDisplayableBody()->setColor(sf::Color::Yellow);
		//////	fprintf(stderr, "Test key pressed...\n");//strzelam seriami...
		//////}


		////////ten kod działa
		//////if (gGame.GetGameEvent().key.code == sf::Keyboard::Y)
		//////{
		//////	GetDisplayableBody()->setColor(sf::Color::Yellow);
		//////	fprintf(stderr, "Yellow key pressed...\n");//strzelam seriami...
		//////}

		//ten kod działa poprawnie
		if (gGame.getGameEvent().key.code == sf::Keyboard::K)
			restoreColorBody();
	

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			//key R is pressed: set Red color our character
			getDisplayableBody()->setColor(sf::Color::Red);
			fprintf(stderr, "Red key pressed...\n");//single...(ale w update trudno upilnować)
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			//key G is pressed: set Green color our character
			getDisplayableBody()->setColor(sf::Color::Green);
			fprintf(stderr, "Green key pressed...\n");//single...(ale w update trudno upilnować)
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			//key B is pressed: set Blue color our character
			getDisplayableBody()->setColor(sf::Color::Blue);
			fprintf(stderr, "Blue key pressed...\n");//single...(ale w update trudno upilnować)
		}
	}
}//namespace logic
