﻿//  _________________________________________________
// | PowerStationTemplate.cpp - class implementation |
// | Jack Flower - May 2015                          |
// |_________________________________________________|
//

#include "PowerStationTemplate.h"
#include "../../../Rendering/Animations/AnimSet.h"
#include "../../../ResourceManager/ResourceManager.h"
#include "../../EquipmentFactory/CommunicationFactory/CommunicationTemplate.h"

using namespace resource;

namespace factory
{
	RTTI_IMPL(PowerStationTemplate, ActorTemplate);

	//Konstruktor
	PowerStationTemplate::PowerStationTemplate()
	:
		ActorTemplate{},//konstruktor klasy bazowej
		m_templ_power_station_name{},
		m_templ_energy_capacitor{ 0.0f },
		m_templ_amount_power_modules{ 0 },
		p_templ_communication{ nullptr }
	{
	}

	//Destruktor wirtualny
	PowerStationTemplate::~PowerStationTemplate()
	{
		//~ActorTemplate()
		m_templ_power_station_name = "";
		m_templ_energy_capacitor = 0.0f;
		m_templ_amount_power_modules = 0;
		mm_templ_communication_data;
		p_templ_communication = nullptr;
	}

	//Metoda zwraca typ obiektu /RTTI/
	const std::string PowerStationTemplate::getType() const
	{
		return rtti.getNameClass();
	}

	//Wirtualna metoda zwalniająca zasób - implementacje w klasach pochodnych
	void PowerStationTemplate::drop()
	{
		delete this;
	}

	//Metoda ładująca dane
	bool PowerStationTemplate::load(const std::string & name)
	{
		Xml xml(name, "root" );
		return load(xml);
	}

	//Wirtualna metoda ładująca dane z xml wywoływana przez implementacje klas potomnych
	bool PowerStationTemplate::load(Xml & xml)
	{
		//sprawdzamy, czy można załadować dane z klasy bazowej ActorTemplate
		if (!ActorTemplate::load(xml)) return false;

		//dane obiektu
		if (xml_node<> *node = xml.getChild(xml.getRootNode(), "power_station_config"))
		{
			m_templ_power_station_name = xml.getString(node, "power_station_name");
			m_templ_energy_capacitor = xml.getFloat(node,"energy_capacitor");
			m_templ_amount_power_modules = xml.getInt(node, "amount_power_modules");
		}

		//ładowanie modułu komunikacyjnego
		if (xml_node<>*	node = xml.getChild(xml.getRootNode(), "communication_data"))
		{
			//flaga, czy obiekt posiada moduł komunikacyjny
			mm_templ_communication_data.setUseEquipment(xml.getBool(node, "use_communication"));

			//zapisuję do zmiennej nazwę pliku z konfiguracją modułu komunikacji
			std::string communication_filename_tmp = xml.getString(node, "communication_filename");
			
			//emitery dla obiektu klasy Communication
			mm_templ_communication_data.setEmiter(xml.getFloat(node, "communication_emiter_x"), xml.getFloat(node, "communication_emiter_y"));

			if(mm_templ_communication_data.getUseEquipment())
				p_templ_communication = (CommunicationTemplate*)gResourceManager.getPhysicalTemplate(communication_filename_tmp);
		}

		//wszystkie podklasy sprawdzają, czy xml jest poprawny
		return true;
	}

	//Metoda tworzy obiekt klasy PowerStation
	PowerStation *PowerStationTemplate::create(std::wstring id)
	{
		PowerStation *power_station = gPhysicalManager.createPowerStation(id);
		fill(power_station);
		return power_station;
	}

	//Wirtualna metoda wypełniająca wskazany obiekt danymi tej klasy
	void PowerStationTemplate::fill(PowerStation *p_power_station)
	{
		if(p_power_station)
		{
			ActorTemplate::fill(p_power_station);

			//przekazanie zestawu animacji do obiektu, który jest wypełniany danymi wzorca
			if (p_templ_animations)
			{
				p_power_station->setAnimSet(p_templ_animations);

				//body
				if (p_templ_animations->getWindPowerStationBodyDefaultAnim() != nullptr)
					p_power_station->setAnimationBody(p_templ_animations->getWindPowerStationBodyDefaultAnim());

				//head
				if (p_templ_animations->getWindPowerStationHeadDefaultAnim() != nullptr)
					p_power_station->setAnimationHead(p_templ_animations->getWindPowerStationHeadDefaultAnim());
			}

			//kategoria
			p_power_station->setCategory(PHYSICAL_POWERSTATION);

			//pola tej klasy wzorca
			p_power_station->setPowerStationName(m_templ_power_station_name);
			p_power_station->setEnergyCapacitor(m_templ_energy_capacitor);
			p_power_station->setAmountPowerModules(m_templ_amount_power_modules);
			p_power_station->setUseCommunication(mm_templ_communication_data.getUseEquipment());

			//jeśli obiekt posiada moduł do komunikacji
			if(mm_templ_communication_data.getUseEquipment())
			{
				if(p_templ_communication)
				{
					//pobieramy składową moduł komunikacji i wzorzec wypełnia wskaźnik danymi
					p_power_station->SetCommunication(p_templ_communication->create(L""));
					//przekazanie wskaźnikowi na klasę Communication informacji o wzorcu
					p_power_station->GetCommunication()->setTemplate(p_templ_communication);
					//decorate
					p_power_station->GetCommunication()->setSmoothing(true);
				}
			}

			//decorate
			p_power_station->setSmoothing(true);
		}
	}
}//namespace factory
