//  _______________________________________
// | CPhysical.cpp - class implementation  |
// | Jack Flower - August 2012             |
// |_______________________________________|
//

#include "CPhysical.h"
#include "../../Weather/CWeather.h"
#include "../../Rendering/Displayable/CDisplayable.h"
#include "../../Rendering/Drawable/CDrawableManager.h"
#include "../../Rendering/Animations/CAnimation.h"
#include "../../Rendering/Animations/CAnimationState.h"
#include "../../Factory/PhysicalTemplate.h"
#include "../../Utilities/Utilities/Utilities.h"
#include <math.h>

using namespace weather;

namespace logic
{
	RTTI_IMPL_NOPARENT(CPhysical);

	//Chroniony konstruktor domy�lny - u�ywany wy��cznie przez CPhysicalManager
	CPhysical::CPhysical(const std::wstring & uniqueId)
	:
		//private:
		m_physical_manager_index	(-1),
		m_physical_data				(),
		m_smooth					(false),
		
		//protected:
		m_unique_id					(uniqueId),
		m_genre						(),
		m_circle_radius				(1.0f),
		m_collision_shape			(SHAPE_CIRCLE),
		m_rect_size					(1.0f, 1.0f),
		m_rect_size_body			(1.0f, 1.0f),
		m_rect_size_head			(1.0f, 1.0f),
		p_template					(NULL),
		m_ready_for_destruction		(false),
		m_part_collision_data		(),
		m_new_anim_speed			(1.0f)
	{
	}

	//Chroniony konstruktor kopiuj�cy
	CPhysical::CPhysical(const CPhysical & CPhysicalCopy)
	:
		//private:
		m_physical_manager_index	(CPhysicalCopy.m_physical_manager_index),
		m_physical_data				(CPhysicalCopy.m_physical_data),
		m_smooth					(CPhysicalCopy.m_smooth),
		
		//protected:
		m_unique_id					(CPhysicalCopy.m_unique_id),
		m_genre						(CPhysicalCopy.m_genre),
		m_circle_radius				(CPhysicalCopy.m_circle_radius),
		m_collision_shape			(CPhysicalCopy.m_collision_shape),
		m_rect_size					(CPhysicalCopy.m_rect_size),
		m_rect_size_body			(CPhysicalCopy.m_rect_size_body),
		m_rect_size_head			(CPhysicalCopy.m_rect_size_head),
		p_template					(CPhysicalCopy.p_template),
		m_ready_for_destruction		(CPhysicalCopy.m_ready_for_destruction),
		m_part_collision_data		(CPhysicalCopy.m_part_collision_data),
		m_new_anim_speed			(CPhysicalCopy.m_new_anim_speed)
	{
	}

	//Chroniony destruktor wirtualny - u�ywany wy��cznie przez CPhysicalManager
	CPhysical::~CPhysical()
	{
		//private:
		m_physical_manager_index	= 0;
		m_smooth					= false;

		//protected:
		m_unique_id					= L"";
		m_genre						= L"";
		//m_physics_data			not edit
		m_circle_radius				= 0.0f;
		m_rect_size.x				= 0.0f;
		m_rect_size.y				= 0.0f;
		m_rect_size_body.x			= 0.0f;
		m_rect_size_body.y			= 0.0f;
		m_rect_size_head.x			= 0.0f;
		m_rect_size_head.y			= 0.0f;
		p_template					= NULL;
		m_ready_for_destruction		= false;
		//m_part_collision_data		not edit
		m_new_anim_speed			= 0.0f;
	}

	//Metoda zwraca typ obiektu /RTTI/
	const std::string CPhysical::GetType() const
	{
		return rtti.GetNameClass();
	}

	//Metoda zwraca unikaln� nazw� obiektu klasy CPhysical
	const std::wstring & CPhysical::GetUniqueId() const
	{
		return m_unique_id;
	}

	//Metoda zwraca nazw� gatunku
	const std::wstring & CPhysical::GetGenre()
	{
		return m_genre; 
	}

	//Metoda zwraca wag�
	const float CPhysical::getWeight() const
	{
		return m_physical_data.getWeight();
	}

	//Metoda ustawia wag�
	void CPhysical::setWeight(float weight)
	{
		if (weight < 0) return;
		m_physical_data.setWeight(weight);
	}

	//Metoda zwraca kategor� CPhysical
	physCategory CPhysical::GetCategory()
	{
		return m_category;
	}

	//Metoda ustawia kategori� CPhysical
	void CPhysical::SetCategory(physCategory category)
	{
		m_category = category;
	}

	//Metoda ustawia kategori� CPhysical
	void CPhysical::SetCategory(const std::wstring & category_name)
	{
		//parsowanie kategorii na podstawie tablicy nazw kategorii
		//docelowo napisa� jaki� prosty translator...
		if (category_name == L"detector")
			m_category = PHYSICAL_DETECTOR;
		else if (category_name == L"player")
			m_category = PHYSICAL_PLAYER;
		else if (category_name == L"monster")
			m_category = PHYSICAL_MONSTER;
		else if (category_name == L"npc")
			m_category = PHYSICAL_NPC;
		else if (category_name == L"bullet")
			m_category = PHYSICAL_BULLET;
		else if (category_name == L"lair")
			m_category = PHYSICAL_LAIR;
		else if (category_name == L"wall")
			m_category = PHYSICAL_WALL;
		else if (category_name == L"item")
			m_category = PHYSICAL_ITEM;
		else if (category_name == L"door")
			m_category = PHYSICAL_DOOR;
		else if (category_name == L"trap")
			m_category = PHYSICAL_TRAP;
		else if (category_name == L"region")
			m_category = PHYSICAL_REGION;
		else if (category_name == L"obstacle")
			m_category = PHYSICAL_OBSTACLE;
		else if (category_name == L"hook")
			m_category = PHYSICAL_HOOK;
		else 
			fprintf(stderr, "unrecognised physical category: %ls for physical %ls\n", category_name.c_str(), GetUniqueId().c_str());
	}

	//Metoda ustawia nazw� gatunku
	void CPhysical::SetGenre(const std::wstring & genre)
	{
		m_genre = genre; 
	}

	//Metoda zwraca pozycj� obiektu
	const sf::Vector2f & CPhysical::GetPosition() const
	{
		return m_physical_data.getPosition();
	}

	//Metoda ustawia pozycj� obiektu
	void CPhysical::SetPosition(float x, float y, bool change_old_position)
	{
		m_physical_data.setPosition(x, y);
	}

	//Metoda ustawia pozycj� obiektu
	void CPhysical::SetPosition(const sf::Vector2f & new_value, bool change_old_position)
	{
		m_physical_data.setPosition(new_value);
	}

	//Metoda zwraca pozycj� przed aktualizacj� logiki m_old_position
	const sf::Vector2f & CPhysical::GetOldPosition() const
	{
		return m_physical_data.getOldPosition();
	}

	//Metoda zwraca skal� (body)
	const sf::Vector2f & CPhysical::GetScaleBody() const
	{
		return m_physical_data.getDisplayableBody()->getScale();
	}

	//Metoda ustawia skal� (body)
	void CPhysical::SetScaleBody(float scale_X, float scale_Y)
	{
		//zapami�tuj� skal�
		m_physical_data.setStoredScaleBody(scale_X, scale_Y);

		//obiekt zasadniczy i cie� zawsze maj� t� sam� skal�
		if(m_physical_data.getDisplayableBody())
			m_physical_data.getDisplayableBody()->setScale(scale_X, scale_Y);

		if(m_physical_data.getDisplayableBodyShadow())
			m_physical_data.getDisplayableBodyShadow()->setScale(scale_X, scale_Y);
	}

	//Metoda ustawia skal� (body)
	void CPhysical::SetScaleBody(const sf::Vector2f & scale_vector)
	{
		//zapami�tuj� skal�
		m_physical_data.setStoredScaleBody(scale_vector);

		//obiekt zasadniczy i cie� zawsze maj� t� sam� skal�
		if(m_physical_data.getDisplayableBody())
			m_physical_data.getDisplayableBody()->setScale(scale_vector);

		if(m_physical_data.getDisplayableBodyShadow())
			m_physical_data.getDisplayableBodyShadow()->setScale(scale_vector);
	}

	//Metoda zwraca skal� (body)
	const sf::Vector2f & CPhysical::GetScaleHead() const
	{
		return m_physical_data.getDisplayableHead()->getScale();
	}

	//Metoda ustawia skal� (head)
	void CPhysical::SetScaleHead(float scale_X, float scale_Y)
	{
		//zapami�tuj� skal�
		m_physical_data.setStoredScaleHead(scale_X, scale_Y);

		//obiekt zasadniczy i cie� zawsze maj� t� sam� skal�
		if(m_physical_data.getDisplayableHead())
			m_physical_data.getDisplayableHead()->setScale(scale_X, scale_Y);

		if(m_physical_data.getDisplayableHeadShadow())
			m_physical_data.getDisplayableHeadShadow()->setScale(scale_X, scale_Y);
	}

	//Metoda ustawia skal� (head)
	void CPhysical::SetScaleHead(const sf::Vector2f & scale_vector)
	{
		//zapami�tuj� skal�
		m_physical_data.setStoredScaleHead(scale_vector);

		//obiekt zasadniczy i cie� zawsze maj� t� sam� skal�
		if(m_physical_data.getDisplayableHead())
			m_physical_data.getDisplayableHead()->setScale(scale_vector);

		if(m_physical_data.getDisplayableHeadShadow())
			m_physical_data.getDisplayableHeadShadow()->setScale(scale_vector);
	}

	//Metoda ustawia skal� (body and head)
	void CPhysical::SetScale(float scale_X, float scale_Y)
	{
		//zapami�tuj� skal�
		m_physical_data.setStoredScaleBody(scale_X, scale_Y);

		//zapami�tuj� skal�
		m_physical_data.setStoredScaleHead(scale_X, scale_Y);

		//obiekt zasadniczy i cie� zawsze maj� t� sam� skal�
		if(m_physical_data.getDisplayableBody())
			m_physical_data.getDisplayableBody()->setScale(scale_X, scale_Y);

		if(m_physical_data.getDisplayableBodyShadow())
			m_physical_data.getDisplayableBodyShadow()->setScale(scale_X, scale_Y);

		//obiekt zasadniczy i cie� zawsze maj� t� sam� skal�
		if(m_physical_data.getDisplayableHead())
			m_physical_data.getDisplayableHead()->setScale(scale_X, scale_Y);

		if(m_physical_data.getDisplayableHeadShadow())
			m_physical_data.getDisplayableHeadShadow()->setScale(scale_X, scale_Y);
	}

	//Metoda ustawia skal� (body and head)
	void CPhysical::SetScale(const sf::Vector2f & scale)
	{
		//zapami�tuj� skal�
		m_physical_data.setStoredScaleBody(scale);
		m_physical_data.setStoredScaleHead(scale);

		//obiekt zasadniczy i cie� zawsze maj� t� sam� skal�
		if(m_physical_data.getDisplayableBody())
			m_physical_data.getDisplayableBody()->setScale(scale);

		if (m_physical_data.getDisplayableBodyShadow())
			m_physical_data.getDisplayableBodyShadow()->setScale(scale);

		//obiekt zasadniczy i cie� zawsze maj� t� sam� skal�
		if(m_physical_data.getDisplayableHead())
			m_physical_data.getDisplayableHead()->setScale(scale);

		if (m_physical_data.getDisplayableHeadShadow())
			m_physical_data.getDisplayableHeadShadow()->setScale(scale);
	}

	//Metoda ustawia skal�
	void CPhysical::SetScale(float uniform)
	{
		//zapami�tuj� skal�
		m_physical_data.setStoredScaleBody(uniform, uniform);

		//obiekt zasadniczy i cie� zawsze maj� t� sam� skal�
		if(m_physical_data.getDisplayableBody())
			m_physical_data.getDisplayableBody()->setScale(uniform);

		if (m_physical_data.getDisplayableHead())
			m_physical_data.getDisplayableHead()->setScale(uniform);

		//obiekt zasadniczy i cie� zawsze maj� t� sam� skal�
		if(m_physical_data.getDisplayableBodyShadow())
			m_physical_data.getDisplayableBodyShadow()->setScale(uniform);

		if (m_physical_data.getDisplayableHeadShadow())
			m_physical_data.getDisplayableHeadShadow()->setScale(uniform);
	}

	//Metoda zwraca warto�� obrotu obiektu w stopniach
	const float CPhysical::GetRotation() const
	{
		return m_physical_data.getRotation();
	}

	//Metoda ustawia warto�� obrotu obiektu w stopniach (body and head)
	void CPhysical::SetRotation(float rotation)
	{
		m_physical_data.setRotation(rotation);
	}

	//Metoda zwraca warto�� obrotu obiektu w stopniach (body)
	const float CPhysical::GetRotationBody() const
	{
		return m_physical_data.getRotationBody();
	}

	//Metoda ustawia warto�� obrotu obiektu w stopniach (body)
	void CPhysical::SetRotationBody(float rotation_body)
	{
		m_physical_data.setRotationBody(rotation_body);
	}

	//Metoda zwraca warto�� obrotu obiektu w stopniach (head)
	const float CPhysical::GetRotationHead() const
	{
		return m_physical_data.getRotationHead();
	}

	//Metoda ustawia warto�� obrotu obiektu w stopniach (head)
	void CPhysical::SetRotationHead(float rotation_head)
	{
		m_physical_data.setRotationHead(rotation_head);
	}

	//Metoda obraca obiekt o zadany k�t (body)
	void CPhysical::RotateBody(float angle)
	{
		m_physical_data.rotateBody(angle);
	}

	//Metoda obraca obiekt o zadany k�t (head)
	void CPhysical::RotateHead(float angle)
	{
		m_physical_data.rotateHead(angle);
	}

	//Metoda obraca obiekt o zadany k�t (body and head)
	void CPhysical::Rotate(float angle)
	{
		RotateBody(angle);
		RotateHead(angle);
	}

	//Metoda zwraca pr�dko�� obiektu
	const sf::Vector2f & CPhysical::GetVelocity() const
	{
		return m_physical_data.getVelocity();
	}

	//Metoda ustawia pr�dko�� obiektu
	void CPhysical::SetVelocity(const sf::Vector2f & velocity)
	{
		m_physical_data.setVelocity(velocity);
	}

	//Metoda zwraca promie� detekcji wykorzystywany przy liczeniu kolizji
	float CPhysical::GetCircleRadius()
	{
		return m_circle_radius;
	}

	//Metoda zwraca wyliczenie - typ liczenia kolizji
	ECollisionShape CPhysical::GetCollisionShape()
	{
		return m_collision_shape;
	}

	//Wirtualna metoda ustawiaj�ca warto�� promienia detekcji wykorzystywan� przy liczeniu kolizji
	void CPhysical::SetBoundingCircle(float radius)
	{
		m_collision_shape = SHAPE_CIRCLE;
		m_circle_radius = radius;
		//obliczamy boki prostok�ta (uproszczenie do kwadratu) wpisanego w okrag
		m_rect_size.x = m_rect_size.y = radius * 2.0f;
	}

	//Metoda ustawia warto�� obszaru prostok�tnego detekcji wykorzystywany przy liczeniu kolizji
	void CPhysical::SetBoundingRect(const sf::Vector2f & rect_size)
	{
		m_collision_shape = SHAPE_RECT;
		m_rect_size = rect_size;
		//obliczamy przeciwprostok�tn�, czyli �rednic� okr�gu opisanego na prostok�cie
		m_circle_radius =  sqrtf(rect_size.x * rect_size.x + rect_size.y * rect_size.y);
	}

	//Metoda zwraca wektor dla obszaru prostok�tnego detekcji wykorzystywany przy liczeniu kolizji
	const sf::Vector2f & CPhysical::GetRectSize() const
	{
		return m_rect_size;
	}

	//Metoda zwraca sta�� referencj� na wektor wielko�ci obiektu
	//wykorzytywana przy tworzeniu syntetyk�w - tekstur dla obiekt�w
	const sf::Vector2f & CPhysical::GetRectangleSizeBody() const
	{
		return m_rect_size_body;
	}

	//Metoda ustawia referencj� na wektor wielko�ci obiektu
	//wykorzytywana przy tworzeniu syntetyk�w - tekstur dla obiekt�w
	void CPhysical::SetRectangleSizeBody(const sf::Vector2f & rect_size_body)
	{
		m_rect_size_body = rect_size_body;
	}

	//Metoda ustawia referencj� na wektor wielko�ci obiektu
	//wykorzytywana przy tworzeniu syntetyk�w - tekstur dla obiekt�w
	void CPhysical::SetRectangleSizeBody(float rect_size_body_width, float rect_size_body_height)
	{
		m_rect_size_body.x = rect_size_body_width;
		m_rect_size_body.y = rect_size_body_height;
	}
	
	//Metoda zwraca sta�� referencj� na wektor wielko�ci obiektu
	//wykorzytywana przy tworzeniu syntetyk�w - tekstur dla obiekt�w
	//klasy CDisplayable
	const sf::Vector2f & CPhysical::GetRectangleSizeHead() const
	{
		return m_rect_size_head;
	}

	//Metoda ustawia referencj� na wektor wielko�ci obiektu
	//wykorzytywana przy tworzeniu syntetyk�w - tekstur dla obiekt�w
	//klasy CDisplayable
	void CPhysical::SetRectangleSizeHead(const sf::Vector2f & rect_size_head)
	{
		m_rect_size_head = rect_size_head;
		m_rect_size_head = rect_size_head;
	}

	//Metoda ustawia referencj� na wektor wielko�ci obiektu
	//wykorzytywana przy tworzeniu syntetyk�w - tekstur dla obiekt�w
	//klasy CDisplayable
	void CPhysical::SetRectangleSizeHead(float rect_size_head_width, float rect_size_head_height)
	{
		m_rect_size_head.x = rect_size_head_width;
	}

	//Metoda ustawia referencj� na wektor wielko�ci obiektu
	//wykorzytywana przy tworzeniu syntetyk�w - tekstur dla obiekt�w
	//klasy CDisplayable - body and head
	void CPhysical::SetRectangleSize(const sf::Vector2f & rect_size_uniform)
	{
		m_rect_size_body = rect_size_uniform;
		m_rect_size_head = rect_size_uniform;
	}

	//Metoda ustawia referencj� na wektor wielko�ci obiektu
	void CPhysical::SetRectangleSize(float rect_size_uniform_width, float rect_size_uniform_height)
	{
		m_rect_size_body.x = rect_size_uniform_width;
		m_rect_size_body.y = rect_size_uniform_height;
		m_rect_size_head.x = rect_size_uniform_width;
		m_rect_size_head.y = rect_size_uniform_height;
	}

	//Metoda ustawia referencj� na wektor wielko�ci obiektu
	//wykorzytywana przy tworzeniu syntetyk�w - tekstur dla obiekt�w
	//klasy CDisplayable - body and head
	void CPhysical::SetRectangleSize(const sf::Vector2f & rect_size_body, const sf::Vector2f & rect_size_head)
	{
		m_rect_size_body = rect_size_body;
		m_rect_size_head = rect_size_head;
	}

	//Metoda ustawia referencj� na wektor wielko�ci obiektu
	//wykorzytywana przy tworzeniu syntetyk�w - tekstur dla obiekt�w
	//klasy CDisplayable - body and head
	void CPhysical::SetRectangleSize(float rect_size_body_width, float rect_size_body_height, float rect_size_head_width, float rect_size_head_height)
	{
		m_rect_size_body.x = rect_size_body_width;
		m_rect_size_body.y = rect_size_body_height;
		m_rect_size_head.x = rect_size_head_width;
		m_rect_size_head.y = rect_size_head_height;
	}

	//Metoda zwraca warto�� pu�apu obiektu
	const float CPhysical::GetAltitude() const
	{
		return m_physical_data.getAltitude();
	}

	//Metoda ustawia warto�� pu�apu obiektu
	void CPhysical::SetAltitude(float altitude)
	{
		if(altitude < 0) return;
		m_physical_data.setAltitude(altitude);
	}

	//Metoda zwraca kolor obiektu - body
	const sf::Color & CPhysical::GetColor() const
	{
		return m_physical_data.getColorBody();	//umawiamy si�, �e default to cz�� body
	}

	//Metoda ustawia kolor obiektu - (body and head)
	void CPhysical::SetColor(const sf::Color & color)
	{
		m_physical_data.setColor(color);
	}

	//Metoda zwraca kolor obiektu - body
	const sf::Color & CPhysical::GetColorBody() const
	{
		return m_physical_data.getColorBody();
	}

	//Metoda ustawia kolor obiektu - body
	void CPhysical::SetColorBody(const sf::Color & color_body)
	{
		m_physical_data.setColorBody(color_body);
	}

	//Metoda zwraca kolor obiektu - head
	const sf::Color & CPhysical::GetColorHead() const
	{
		return m_physical_data.getColorHead();
	}

	//Metoda ustawia kolor obiektu - head
	void CPhysical::SetColorHead(const sf::Color & color_head)
	{
		m_physical_data.setColorHead(color_head);
	}

	//Metoda ustawia oryginalny kolor obiektu za�adowany z tekstury - body and head
	void CPhysical::RestoreColor()
	{
		m_physical_data.restoreColor();
	}

	//Metoda ustawia oryginalny kolor obiektu za�adowany z tekstury - body
	void CPhysical::RestoreColorBody()
	{
		m_physical_data.restoreColorBody();
	}

	//Metoda ustawia oryginalny kolor obiektu za�adowany z tekstury - head
	void CPhysical::RestoreColorHead()
	{
		m_physical_data.restoreColorHead();
	}

	//Metoda ustawia kolor do zapami�tania - body
	const sf::Color & CPhysical::GetStoredColorBody() const
	{
		return m_physical_data.getStoredColorBody();
	}

	//Metoda ustawia kolor do zapami�tania - body
	void CPhysical::StoreColorBody(const sf::Color & color_stored_body)
	{
		m_physical_data.storeColorBody(color_stored_body);
	}
	
	//Metoda ustawia kolor do zapami�tania - body
	const sf::Color & CPhysical::GetStoredColorHead() const
	{
		return m_physical_data.getStoredColorHead();
	}

	//Metoda ustawia kolor do zapami�tania - body
	void CPhysical::StoreColorHead(const sf::Color & color_stored_head)
	{
		m_physical_data.storeColorHead(color_stored_head);
	}

	//Metoda zwraca kolor cienia obiektu
	const sf::Color & CPhysical::GetColorShadow() const
	{
		return m_physical_data.getColorShadow();
	}

	//Metoda ustawia kolor cienia obiektu
	void CPhysical::SetColorShadow(const sf::Color & color_shadow)
	{
		m_physical_data.setColorShadow(color_shadow);
	}

	//Metoda zwraca wektor przesuni�cia cienia wzgl�dem obiektu - body
	sf::Vector2f & CPhysical::GetShadowOffsetBody()
	{
		return m_physical_data.getShadowOffsetBody();
	}

	//Metoda ustawia wektor przesuni�cia cienia wzgl�dem obiektu - body
	void CPhysical::SetShadowOffsetBody(sf::Vector2f & shadow_offset_body)
	{
		m_physical_data.setShadowOffsetBody(shadow_offset_body);
	}

	//Metoda zwraca wektor przesuni�cia cienia wzgl�dem obiektu - head
	sf::Vector2f & CPhysical::GetShadowOffsetHead()
	{
		return m_physical_data.getShadowOffsetHead();
	}

	//Metoda ustawia wektor przesuni�cia cienia wzgl�dem obiektu - head
	void CPhysical::SetShadowOffsetHead(sf::Vector2f & shadow_offset_head)
	{
		m_physical_data.setShadowOffsetHead(shadow_offset_head);
	}

	//Metoda zwraca flag�, czy obiekt generuje reprezentacj� graficzn� (body and head) /zgodno�� interfejsu/
	const bool CPhysical::GetUseDisplayable() const
	{
		return m_physical_data.getUseDisplayableBody();
	}

	//Metoda zwraca flag�, czy CPhysical ma reprezentacj� graficz� (body)
	const bool CPhysical::GetUseDisplayableBody() const
	{
		return m_physical_data.getUseDisplayableBody();
	}

	//Metoda zwraca flag�, czy CPhysical ma reprezentacj� graficz� (head)
	const bool CPhysical::GetUseDisplayableHead() const
	{
		return m_physical_data.getUseDisplayableHead();
	}

	//Metoda ustawia flag�, czy CPhysical ma reprezentacj� graficz� (body and head)
	void CPhysical::SetUseDisplayable(const bool use_displayable)
	{
		m_physical_data.setUseDisplayable(use_displayable);
	}

	//Metoda ustawia flag�, czy CPhysical ma reprezentacj� graficz� (body)
	void CPhysical::SetUseDisplayableBody(const bool use_displayable_body)
	{
		m_physical_data.setUseDisplayableBody(use_displayable_body);
	}

	//Metoda ustawia flag�, czy CPhysical ma reprezentacj� graficz� (head)
	void CPhysical::SetUseDisplayableHead(const bool use_displayable_head)
	{
		m_physical_data.setUseDisplayableHead(use_displayable_head);
	}

	//Metoda zwraca flag�, czy obiekt generuje cie� (body and head) /zgodno�� interfejsu/
	const bool CPhysical::GetUseShadow() const
	{
		return m_physical_data.getUseShadowBody();
	}

	//Metoda zwraca flag�, czy obiekt generuje cie� (body)
	const bool CPhysical::GetUseShadowBody() const
	{
		return m_physical_data.getUseShadowBody();
	}

	//Metoda zwraca flag�, czy obiekt generuje cie� (head)
	const bool CPhysical::GetUseShadowHead() const
	{
		return m_physical_data.getUseShadowHead();
	}

	//Metoda ustawia flag�, czy obiekt ma generowa� cie� (body and head) /zgodno�� interfejsu/
	void CPhysical::SetUseShadow(const bool use_shadow)
	{
		m_physical_data.setUseShadow(use_shadow);
	}

	//Metoda ustawia flag�, czy obiekt ma generowa� cie� (body)
	void CPhysical::SetUseShadowBody(const bool use_shadow_body)
	{
		m_physical_data.setUseShadowBody(use_shadow_body);
	}

	//Metoda ustawia flag�, czy obiekt ma generowa� cie� (head)
	void CPhysical::SetUseShadowHead(const bool use_shadow_head)
	{
		m_physical_data.setUseShadowHead(use_shadow_head);
	}

	//Metoda zwraca wska�nik na animacj� - obiekt klasy CAnimation (body)
	CAnimation *CPhysical::GetAnimationBody()
	{
		return m_physical_data.getAnimationBody();
	}

	//Metoda ustawia ustawia wska�nik na animacj� (body)
	void CPhysical::SetAnimationBody(CAnimation* p_anim_body)
	{
		m_physical_data.setAnimationBody(p_anim_body);
	}

	//Metoda zwraca nazw� animacji (body)
	const std::string & CPhysical::GetAnimationBodyName() const
	{
		return m_physical_data.getAnimationBodyName();
	}

	//Metoda ustawia nazw� animacji (body)
	void CPhysical::SetAnimationBody(const std::string & anim_body_name)
	{
		m_physical_data.setAnimationBody(anim_body_name);
	}

	//Metoda zwraca wska�nik na animacj� - obiekt klasy CAnimation (head)
	CAnimation *CPhysical::GetAnimationHead()
	{
		return m_physical_data.getAnimationHead();
	}

	//Metoda ustawia ustawia wska�nik na animacj� (head)
	void CPhysical::SetAnimationHead(CAnimation *p_anim_head)
	{
		m_physical_data.setAnimationHead(p_anim_head);
	}

	//Metoda zwraca nazw� animacji (head)
	const std::string & CPhysical::GetAnimationHeadName() const
	{
		return m_physical_data.getAnimationHeadName();
	}

	//Metoda ustawia nazw� animacji (head)
	void CPhysical::SetAnimationHead(const std::string & anim_head_name)
	{
		m_physical_data.setAnimationHead(anim_head_name);
	}

	//Metoda ustawia komplet animacji
	void CPhysical::SetAnimation(CAnimation *p_anim_body, CAnimation *p_anim_head)
	{
		SetAnimationBody(p_anim_body);
		SetAnimationHead(p_anim_head);
	}

	//Metoda ustawia komplet animacji
	void CPhysical::SetAnimation(const std::string & anim_name_body, const std::string & anim_name_head)
	{
		SetAnimationBody(anim_name_body);
		SetAnimationHead(anim_name_head);
	}

	//Metoda zwraca pami�tany wsp�czynnik pr�dko�ci odtwarzania animacji (body)
	const float CPhysical::GetStoredAnimSpeedBody() const
	{
		return m_physical_data.getStoredAnimSpeedBody();
	}

	//Metoda zwraca pami�tany wsp�czynnik pr�dko�ci odtwarzania animacji (body)
	const float CPhysical::GetStoredAnimSpeedHead() const
	{
		return m_physical_data.getStoredAnimSpeedHead();
	}

	//Metoda zwraca wsp�czynnik pr�dko�ci odtwarzania animacji 1.0f - normal speed (body)
	const float CPhysical::GetAnimSpeedBody() const
	{
		return m_physical_data.getAnimSpeedBody();
	}

	//Metoda zwraca wsp�czynnik pr�dko�ci odtwarzania animacji 1.0f - normal speed (head)
	const float CPhysical::GetAnimSpeedHead() const
	{
		return m_physical_data.getAnimSpeedHead();
	}

	//Metoda ustawia wsp�czynnik pr�dko�ci odtwarzania animacji 1.0f - normal speed (body)
	void CPhysical::SetAnimSpeedBody(float anim_speed)
	{
		m_physical_data.setAnimSpeedBody(anim_speed);
	}

	//Metoda ustawia wsp�czynnik pr�dko�ci odtwarzania animacji 1.0f - normal speed (head)
	void CPhysical::SetAnimSpeedHead(float anim_speed)
	{
		m_physical_data.setAnimSpeedHead(anim_speed);
	}

	//Metoda ustawia wsp�czynnik pr�dko�ci odtwarzania animacji 1.0f - normal speed (body and head)
	void CPhysical::SetAnimSpeed(float anim_uniform_speed)
	{
		SetAnimSpeedBody(anim_uniform_speed);
		SetAnimSpeedHead(anim_uniform_speed);
	}

	//Metoda ustawia wsp�czynnik pr�dko�ci odtwarzania animacji 1.0f - normal speed (body and head)
	void CPhysical::SetAnimSpeed(float anim_speed_body, float anim_speed_head)
	{
		SetAnimSpeedBody(anim_speed_body);
		SetAnimSpeedHead(anim_speed_head);
	}

	//Metoda zwraca wska�nik na obiekt klasy CDisplayable (body) /zgodno�� interfejsu/
	CDisplayable *CPhysical::GetDisplayable()
	{
		return m_physical_data.getDisplayableBody();
	}

	//Metoda zwraca wska�nik na obiekt klasy CDisplayable (shadow) /zgodno�� interfejsu/
	CDisplayable *CPhysical::GetShadow()
	{
		return m_physical_data.getDisplayableBodyShadow();
	}

	//Metoda zwraca wska�nik na obiekt klasy CDisplayable (body)
	CDisplayable *CPhysical::GetDisplayable(EPhysicalPart physical_part)
	{
		if (physical_part == BODY)
			return m_physical_data.getDisplayableBody();
		else if (physical_part == HEAD)
			return m_physical_data.getDisplayableHead();
		return m_physical_data.getDisplayableBody();
	}

	//Metoda zwraca wska�nik na obiekt klasy CDisplayable (shadow)
	CDisplayable *CPhysical::GetShadow(EPhysicalPart physical_part)
	{
		if (physical_part == BODY)
			return m_physical_data.getDisplayableBodyShadow();
		else if (physical_part == HEAD)
			return m_physical_data.getDisplayableHead();
		return m_physical_data.getDisplayableBodyShadow();
	}

	//Metoda zwraca wska�nik na obiekt klasy CDisplayable (body)
	CDisplayable *CPhysical::GetDisplayableBody()
	{
		return m_physical_data.getDisplayableBody();
	}

	//Metoda zwraca wska�nik na obiekt klasy CDisplayable (body shadow)
	CDisplayable *CPhysical::GetDisplayableBodyShadow()
	{
		return m_physical_data.getDisplayableBodyShadow();
	}

	//Metoda zwraca wska�nik na obiekt klasy CDisplayable (head)
	CDisplayable *CPhysical::GetDisplayableHead()
	{
		return m_physical_data.getDisplayableHead();
	}

	//Metoda zwraca wska�nik na obiekt klasy CDisplayable (head shadow)
	CDisplayable *CPhysical::GetDisplayableHeadShadow()
	{
		return m_physical_data.getDisplayableHeadShadow();
	}

	//Metoda ustawia flag� dla obiekt�w gotowych do destrukcji
	void CPhysical::MarkForDelete()
	{
		m_ready_for_destruction = true;
	}

	//Wirtualna metoda zaznacza obiekty do destrukcji
	void CPhysical::kill()
	{
		MarkForDelete();
	}

	//Metoda zwraca flag�, czy obiekt jest gotowy do usuniecia
	bool CPhysical::IsDead()
	{
		return m_ready_for_destruction;
	}

	//Metoda zwraca nazw� tekstury
	const std::string & CPhysical::GetTextureBody() const
	{
		return m_physical_data.getTextureBody();
	}

	//Metoda ustatawia nazw� tekstury (body)
	void CPhysical::SetTextureBody(const std::string & texture_body)
	{
		m_physical_data.setTextureBody(texture_body);
	}

	//Metoda zwraca nazw� tekstury (head)
	const std::string & CPhysical::GetTextureHead() const
	{
		return m_physical_data.getTextureHead();
	}

	//Metoda ustatwia nazw� tekstury (head)
	void CPhysical::SetTextureHead(const std::string & texture_head)
	{
		m_physical_data.setTextureHead(texture_head);
	}

	//Metoda generuje obraz tekstury
	void CPhysical::SetTextureBody(unsigned width, unsigned height, const sf::Color & color)
	{
		m_physical_data.setTextureBody(width, height, color);
	}

	//Metoda generuje obraz tekstury
	void CPhysical::SetTextureBody(unsigned width, unsigned height, unsigned r, unsigned g, unsigned b, unsigned a)
	{
		m_physical_data.setTextureBody(width, height, r, g, b, a);
	}

	//Metoda generuje obraz tekstury
	void CPhysical::SetTextureHead(unsigned width, unsigned height, const sf::Color & color)
	{
		m_physical_data.setTextureHead(width, height, color);
	}

	//Metoda generuje obraz tekstury
	void CPhysical::SetTextureHead(unsigned width, unsigned height, unsigned r, unsigned g, unsigned b, unsigned a)
	{
		m_physical_data.setTextureHead(width, height, r, g, b, a);
	}

	//Metoda zwraca tryb wyg�adzania tekstury
	const bool CPhysical::getSmoothing() const
	{
		return m_smooth;
	}

	//Metoda ustawia tryb wyg�adzania tekstury
	void CPhysical::setSmoothing(bool smooth)
	{
		m_smooth = smooth; //zapamietuj� flag� wyg�adzania tekstury

		if(m_physical_data.getDisplayableBody())
			m_physical_data.getDisplayableBody()->setSmoothing(m_smooth);
		if(m_physical_data.getDisplayableBodyShadow())
			m_physical_data.getDisplayableBodyShadow()->setSmoothing(m_smooth);
		if(m_physical_data.getDisplayableHead())
			m_physical_data.getDisplayableHead()->setSmoothing(m_smooth);
		if(m_physical_data.getDisplayableHeadShadow())
			m_physical_data.getDisplayableHeadShadow()->setSmoothing(m_smooth);
	}

	//Metoda zwraca statyczny wsp�czynnik wirtualnej wysoko�ci obiektu
	const float CPhysical::GetIncrease() const
	{
		return m_increase;
	}

	//Metoda ustawia statyczny wsp�czynnik wirtualnej wysoko�ci obiektu
	const void CPhysical::SetIncrease(float increase) const
	{
		m_increase = increase;
	}

	//Metoda zwraca opakowanie informacji o kolidowaniu
	PartCollisionData	& CPhysical::getPartCollisionData()
	{
		return m_part_collision_data;
	}

	//Wirtualna metoda aktualizuj�ca obiekt
	void CPhysical::update(float dt)
	{
		sf::Vector2f new_position;
		new_position.x = m_physical_data.getPosition().x + (dt * m_physical_data.getVelocity().x);
		new_position.y = m_physical_data.getPosition().y + (dt * m_physical_data.getVelocity().y);
		m_physical_data.setOldPosition(m_physical_data.getPosition());
		SetPosition(new_position);
		UpdateShadow(dt);
	}

	//implementajca metod protected:

	//Metoda zwraca wyliczony wsp�czynnik pr�dko�ci animacji dla zadanego czasu trwania jednego obiegu animacji
	const float CPhysical::getCalcualtedAnimSpeed(float anim_time)
	{
		if (anim_time > 0)
		{
			//wyliczenie nowego czasu odtwarzania pe�nego obiegu animacji
			m_new_anim_speed = GetAnimSpeedHead() / anim_time;
			//im kr�tszy czas trwania animacji, tym wi�ksza pr�dko�� odtwarzania
			//im d�u�szy czas trwania animacji, tym mniejsza pr�dko�� odtwarzania
			//new_anim_speed_factor		= current_anim_speed / new_anim_total_time
			//anim_speed_factor_one		= 1 / 1.0000	=>	1.0000
			//anim_speed_factor_two		= 1 / 0.5000	=>	2.0000
			//anim_speed_factor_three	= 1 / 4.0000	=>	0.2500
			return m_new_anim_speed;
		}
		return GetAnimSpeedHead();//zwracamy nienaruszone
	}


	//Metoda zwraca indeks warstwy renderingu obiektu (body)
	const int CPhysical::GetZIndexBody() const
	{
		return m_physical_data.getZIndexBody();
	}

	//Metoda ustawia indeks warstwy renderingu obiektu (body)
	void CPhysical::SetZIndexBody(int layer_index)
	{
		m_physical_data.setZIndexBody(layer_index);
	}

	//Metoda zwraca indeks warstwy renderingu obiektu (body shadow)
	const int CPhysical::GetZIndexShadowBody() const
	{
		return m_physical_data.getZIndexShadowBody();
	}
	
	//Metoda ustawia indeks warstwy renderingu obiektu (body shadow)
	void CPhysical::SetZIndexShadowBody(int layer_index)
	{
		m_physical_data.setZIndexShadowBody(layer_index);
	}

	//Metoda zwraca indeks warstwy renderingu obiektu (head)
	const int CPhysical::GetZIndexHead() const
	{
		return m_physical_data.getZIndexHead();
	}

	//Metoda ustawia indeks warstwy renderingu obiektu (head)
	void CPhysical::SetZIndexHead(int layer_index)
	{
		m_physical_data.setZIndexHead(layer_index);
	}

	//Metoda zwraca indeks warstwy renderingu obiektu (head shadow)
	const int CPhysical::GetZIndexShadowHead() const
	{
		return m_physical_data.getZIndexShadowHead();
	}

	//Metoda ustawia indeks warstwy renderingu obiektu (head shadow)
	void CPhysical::SetZIndexShadowHead(int layer_index)
	{
		m_physical_data.setZIndexShadowHead(layer_index);
	}

	//Metoda aktualizuje cie� rzucany przez obiekt i jego nasycenie w zale�no�ci od pory dnia
	void CPhysical::UpdateShadow(float dt)
	{
		m_physical_data.updateShadowTransformation();
	}


	//implementajca metod private:

	//prywatna metoda sprawdza, czy trzeba utworzy� obiekt klasy CDisplayable
	void CPhysical::CheckDisplayableBody()
	{
		m_physical_data.checkDisplayableBody();
	}

	//prywatna metoda sprawdza, czy trzeba utworzy� obiekt klasy CDisplayable
	void CPhysical::CheckDisplayableHead()
	{
		m_physical_data.checkDisplayableHead();
	}

	//prywatna metoda dobieraj�ca przesuni�cie cienia
	//w zale�no�ci od wielko�ci obiektu - body and head
	//oraz jego nasycenie w zale�no�ci od pory dnia
	//pozycji s�o�ca (�r�d�a �wiat�a - gwiazd, etc...)
	void CPhysical::UpdateShadowTransformation()
	{
		m_physical_data.updateShadowTransformation();
	}

	//Metoda ustala wektor przesuni�cia cienia - body
	void CPhysical::CheckShadowOffsetBody()
	{
		m_physical_data.checkShadowOffsetBody();
	}

	//Metoda ustala wektor przesuni�cia cienia - head
	void CPhysical::CheckShadowOffsetHead()
	{
		m_physical_data.checkShadowOffsetHead();
	}

	//Metoda ustala wektor przesuni�cia cienia - body and head
	void CPhysical::CheckShadowOffset()
	{
		m_physical_data.checkShadowOffsetBody();
		m_physical_data.checkShadowOffsetHead();
	}

}//namespace logic

//Nadanie warto�ci sta�ym sk�adowym statycznym
float logic::CPhysical::m_increase		= 0.33f;	//default - wsp�czynnik wysoko�ci (wzrostu) obiektu)
