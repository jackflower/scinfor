//  ____________________________________________
// | CTransformation.cpp - class implementation |
// | Jack Flower - May 2016                     |
// |____________________________________________|
//

#include "CTransformation.h"
#include "../../Logic/Actor/Actor.h"
#include "../../Rendering/Displayable/Displayable.h"
#include "../Utilities/Utilities.h"

using namespace rendering::displayable;

namespace transformation
{
	RTTI_IMPL_NOPARENT(CTransformation);//nie podajemy klas z biblioteki
	
	//Konstruktor
	CTransformation::CTransformation()
	:
		m_initial	(0.0f, 0.0f),
		m_offset	(0.0f, 0.0f),
		m_emiter	(0.0f, 0.0f)
	{
	}

	//Konstruktor kopiuj�cy
	CTransformation::CTransformation(const CTransformation & CTransformationCopy)
	:
		m_initial	(CTransformationCopy.m_initial),
		m_offset	(CTransformationCopy.m_offset),
		m_emiter	(CTransformationCopy.m_emiter)
	{
	}

	//Destruktor wurtualny
	CTransformation::~CTransformation()
	{
		m_initial.x	= 0.0f;
		m_initial.y = 0.0f;
		m_offset.x	= 0.0f;
		m_offset.y	= 0.0f;
		m_emiter.x	= 0.0f;
		m_emiter.y	= 0.0f;
	}

	//Metoda zwraca po�o�enie przed transformacj�
	const sf::Vector2f & CTransformation::getInitial() const
	{
		return m_initial;
	}

	//Metoda ustawia po�o�enie przed transformacj�
	void CTransformation::setInitial(sf::Vector2f & initial)
	{
		m_initial = initial;
	}

	//Metoda ustawia po�o�enie przed transformacj�
	void CTransformation::setInitial(float initial_x, float initial_y)
	{
		m_initial.x = initial_x;
		m_initial.y = initial_y;
	}

	//Metoda zwraca referencj� wektora przesuni�cia
	const sf::Vector2f & CTransformation::getOffset() const
	{
		return m_offset;
	}

	//Metoda ustawia wektor przesuni�cia
	void CTransformation::setOffset(sf::Vector2f & offset)
	{
		m_offset = offset;
	}

	//Metoda ustawia wektor przesuni�cia
	void CTransformation::setOffset(float offset_x, float offset_y)
	{
		m_offset.x = offset_x;
		m_offset.y = offset_y;
	}

	//Metoda zwraca referencj� na wektora po�o�enia emitera
	const sf::Vector2f & CTransformation::getEmiter() const
	{
		return m_emiter;
	}

	//Metoda ustawia wektor po�o�enia emitera
	void CTransformation::setEmiter(sf::Vector2f & emiter)
	{
		m_emiter = emiter;
	}

	//Metoda ustawia wektor po�o�enia emitera
	void CTransformation::setEmiter(float emiter_x, float emiter_y)
	{
		m_emiter.x = emiter_x;
		m_emiter.y = emiter_y;
	}

	//Metoda dokonuje transformacji skali, pozycji, obrotu
	void CTransformation::Transform(Actor * p_parent, Actor * p_child)
	{
		//transformacja opiera si� na zainicjowanych wska�nikach
		//obiekt�w drawowalnych, zatem trzeba sprawdzi� ten warunek
		if (!p_child->getDisplayableBody()) return;
		if (!p_parent->getDisplayableBody()) return;

		//obiekt p_child znajduje si� na cz�ci body w�a�ciciela p_parent
		//dlatego wszystkie obliczenia (aktualizacja po�o�enie)
		//wszystkie obliczenia (transformacja) liczone s� wzgl�dem cz�ci body
	
		if (p_parent != nullptr)
		{
			if (p_child != nullptr)
			{
				//pobieramy warto�� obrotu w�a�ciciela (body)
				p_child->setRotationBody(p_parent->getRotationBody());
				
				//pobieramy skal� w�a�ciciela
				p_child->setScale(p_parent->getScaleBody());

				//ustawiam wektor przesuni�cia wzgl�dem w�a�ciciela (body)
				m_offset.x = p_parent->getDisplayableBody()->getLocalBounds().width * 0.5f * p_parent->getScaleBody().x + (m_emiter.x * p_parent->getScaleBody().x);
				m_offset.y = p_parent->getDisplayableBody()->getLocalBounds().height * 0.5f * p_parent->getScaleBody().y + (m_emiter.y * p_parent->getScaleBody().y);

				//wyliczam pozycj� pocz�tkow� uwzgl�dniaj�c przesuni�cie (body)
				m_initial.x = p_parent->getDisplayableBody()->getPosition().x + (m_offset.x * -cos(p_parent->getRotationBody() * (float)RADIANS_PER_DEGREE) + m_offset.y * -sin(p_parent->getRotationBody() * (float)RADIANS_PER_DEGREE));
				m_initial.y = p_parent->getDisplayableBody()->getPosition().y + (m_offset.x * -sin(p_parent->getRotationBody() * (float)RADIANS_PER_DEGREE) - m_offset.y * -cos(p_parent->getRotationBody() * (float)RADIANS_PER_DEGREE));

				//przekazuj� wyliczon� pozycj� do child
				p_child->setPosition(m_initial.x, m_initial.y);
			}
		}
	}
}//namespace transformation
