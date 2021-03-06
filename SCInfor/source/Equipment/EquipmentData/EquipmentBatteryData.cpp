//  _________________________________________________
// | EquipmentBatteryData.cpp - class implementation |
// | Jack Flower - May 2016                          |
// |_________________________________________________|
//

#include "EquipmentBatteryData.h"
#include "../Energy/Battery/Battery.h"
#include "../../Logic/PhysicalManager.h"

namespace equipmentdata
{
	RTTI_IMPL(EquipmentBatteryData, EquipmentData);

	//Konstruktor
	EquipmentBatteryData::EquipmentBatteryData()
	:
		EquipmentData{},//konstruktor klasy bazowej
		p_battery{ nullptr }
	{
	}

	//Konstruktor kopiujący
	EquipmentBatteryData::EquipmentBatteryData(const EquipmentBatteryData & EquipmentBatteryDataaCopy)
	:
		EquipmentData{ EquipmentBatteryDataaCopy },//konstruktor kopiujący klasy bazowej
		p_battery{ EquipmentBatteryDataaCopy.p_battery }
	{
	}

	//Destruktor wirtualny
	EquipmentBatteryData::~EquipmentBatteryData()
	{
		//~EquipmentData()
		if (p_battery)
			gPhysicalManager.destroyPhysical(p_battery);
		p_battery = nullptr;
	}

	//Metoda zwraca typ obiektu /RTTI/
	const std::string EquipmentBatteryData::getType() const
	{
		return rtti.getNameClass();
	}

	//Metoda zwraca wskaźnik na obiekt klasy Ventilator
	Battery *EquipmentBatteryData::getBattery()
	{
		return p_battery;
	}

	//Metoda ustawia wskaźnik na obiekt klasy Ventilator
	void EquipmentBatteryData::setBattery(Battery *battery)
	{
		p_battery = battery;
	}
}//namespace equipmentdata
