﻿//  _________________________________________________
// | PhysicalInfoTemplate.cpp - class implementation |
// | Jack Flower - April 2014                        |
// |_________________________________________________|
//

#include "PhysicalInfoTemplate.h"
#include "../Rendering/Drawable/Layers.h"
#include "../Rendering/Drawable/DrawableManager.h"
#include <SFML/Graphics/RectangleShape.hpp>

using namespace rendering;
using namespace rendering::primitives;

namespace factory
{
	RTTI_IMPL(PhysicalInfoTemplate, PhysicalTemplate);


	//Konstruktor
	PhysicalInfoTemplate::PhysicalInfoTemplate()
	:
		PhysicalTemplate{},//konstruktor klasy bazowej
		m_templ_physical_info_name{ "" },
		m_templ_z_index_rectangle{ Z_PHYSICAL_INFO_STATUS_BAR },
		m_templ_use_status_bar_energy{ false },
		m_templ_use_status_bar_fuel{ false },
		m_templ_color_bar_energy{},
		m_templ_color_bar_fuel{},
		m_templ_size_energy{ 0.0f, 0.0f },
		m_templ_size_fuel{ 0.0f, 0.0f },
		m_templ_position_offset_energy{ 0.0f, 0.0f },
		m_templ_position_offset_fuel{ 0.0f, 0.0f },
		p_templ_status_bar_energy{ nullptr },
		p_templ_status_bar_fuel{ nullptr },
		m_templ_use_animation{ false },
		m_templ_use_texture{ false },
		m_templ_animation_name{},
		m_templ_texture_name{}
	{
	}
	
	//Destruktor wirtualny
	PhysicalInfoTemplate::~PhysicalInfoTemplate()
	{
		//~PhysicalTemplate()
		if(p_templ_status_bar_energy)
			gDrawableManager.destroyDrawable(p_templ_status_bar_energy);
		if(p_templ_status_bar_fuel)
			gDrawableManager.destroyDrawable(p_templ_status_bar_fuel);

		m_templ_physical_info_name = "";
		m_templ_z_index_rectangle = 0;
		m_templ_use_status_bar_energy = false;
		m_templ_use_status_bar_fuel = false;
		m_templ_color_bar_energy;
		m_templ_color_bar_fuel;
		m_templ_size_energy.x = 0.0f;
		m_templ_size_energy.y = 0.0f;
		m_templ_size_fuel.x = 0.0f;
		m_templ_size_fuel.y = 0.0f;
		m_templ_position_offset_energy.x = 0.0f;
		m_templ_position_offset_energy.y = 0.0f;
		m_templ_position_offset_fuel.x = 0.0f;
		m_templ_position_offset_fuel.y = 0.0f;
		p_templ_status_bar_energy = nullptr;
		p_templ_status_bar_fuel = nullptr;
		m_templ_use_animation = false;
		m_templ_use_texture = false;
		m_templ_animation_name = "";
		m_templ_texture_name = "";
	}

	//Metoda zwraca typ obiektu /RTTI/
	const std::string PhysicalInfoTemplate::getType() const
	{
		return rtti.getNameClass();
	}

	//Wirtualna metoda zwalniająca zasób - implementacje w klasach pochodnych
	void PhysicalInfoTemplate::drop()
	{
		delete this;
	}

	//Metoda ładująca dane
	bool PhysicalInfoTemplate::load(const std::string & name)
	{
		Xml xml(name, "root" );
		return load(xml);
	}

	//Wirtualna metoda ładująca dane z xml
	bool PhysicalInfoTemplate::load(Xml & xml)
	{
		//ładowanie danych klasy bazowej Physical
		if (!PhysicalTemplate::load(xml)) return false;

		//odczytanie danych animacji - owner(this) body part
		if (xml_node<> *node = xml.getChild(xml.getRootNode(), "unit_animation"))
		{
			m_templ_use_animation = xml.getBool(node, "use_animation");
			m_templ_animation_name = xml.getString(node, "animation_name");
		}

		//odczytanie danych static image - owner(this) body part
		if (xml_node<> *node = xml.getChild(xml.getRootNode(), "unit_texture"))
		{
			m_templ_use_texture = xml.getBool(node, "use_texture");
			m_templ_texture_name = xml.getString(node, "texture_name");
		}

		//przepisanie do klasy danych z pliku xml
		if (xml_node<> *node = xml.getChild(xml.getRootNode(), "physical_info_config"))
		{
			m_templ_physical_info_name = xml.getString(node, "physical_info_name");
			m_templ_use_status_bar_energy = xml.getBool(node, "use_status_bar_energy");
			m_templ_use_status_bar_fuel = xml.getBool(node, "use_status_bar_fuel");
			m_templ_color_bar_energy.r = xml.getInt(node, "energy_bar_color_red");
			m_templ_color_bar_energy.g = xml.getInt(node, "energy_bar_color_green");
			m_templ_color_bar_energy.b = xml.getInt(node, "energy_bar_color_blue");
			m_templ_color_bar_energy.a = xml.getInt(node, "energy_bar_color_alpha");
			m_templ_color_bar_fuel.r = xml.getInt(node, "fuel_bar_color_red");
			m_templ_color_bar_fuel.g = xml.getInt(node, "fuel_bar_color_green");
			m_templ_color_bar_fuel.b = xml.getInt(node, "fuel_bar_color_blue");
			m_templ_color_bar_fuel.a = xml.getInt(node, "fuel_bar_color_alpha");
			m_templ_size_energy.x = xml.getFloat(node, "size_energy_x");
			m_templ_size_energy.y = xml.getFloat(node, "size_energy_y");
			m_templ_size_fuel.x = xml.getFloat(node, "size_fuel_x");
			m_templ_size_fuel.y = xml.getFloat(node, "size_fuel_y");
			m_templ_position_offset_energy.x = xml.getFloat(node, "position_offset_energy_x");
			m_templ_position_offset_energy.y = xml.getFloat(node, "position_offset_energy_y");
			m_templ_position_offset_fuel.x = xml.getFloat(node, "position_offset_fuel_x");
			m_templ_position_offset_fuel.y = xml.getFloat(node, "position_offset_fuel_y");
		}
		//wszystkie podklasy sprawdzają, czy xml jest poprawny
		return true;
	}

	//Metoda tworzy obiekt klasy PhysicalInfo
	PhysicalInfo *PhysicalInfoTemplate::create(std::wstring id)
	{
		PhysicalInfo *physical_info = gPhysicalManager.createPhysicalInfo(id);
		fill(physical_info);
		return physical_info;
	}

	//Wirtualna metoda wypełniająca wskazany obiekt danymi tej klasy
	void PhysicalInfoTemplate::fill(PhysicalInfo *p_physical_info)
	{
		if(p_physical_info)
		{
			PhysicalTemplate::fill(p_physical_info);
			//składowe tej klasy			
			p_physical_info->setPhysicalInfoName(m_templ_physical_info_name);
			p_physical_info->setZIndexRectangle(m_templ_z_index_rectangle);
			p_physical_info->setUseStatusBarEnergy(m_templ_use_status_bar_energy);
			p_physical_info->setUseStatusBarFuel(m_templ_use_status_bar_fuel);

			//animacja/tekstura - owner(this) body part
			if(m_templ_use_animation)
				p_physical_info->setAnimationBody(m_templ_animation_name);

			//tekstura/animacja - owner(this) body part
			if(m_templ_use_texture)
				p_physical_info->setTextureBody(m_templ_texture_name);

			//wskaźnik energii
			if(m_templ_use_status_bar_energy)
			{
				//wymuszam utworzenie obiektu
				p_physical_info->initStatusBarEnergy();
				//kolor status progress bar (energia-życie)
				p_physical_info->setFillColorEnergy(m_templ_color_bar_energy);
				//rozmiar paska - progress bar (energia-życie)
				p_physical_info->setEnergyStatusBarSize(m_templ_size_energy);
				//wektor kalibracji położenia obiektu - progress bar (energia-życie)
				p_physical_info->setEnergyPositionStatusBarOffset(m_templ_position_offset_energy);
			}

			//wskaźnik paliwa
			if(m_templ_use_status_bar_fuel)
			{
				//wymuszam utworzenie obiektu
				p_physical_info->initStatusBarFuel();
				//kolor status progress bar (energia-życie)
				p_physical_info->setFillColorFuel(m_templ_color_bar_fuel);
				//rozmiar paska - progress bar (energia-życie)
				p_physical_info->setFuelStatusBarSize(m_templ_size_fuel);
				//wektor kalibracji położenia obiektu - progress bar (energia-życie)
				p_physical_info->setFuelPositionStatusBarOffset(m_templ_position_offset_fuel);
			}
		}
	}
}//namespace factory
