﻿//  ________________________________________________
// | InformationTemplate.cpp - class implementation |
// | Jack Flower - April 2015                       |
// |________________________________________________|
//

#include "InformationTemplate.h"
#include "../../Information/InfoManager.h"
#include "../../Information/Information.h"
#include "../../Utilities/StringUtils/StringUtils.h"

using namespace infologic;

template<> InformationTemplate* Singleton<InformationTemplate>::m_singleton = 0;

namespace factory
{
	RTTI_IMPL(InformationTemplate, Resource);

	//Konstruktor
	InformationTemplate::InformationTemplate()
	:
		Resource{},//konstruktor klasy bazowej
		m_templ_filename{ "" },
		m_templ_type{ "" },
		p_templ_digit_displayable{ nullptr },
		p_templ_mask_displayable{ nullptr },
		m_templ_texture_digit_name{ "" },
		m_templ_texture_mask_name{ "" },
		m_templ_tranformable_digit{},
		m_templ_tranformable_mask{}
	{
	}

	//Destruktor
	InformationTemplate::~InformationTemplate()
	{
		//~Resource()
		m_templ_filename = "";
		m_templ_type = "";
		p_templ_digit_displayable = nullptr;
		p_templ_mask_displayable = nullptr;
		m_templ_texture_digit_name = "";
		m_templ_texture_mask_name = "";
		m_templ_tranformable_digit;
		m_templ_tranformable_mask;
	}

	//Metoda zwraca typ obiektu /RTTI/
	const std::string InformationTemplate::getType() const
	{
		return rtti.getNameClass();
	}

	//Wirtualna metoda zwalniająca zasób
	void InformationTemplate::drop()
	{
		delete this;
	}

	//Metoda ładująca dane
	bool InformationTemplate::load(const std::string & name)
	{
		Xml xml(name, "root");
		return load(xml);
	}

	//Wirtualna metoda ładująca dane z xml wywoływana przez implementacje klas potomnych
	bool InformationTemplate::load(Xml & xml)
	{
		//nazwa pliku xml
		m_templ_filename = xml.getFilename();

		//typ obiektu
		if (xml_node<> *node = xml.getRootNode())
			m_templ_type = xml.getString(node, "type");

		//reprezentacja graficzna - tekstury
		if (xml_node<> *node = xml.getChild(xml.getRootNode(), "graphics_configuration"))
		{
			m_templ_texture_digit_name = xml.getString(node, "texture_digit_name");
			m_templ_texture_mask_name = xml.getString(node, "texture_mask_name");
		}

		//transformacja geometryczna
		if (xml_node<> *node = xml.getChild(xml.getRootNode(), "scale"))
		{
			m_templ_tranformable_digit.setScale(xml.getFloat(node, "scale_digit_x"),xml.getFloat(node, "scale_digit_y"));
			m_templ_tranformable_mask.setScale(xml.getFloat(node, "scale_mask_x"),xml.getFloat(node, "scale_mask_y"));
		}
		//wszystkie podklasy sprawdzają, czy xml jest poprawny
		return true;
	}

	//Metoda tworzy obiekt klasy Actor
	Information *InformationTemplate::create(std::wstring id)
	{
		Information* information = gInfoManager.createInformation(id);
		fill(information);
		return information;
	}

	//Wirtualna metoda wypełniająca wskazany obiekt danymi tej klasy
	void InformationTemplate::fill(Information *information)
	{
		//ustawienie kompletnego wzorca
		information->setTemplate(this);

		//próba przekazania tekstur
		information->setTextureDigit(m_templ_texture_digit_name);
		information->setTextureMask(m_templ_texture_mask_name);

		//próba przekazania danych transformacji geometrycznych
		information->setTransformableDigit(m_templ_tranformable_digit);
		information->setTransformableMask(m_templ_tranformable_mask);
	}
}//namespace factory
