﻿//  ____________________________________________________
// | EquipmentVentilatorData.cpp - class implementation |
// | Jack Flower - May 2016                             |
// |____________________________________________________|
//

#include "EquipmentVentilatorData.h"
#include "../Thermodynamics/Ventilator/Ventilator.h"
#include "../../Logic/PhysicalManager.h"

namespace equipmentdata
{
	RTTI_IMPL(EquipmentVentilatorData, EquipmentData);

	//Konstruktor
	EquipmentVentilatorData::EquipmentVentilatorData()
	:
		EquipmentData(),//konstruktor klasy bazowej
		p_ventilator(NULL)
	{
	}

	//Konstruktor kopiujący
	EquipmentVentilatorData::EquipmentVentilatorData(const EquipmentVentilatorData & EquipmentVentilatorDataCopy)
	:
		EquipmentData(EquipmentVentilatorDataCopy),//konstruktor kopiujący klasy bazowej
		p_ventilator(EquipmentVentilatorDataCopy.p_ventilator)
	{
	}

	//Destruktor wirtualny
	EquipmentVentilatorData::~EquipmentVentilatorData()
	{
		//EquipmentData
		if (p_ventilator)
			gPhysicalManager.destroyPhysical(p_ventilator);
		p_ventilator = NULL;
	}

	//Metoda zwraca typ obiektu /RTTI/
	const std::string EquipmentVentilatorData::getType() const
	{
		return rtti.GetNameClass();
	}

	//Metoda zwraca wskaźnik na obiekt klasy Ventilator
	Ventilator* EquipmentVentilatorData::getVentilator()
	{
		return p_ventilator;
	}

	//Metoda ustawia wskaźnik na obiekt klasy Ventilator
	void EquipmentVentilatorData::setVentilator(Ventilator * ventilator)
	{
		p_ventilator = ventilator;
	}
}//namespace equipmentdata