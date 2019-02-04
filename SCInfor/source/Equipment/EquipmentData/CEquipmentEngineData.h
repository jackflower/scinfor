//  _________________________________________________
// | CEquipmentEngineData.h - class definition       |
// | Jack Flower - May 2016                          |
// |_________________________________________________|
//

#ifndef H_EQUIPMENT_ENGINE_DATA_JACK
#define H_EQUIPMENT_ENGINE_DATA_JACK

#include "CEquipmentData.h"

///
///Forward declaration
///
namespace equipment
{
	class CEngine;
}

using namespace equipment;

namespace equipmentdata
{
	///
	///Klasa reprezentuje funkcjonalno�� obiektu b�d�cego wyposa�aniem - silnik
	///
	class CEquipmentEngineData : public CEquipmentData
	{
		RTTI_DECL;

	public:

		///
		///Konstruktor
		///
		CEquipmentEngineData();

		///
		///Konstruktor kopiuj�cy
		///
		///@param & CEquipmentEngineDataCopy - sta�a referencja na obiekt klasy CEquipmentEngineData
		///
		CEquipmentEngineData(const CEquipmentEngineData & CEquipmentEngineDataCopy);

		///
		///Destruktor wirtualny
		///
		virtual ~CEquipmentEngineData();

		///
		///Metoda zwraca typ obiektu /RTTI/
		///
		const std::string GetType() const;

		///
		///Metoda zwraca wska�nik na obiekt klasy CEngine
		///
		CEngine* getEngine();

		///
		///Metoda ustawia wska�nik na obiekt klasy CEngine
		///
		///@param *engine - wska�nik na obiekt klasy CEngine
		///
		void setEngine(CEngine* engine);

	private:

		CEngine*	p_engine;	//wska�nik na klas� CEngine - silnik
	};
}//namespace equipmentdata
#endif//H_EQUIPMENT_ENGINE_DATA_JACK