﻿//  ______________________________________________________
// | ThermalInsulationTemplate.cpp - class implementation |
// | Jack Flower June 2014                                |
// |______________________________________________________|
//

#include "ThermalInsulationTemplate.h"
#include "../../../../Weather/Weather.h"
#include "../../../../Rendering/Animations/AnimSet.h"

using namespace weather;

namespace factory
{
	RTTI_IMPL(ThermalInsulationTemplate, ActorTemplate);

	ThermalInsulationTemplate::ThermalInsulationTemplate()
	:
		ActorTemplate{},//konstruktor klasy bazowej
		m_templ_thermalinsulation_name{ "" },
		m_templ_temperature_ambient{ 0.0f },
		m_templ_thermal_protection{ 0.0f },
		m_templ_thermal_protection_factor{ 0.0f },
		m_templ_thermal_protection_consume{ 0.0f },
		m_templ_thermal_protection_duration{ 0.0f }
	{
	}

	ThermalInsulationTemplate::~ThermalInsulationTemplate()
	{
		//~ActorTemplate()
		m_templ_thermalinsulation_name = "";
		m_templ_temperature_ambient = 0.0f;
		m_templ_thermal_protection = 0.0f;
		m_templ_thermal_protection_factor = 0.0f;
		m_templ_thermal_protection_consume = 0.0f;
		m_templ_thermal_protection_duration = 0.0f;
	}

	//Metoda zwraca typ obiektu /RTTI/
	const std::string ThermalInsulationTemplate::getType() const
	{
		return rtti.getNameClass();
	}

	//Wirtualna metoda zwalniająca zasób
	void ThermalInsulationTemplate::drop()
	{
		delete this;
	}

	//Metoda ładująca dane
	bool ThermalInsulationTemplate::load(const std::string & name)
	{
		Xml xml(name, "root" );
		return load(xml);
	}

	//Wirtualna metoda ładująca dane z xml ładuje wspólne cechy Actor
	bool ThermalInsulationTemplate::load(Xml & xml)
	{
		//ładowanie danych klasy bazowej Actor
		if (!ActorTemplate::load(xml)) return false;

		//dane termoizolatora
		if (xml_node<> *node = xml.getChild(xml.getRootNode(), "thermalinsulation_config"))
		{
			m_templ_thermalinsulation_name = xml.getString(node, "thermalinsulation_name");
			m_templ_temperature_ambient = xml.getFloat(node, "temperature_ambient");
			m_templ_thermal_protection = xml.getFloat(node, "thermal_protection");
			m_templ_thermal_protection_factor = xml.getFloat(node, "thermal_protection_factor");
			m_templ_thermal_protection_consume = xml.getFloat(node, "thermal_protection_consume");
			m_templ_thermal_protection_duration = xml.getFloat(node, "thermal_protection_duration");
		}
		
		//wszystkie podklasy sprawdzają, czy xml jest poprawny
		return true;
	}

	//Metoda tworzy obiekt klasy ThermalInsulation
	ThermalInsulation *ThermalInsulationTemplate::create(std::wstring id)
	{
		ThermalInsulation *thermalinsulation = gPhysicalManager.createThermalInsulation(id);
		fill(thermalinsulation);
		return thermalinsulation;
	}

	//Wirtualna metoda wypełniająca wskazany obiekt danymi tej klasy
	void ThermalInsulationTemplate::fill(ThermalInsulation *p_thermalinsulation)
	{
		if(p_thermalinsulation)
		{
			ActorTemplate::fill(p_thermalinsulation);

			//przekazanie zestawu animacji do obiektu, który jest wypełniany danymi wzorca
			if (p_templ_animations)
			{
				p_thermalinsulation->setAnimSet(p_templ_animations);

				//body
				if (p_templ_animations->getThermalInsulationBodyDefaultAnim() != nullptr)
					p_thermalinsulation->setAnimationBody(p_templ_animations->getThermalInsulationBodyDefaultAnim());

				//head
				if (p_templ_animations->getThermalInsulationHeadDefaultAnim() != nullptr)
					p_thermalinsulation->setAnimationHead(p_templ_animations->getThermalInsulationHeadDefaultAnim());
			}


			//obliczam wartość zużycia ochrony termicznej w jednostce czasu (na sekundę) znając czas trwania doby
			//termoizolacja zużyje się w ciągu doby...
			if(gWeather.getDayDuration() != 0)
				m_templ_thermal_protection_consume = (gWeather.getUpdateTime() * m_templ_thermal_protection)/gWeather.getDayDuration();

			//przekazanie skonfigurowanych danych...
			p_thermalinsulation->setThermalInsulationName(m_templ_thermalinsulation_name);
			p_thermalinsulation->setTemperatureAmbient(m_templ_temperature_ambient);
			p_thermalinsulation->setThermalProtection(m_templ_thermal_protection);
			p_thermalinsulation->setThermalProtectionFactor(m_templ_thermal_protection_factor);
			p_thermalinsulation->setThermalProtectionConsume(m_templ_thermal_protection_consume);
			p_thermalinsulation->setThermalProtectionDuration(m_templ_thermal_protection_duration);
		}
	}
}//namespace factory
