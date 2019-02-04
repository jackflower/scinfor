//  __________________________________________________
// | CEquipmentBatteryData.h - class definition       |
// | Jack Flower - May 2016                           |
// |__________________________________________________|
//

#ifndef H_EQUIPMENT_BATTERY_DATA_JACK
#define H_EQUIPMENT_BATTERY_DATA_JACK

#include "CEquipmentData.h"

///
///Forward declaration
///
namespace equipment
{
	namespace battery
	{
		class CBattery;
	}
}

using namespace equipment;
using namespace equipment::battery;

namespace equipmentdata
{
	///
	///Klasa reprezentuje funkcjonalno�� obiektu b�d�cego wyposa�aniem - wentylator
	///
	class CEquipmentBatteryData : public CEquipmentData
	{
		RTTI_DECL;

	public:

		///
		///Konstruktor
		///
		CEquipmentBatteryData();

		///
		///Konstruktor kopiuj�cy
		///
		///@param & CEquipmentBatteryDataCopy - sta�a referencja na obiekt klasy CEquipmentBatteryData
		///
		CEquipmentBatteryData(const CEquipmentBatteryData & CEquipmentBatteryDataCopy);

		///
		///Destruktor wirtualny
		///
		virtual ~CEquipmentBatteryData();

		///
		///Metoda zwraca typ obiektu /RTTI/
		///
		const std::string GetType() const;

		///
		///Metoda zwraca wska�nik na obiekt klasy CBattery
		///
		CBattery* getBattery();

		///
		///Metoda ustawia wska�nik na obiekt klasy CBattery
		///
		///@param *battery - wska�nik na obiekt klasy CBattery
		///
		void setBattery(CBattery* battery);

	private:

		CBattery*	p_battery;	//wska�nik na klas� CVentilator - wentylator
	};
}//namespace equipmentdata
#endif//H_EQUIPMENT_BATTERY_DATA_JACK