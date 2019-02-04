//  ___________________________________________
// | CActorTemplate.h - class definition       |
// | Jack Flower - February 2013               |
// |___________________________________________|
//

#ifndef H_ACTOR_TEMPLATE_JACK
#define H_ACTOR_TEMPLATE_JACK

#include "CPhysicalTemplate.h"
#include "../Logic/Actor/CActor.h"
#include <string>
#include <vector>
#include <iostream>

///
///Forward declaration
///
namespace xml
{
	class CXml;
}

///
///Forward declaration
///
namespace logic
{
	class CActor;
}

///
///Forward declaration
///
namespace rendering
{
	namespace animation
	{
		class CAnimSet;
	}
}

///
///Forward declaration
///
namespace factory
{
	class CEngineTemplate;
	class CEnergyTemplate;
	class CAirconditioningTemplate;
	class CVentilatorTemplate;
	class CGunTemplate;
	class CWindTurbineTemplate;
	class CWindPowerStationTemplate;
	class CPhysicalInfoTemplate;
}

namespace factory
{
	///
	///Klasa reprezentuje generyczny wzorzec aktora
	///
	class CActorTemplate : public CPhysicalTemplate
	{
		RTTI_DECL;

	public:

		///
		///Konstruktor
		///
		CActorTemplate();

		///
		///Destruktor wirtualny
		///
		virtual ~CActorTemplate();

		///
		///Metoda zwraca typ obiektu /RTTI/
		///
		const std::string GetType() const;

		///
		///Wirtualna metoda zwalniająca zasób - implementacje w klasach pochodnych
		///
		void Drop();

		///
		///Metoda ładująca dane
		///
		///@param &name - stała referencja na std::string
		///
		bool Load(const std::string &name);

		///
		///Wirtualna metoda ładująca dane z xml
		///
		///@param &xml - referencja na obiekt klasy CXml
		///
		bool Load(CXml &xml);
			
	protected:

		CAnimSet*						p_templ_animations;				//wskaźnik na zestaw animacji CActor
		std::vector<CAnimSet*>			m_templ_available_animations;	//wektor wskaźników na zestawy dostępnych animacji dla CActor
		CActorTechnicalData				m_templ_technical_data;			//opakowanie fizyki
		CEquipmentEngineData			m_templ_engine_data;			//opakowanie funkcjonalności silnika
		CEquipmentEnergyData			m_templ_energy_data;			//opakowanie funkcjonalności energii
		CEquipmentAirconditioningData	m_templ_airconditioning_data;	//opakowanie funkcjonalności klimatyzacji
		CEquipmentVentilatorData		m_templ_ventilator_data;		//opakowanie funkcjonalności wentylatora
		CEquipmentGunData				m_templ_gun_data;				//opakowanie funkcjonalności działo
		CEngineTemplate*				p_templ_engine;					//dane wzorca obiektu CEngine
		CEnergyTemplate*				p_templ_energy;					//dane wzorca obiektu CEnergy
		CAirconditioningTemplate*		p_templ_airconditioning;		//wskaźnik na obiekt CAirconditioning z logiką zarządzania modułem klimatyzatora
		CVentilatorTemplate*			p_templ_ventilator;				//wskaźnik na obiekt CVentilatorTemplate z logiką zarządzania modułem wentylatora
		CGunTemplate*					p_templ_gun;					//wskaźnik na obiekt CGunTemplate z logiką zarządzania działem
		
		bool							m_templ_use_physical_info;		//flaga, czy obiekt posiada wskaźnik energii i paliwa
		CPhysicalInfoTemplate*			p_templ_physical_info;			//dane wzorca obiekty CPhysicalInfoTemplate

	protected:

		///
		///Metoda tworzy obiekt klasy CActor
		///
		///@param id - nazwa identyfikatora - obiekt klasy std::wstring
		///
		CActor* Create(std::wstring id = L"");

		///
		///Wirtualna metoda wypełniająca danymi obiekt klasy CActor
		///
		///@param *actor - wskaźnik na obiekt klasy CActor
		///
		virtual void Fill(CActor *actor);

	public:

		//metoda zwraca referencję na kontener z zestawem animacji
		inline const std::vector<CAnimSet*> &GetAvailableAnims() { return m_templ_available_animations; }
	};
} //namespace factory
#endif //H_ACTOR_TEMPLATE_JACK
