﻿//  __________________________________________________
// | CommunicationTemplate.cpp - class implementation |
// | Jack Flower - July 2015                          |
// |__________________________________________________|
//

#include "CommunicationTemplate.h"
#include "../../../Rendering/Animations/CAnimSet.h"
#include "../../../ResourceManager/CResourceManager.h"

using namespace resource;

namespace factory
{
	RTTI_IMPL(CommunicationTemplate, CActorTemplate);

	//Konstruktor
	CommunicationTemplate::CommunicationTemplate()
	:
		CActorTemplate(),//konstruktor klasy bazowej
		m_templ_communication_name(),
		m_templ_range(0.0f),
		m_templ_reset_duration(0.0f),
		m_templ_login(),
		m_templ_password()
	{
	}

	//Destruktor wirtualny
	CommunicationTemplate::~CommunicationTemplate()
	{
		//CActorTemplate
		m_templ_communication_name = "";
		m_templ_range = 0.0f;
		m_templ_reset_duration = 0.0f;
		m_templ_login = "";
		m_templ_password = "";
	}

	//Metoda zwraca typ obiektu /RTTI/
	const std::string CommunicationTemplate::getType() const
	{
		return rtti.GetNameClass();
	}

	//Wirtualna metoda zwalniająca zasób - implementacje w klasach pochodnych
	void CommunicationTemplate::drop()
	{
		delete this;
	}

	//Metoda ładująca dane
	bool CommunicationTemplate::load(const std::string &name)
	{
		CXml xml(name, "root" );
		return load(xml);
	}

	//Wirtualna metoda ładująca dane z xml
	bool CommunicationTemplate::load(CXml &xml)
	{
		//sprawdzamy, czy można załadować dane z klasy bazowej CActorTemplate
		if (!CActorTemplate::load(xml)) return false;

		//dane obiektu
		if (xml_node<> *node = xml.GetChild(xml.GetRootNode(), "communication_config"))
		{
			m_templ_communication_name = xml.GetString(node, "communication_name");
			m_templ_range = xml.GetFloat(node,"range");
			m_templ_reset_duration = xml.GetFloat(node, "reset_duration");
			m_templ_login = xml.GetString(node, "login");
			m_templ_password = xml.GetString(node, "password");
		}

		//wszystkie podklasy sprawdzają, czy xml jest poprawny
		return true;
	}

	//Metoda tworzy obiekt klasy CPowerStation
	CCommunication* CommunicationTemplate::create(std::wstring id)
	{
		CCommunication *communication = gPhysicalManager.CreateCommunication(id);
		fill(communication);
		return communication;
	}

	//Wirtualna metoda wypełniająca wskazany obiekt danymi tej klasy
	void CommunicationTemplate::fill(CCommunication *p_communication)
	{
		if(p_communication)
		{
			CActorTemplate::fill(p_communication);

			//przekazanie zestawu animacji do obiektu, który jest wypełniany danymi wzorca
			if (p_templ_animations)
			{
				p_communication->SetAnimSet(p_templ_animations);

				//body
				if (p_templ_animations->GetCommunicationBodyDefaultAnim() != NULL)
					p_communication->SetAnimationBody(p_templ_animations->GetCommunicationBodyDefaultAnim());

				//head
				if (p_templ_animations->GetCommunicationHeadDefaultAnim() != NULL)
					p_communication->SetAnimationHead(p_templ_animations->GetCommunicationHeadDefaultAnim());
			}

			//pola tej klasy wzorca
			p_communication->SetCommunicationName(m_templ_communication_name);
			p_communication->setRange(m_templ_range);
			p_communication->setResetDuration(m_templ_reset_duration);
			p_communication->getLoginModule().setLogin(m_templ_login);
			p_communication->getLoginModule().setPassword(m_templ_password);
			//decorate
			p_communication->setSmoothing(true);
		}
	}
}//namespace factory