﻿//  _______________________________________________
// | EnergyTankTemplate.cpp - class implementation |
// | Jack Flower - November 2013                   |
// |_______________________________________________|
//

#include "EnergyTankTemplate.h"
#include "../../../../Logic/PhysicalManager.h"
#include "../../../../Logic/Actor/Actor.h"
#include "../../../../Rendering/Animations/AnimSet.h"

using namespace rendering::animation;
using namespace equipment;
using namespace logic;

namespace factory
{
	RTTI_IMPL(EnergyTankTemplate, ActorTemplate);

	//Konstruktor
	EnergyTankTemplate::EnergyTankTemplate()
	:
		ActorTemplate{},//konstruktor klasy bazowej
		m_templ_energy_tank_name{ "" },
		m_templ_energy_tank_capacity{ 0.0f },
		m_templ_energy{ 0.0f },
		m_templ_energy_tank_rotation_speed{ 0.0f }
	{
	}

	//Destruktor
	EnergyTankTemplate::~EnergyTankTemplate()
	{
		//~ActorTemplate()
		m_templ_energy_tank_name = "";
		m_templ_energy_tank_capacity = 0.0f;
		m_templ_energy = 0.0f;
		m_templ_energy_tank_rotation_speed = 0.0f;
	}

	//Metoda zwraca typ obiektu /RTTI/
	const std::string EnergyTankTemplate::getType() const
	{
		return rtti.getNameClass();
	}

	//Wirtualna metoda zwalniająca zasób
	void EnergyTankTemplate::drop()
	{
		delete this;
	}

	//Wirtualna metoda ładująca dane
	bool EnergyTankTemplate::load(const std::string & name)
	{
		Xml xml(name, "root");
		return load(xml);
	}

	//Wirtualna metoda ładująca dane z xml
	bool EnergyTankTemplate::load(Xml & xml)
	{
		//sprawdzamy, czy można załadować dane z klasy bazowej ActorTemplate
		if (!ActorTemplate::load(xml)) return false;

		//ładowanie wartości konfiguracji akumulatora energii
		if (xml_node<>*	node = xml.getChild(xml.getRootNode(), "energytank_config"))
		{
			m_templ_energy_tank_name = xml.getString(node, "energy_tank_name");
			m_templ_energy_tank_capacity = xml.getFloat(node, "energy_tank_capacity");
			m_templ_energy = xml.getFloat(node, "energy");
			m_templ_energy_tank_rotation_speed = xml.getFloat(node, "energy_tank_rotation_speed");
		}

		//wszystkie podklasy sprawdzają, czy xml jest poprawny
		return true;
	}

	//Metoda tworzy obiekt klasy FuelTank
	EnergyTank *EnergyTankTemplate::create(std::wstring id)
	{
		EnergyTank *energytank = gPhysicalManager.createEnergyTank(id);
		fill(energytank);
		return energytank;
	}

	//Wirtualna metoda wypełniająca wskazany obiekt danymi tej klasy
	void EnergyTankTemplate::fill(EnergyTank *p_energytank)
	{
		if(p_energytank)
		{
			ActorTemplate::fill(p_energytank);

			//przekazanie zestawu animacji do obiektu, który jest wypełniany danymi wzorca
			if (p_templ_animations)
			{
				p_energytank->setAnimSet(p_templ_animations);  
				
				//body
				if (p_templ_animations->getEnergyTankBodyDefaultAnim()!= nullptr)
					p_energytank->setAnimationBody(p_templ_animations->getEnergyTankBodyDefaultAnim());

				//head
				if (p_templ_animations->getEnergyTankHeadDefaultAnim()!= nullptr)
					p_energytank->setAnimationHead(p_templ_animations->getEnergyTankHeadDefaultAnim());
			}

			//pola tej klasy wzorca
			p_energytank->setEnergyTankName(m_templ_energy_tank_name);
			p_energytank->setEnergyTankCapacity(m_templ_energy_tank_capacity);
			p_energytank->setEnergy(m_templ_energy);
			p_energytank->setEnergyTankRotationSpeed(m_templ_energy_tank_rotation_speed);
		}
	}
}//namespace factory
