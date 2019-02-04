//  _____________________________________________________
// | CAirconditioningTemplate.h - class definition       |
// | Jack Flower June 2014                               |
// |_____________________________________________________|
//

#ifndef H_AIRCONDITIONING_TEMPLATE_JACK
#define H_AIRCONDITIONING_TEMPLATE_JACK

#include "../../../CActorTemplate.h"
#include "../ThermalInsulationFactory/CThermalInsulationTemplate.h"
#include "../../../../Equipment/Thermodynamics/Airconditioning/CAirconditioning.h"
#include "../../../../Equipment/EquipmentData/CThermalInsulationData.h"

using namespace equipmentdata;

namespace factory
{
	///
	///Klasa reprezentuje wzorzec modu�u klimatyzatora
	///
	class CAirconditioningTemplate : public CActorTemplate
	{
		RTTI_DECL;

	public:

		///
		///Konstruktor
		///
		CAirconditioningTemplate();

		///
		///Destruktor wirtualny
		///
		~CAirconditioningTemplate();

		///
		///Metoda zwraca typ obiektu /RTTI/
		///
		const std::string GetType() const;

		///
		///Wirtualna metoda zwalniaj�ca zas�b - implementacje w klasach pochodnych
		///
		void Drop();

		///
		///Metoda �aduj�ca dane
		///
		///@param &name - sta�a referencja na std::string
		///
		bool Load(const std::string &name);

		///
		///Wirtualna metoda �aduj�ca dane z xml
		///
		///@param &xml - referencja na obiekt klasy CXml
		///
		bool Load(CXml &xml);

		///
		///Metoda tworzy obiekt klasy CAirconditioning
		///
		///@param id - nazwa identyfikatora - obiekt klasy std::wstring
		///
		CAirconditioning* Create(std::wstring id = L"");

		///
		///Wirtualna metoda wype�niaj�ca wskazany obiekt danymi tej klasy
		///
		///@param *p_airconditioning - wska�nik na obiekt klasy CAirconditioning
		///
		virtual void Fill(CAirconditioning *p_airconditioning);

	private:

		std::string					m_templ_airconditioning_name;		//nazwa klimatyzatora
		float						m_templ_temperature;				//temperatura [obliczana]
		float						m_templ_temperature_set;			//temperatura ustawiona na urz�dzeniu (klimatyzator)[losowana z zakresu]
		std::pair<float, float>		m_templ_temperature_range;			//zakres temperatury - skuteczno�� urz�dzenia [first - cold, second - warm]
		float						m_templ_temperature_increment;		//przyrost temperatury - cykl - dynammika
		float						m_templ_energy_consumption;			//zu�ycie energii przez klimatyzator
		float						m_templ_fuel_consumption;			//zu�ycie paliwa przez klimatyzator
		CThermalInsulationData		m_templ_thermalinsulation_data;		//opakowanie funkcjonalno�ci termoizolatora
		CThermalInsulationTemplate* p_templ_thermal_insulation;			//wska�nik na obiekt CThermalInsulationTemplate (wzorzec termoizolaora)
	};
}//namespace factory
#endif//H_AIRCONDITIONING_TEMPLATE_JACK