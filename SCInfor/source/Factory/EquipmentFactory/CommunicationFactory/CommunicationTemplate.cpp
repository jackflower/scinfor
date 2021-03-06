﻿//  __________________________________________________
// | CommunicationTemplate.cpp - class implementation |
// | Jack Flower - July 2015                          |
// |__________________________________________________|
//

#include "CommunicationTemplate.h"
#include "../../../Rendering/Animations/AnimSet.h"
#include "../../../ResourceManager/ResourceManager.h"

using namespace resource;

namespace factory
{
	RTTI_IMPL(CommunicationTemplate, ActorTemplate);

	//Konstruktor
	CommunicationTemplate::CommunicationTemplate()
	:
		ActorTemplate{},//konstruktor klasy bazowej
		m_templ_communication_name{},
		m_templ_range{ 0.0f },
		m_templ_reset_duration{ 0.0f },
		m_templ_login{},
		m_templ_password{}
	{
	}

	//Destruktor wirtualny
	CommunicationTemplate::~CommunicationTemplate()
	{
		//~ActorTemplate()
		m_templ_communication_name = "";
		m_templ_range = 0.0f;
		m_templ_reset_duration = 0.0f;
		m_templ_login = "";
		m_templ_password = "";
	}

	//Metoda zwraca typ obiektu /RTTI/
	const std::string CommunicationTemplate::getType() const
	{
		return rtti.getNameClass();
	}

	//Wirtualna metoda zwalniająca zasób - implementacje w klasach pochodnych
	void CommunicationTemplate::drop()
	{
		delete this;
	}

	//Metoda ładująca dane
	bool CommunicationTemplate::load(const std::string & name)
	{
		Xml xml(name, "root" );
		return load(xml);
	}

	//Wirtualna metoda ładująca dane z xml
	bool CommunicationTemplate::load(Xml & xml)
	{
		//sprawdzamy, czy można załadować dane z klasy bazowej ActorTemplate
		if (!ActorTemplate::load(xml)) return false;

		//dane obiektu
		if (xml_node<> *node = xml.getChild(xml.getRootNode(), "communication_config"))
		{
			m_templ_communication_name = xml.getString(node, "communication_name");
			m_templ_range = xml.getFloat(node,"range");
			m_templ_reset_duration = xml.getFloat(node, "reset_duration");
			m_templ_login = xml.getString(node, "login");
			m_templ_password = xml.getString(node, "password");
		}

		//wszystkie podklasy sprawdzają, czy xml jest poprawny
		return true;
	}

	//Metoda tworzy obiekt klasy PowerStation
	Communication* CommunicationTemplate::create(std::wstring id)
	{
		Communication *communication = gPhysicalManager.createCommunication(id);
		fill(communication);
		return communication;
	}

	//Wirtualna metoda wypełniająca wskazany obiekt danymi tej klasy
	void CommunicationTemplate::fill(Communication *p_communication)
	{
		if(p_communication)
		{
			ActorTemplate::fill(p_communication);

			//przekazanie zestawu animacji do obiektu, który jest wypełniany danymi wzorca
			if (p_templ_animations)
			{
				p_communication->setAnimSet(p_templ_animations);

				//body
				if (p_templ_animations->getCommunicationBodyDefaultAnim() != nullptr)
					p_communication->setAnimationBody(p_templ_animations->getCommunicationBodyDefaultAnim());

				//head
				if (p_templ_animations->getCommunicationHeadDefaultAnim() != nullptr)
					p_communication->setAnimationHead(p_templ_animations->getCommunicationHeadDefaultAnim());
			}

			//pola tej klasy wzorca
			p_communication->setCommunicationName(m_templ_communication_name);
			p_communication->setRange(m_templ_range);
			p_communication->setResetDuration(m_templ_reset_duration);
			p_communication->setLogin(m_templ_login);
			p_communication->setPassword(m_templ_password);
			//decorate
			p_communication->setSmoothing(true);
		}
	}
}//namespace factory
