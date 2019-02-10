/*
 ____________________________________________
| CPhysicalManager.h - definicja klasy       |
| Jack Flower - November 2012.               |
|____________________________________________|

*/

#ifndef H_PHYSICAL_MANAGER_JACK
#define H_PHYSICAL_MANAGER_JACK

#include "../Utilities/Singleton/CSingleton.h"
#include "../Game/Listener/IFrameListener.h"
#include <string>
#include <map>

#define gPhysicalManager CPhysicalManager::GetSingleton()

///
///Forward declaration
///
namespace logic
{
	class CPhysical;
	class Actor;
	class CEnemy;
	class CPlayer;
	class Bullet;
	class CMonster;
	class CFlora;
	class CPhysicalInfo;
	namespace unit
	{
		class CRobot;
	}
	namespace powerstation
	{
		class CPowerStation;
		class CWindPowerStation;
		class CWindPowerStationMultipled;
	}
	namespace energetics
	{
		class CRelayStation;
		class CPowerRelayStation;
		class CSlotsRate;
	}
	namespace communication
	{
		class Communication;
	}
}

///
///Forward declaration
///
namespace equipment
{
	class Engine;
	class FuelTank;
	class Energy;
	class EnergyTank;
	class FuelBar;
	class Airconditioning;
	class ThermalInsulation;
	class Ventilator;
	class WindTurbine;
	class SolarCell;
	class LightingEquipment;

	namespace weapon
	{
		class Ammo;
		class Gun;
	}

	namespace battery
	{
		class Battery;
		class SolarBattery;
	}
}

///
///Forward declaration
///
namespace mapengine
{
	class CGround;
}

//fabryka mo�e produkowa� obiekty wy�ej wymienionych klasy

using namespace listener;
using namespace equipment;
using namespace equipment::weapon;
using namespace equipment::battery;
using namespace logic::powerstation;
using namespace logic::energetics;
using namespace logic::communication;
using namespace logic::unit;
using namespace mapengine;

namespace logic
{
	///
	///Klasa reprezentuje fabryk� produkuj�c� obiekty gry i zarz�dzanie obiektami
	///
	class CPhysicalManager : public CSingleton<CPhysicalManager>, public IFrameListener
	{
	public:

		///
		///Konstruktor
		///
		CPhysicalManager();

		///
		///Destruktor wirtualny
		///
		virtual ~CPhysicalManager();

		///
		///Wirtualna metoda - czy�ci obiekty z kontenera
		///
		///@param secondsPassed - up�ywaj�cy czas
		///
		virtual void frameStarted(float secondsPassed);
		
		///
		///Metoda tworzy obiekt klasy CPhysical i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		CPhysical* CreatePhysical(const std::wstring& unique_id = L"");

		///
		///Metoda tworzy obiekt klasy Actor i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		Actor *CreateActor(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy CRobot i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		CRobot *CreateRobot(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy CEnemy i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		CEnemy *CreateEnemy(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy CPlayer i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		CPlayer *CreatePlayer(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy Bullet i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		Bullet *CreateBullet(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy Engine i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		Engine *CreateEngine(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy FuelTank i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		FuelTank *CreateFuelTank(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy Energy i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		Energy *CreateEnergy(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy EnergyTank i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		EnergyTank *CreateEnergyTank(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy CMonster i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		CMonster *CreateMonster(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy CFlora i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		CFlora *CreateFlora(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy FuelBar i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		FuelBar *CreateFuelBar(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy CPhysicalInfo i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		CPhysicalInfo *CreatePhysicalInfo(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy Battery i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		Battery *CreateBattery(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy SolarBattery i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		SolarBattery *CreateSolarBattery(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy Airconditioning i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		Airconditioning *CreateAirconditioning(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy ThermalInsulation i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		ThermalInsulation *CreateThermalInsulation(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy Ventilator i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		Ventilator *CreateVentilator(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy Ammo i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		Ammo *CreateAmmo(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy Gun i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		Gun *CreateGun(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy WindTurbine i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		WindTurbine *CreateWindTurbine(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy SolarCell i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		SolarCell *CreateSolarCell(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy CPowerStation i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		CPowerStation *CreatePowerStation(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy CWindPowerStation i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		CWindPowerStation *CreateWindPowerStation(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy CWindPowerStationMultipled i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		CWindPowerStationMultipled *CreateWindPowerStationMultipled(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy CRelayStation i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		CRelayStation *CreateRelayStation(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy CPowerRelayStation i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		CPowerRelayStation *CreatePowerRelayStation(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy CSlotsRate i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		CSlotsRate* CreateSlotsRate(const std::wstring &uniqueId = L"");
		
		///
		///Metoda tworzy obiekt klasy Communication i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		Communication *CreateCommunication(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy LightingEquipment i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		LightingEquipment *CreateLightingEquipment(const std::wstring &uniqueId = L"");

		///
		///Metoda tworzy obiekt klasy CGround i zwraca wska�nik na ten obiekt
		///
		///@param &uniqueId - unikalny identyfikator - sta�a referencja na obiekt klasy std::wstring
		///
		CGround *CreateGround(const std::wstring &uniqueId = L"");

		///
		///Metoda usuwa obiekt klasy CPhysical z kontenera
		///
		///@param *physical - wska�nik na obiekt klasy CPhysical
		///
		void DestroyPhysical(CPhysical* physical);
	    
		///
		///Metoda usuwa obiekt klasy CPhysical z kontenera
		///
		///@param &id_physical - sta�a referencja na obiekt klasy std::wstring - unikalny identyfikator obiektu
		///
		void DestroyPhysical(const std::wstring& id_physical);

		///
		///Metoda usuwa wszystkie obiekty z kontenera
		///
		///@param force_destroy_instantly - flaga, czy usun�� z kontenera wszystkie obiekty
		///
		void Clear(bool force_destroy_instantly = false);

		///
		///Metoda zwraca sta�a referencj� do kontenera z nazwami wszystkich zarejestorwanych obiekt�w CPhysical
		///
		const std::map<std::wstring, CPhysical*>& GetNamedPhysicals();

		///
		///Metoda zwraca sta�a referencj� do kontenera z wszystkimi wska�nikami zarejestorwanych obiekt�w CPhysical
		///
		const std::vector<CPhysical*>& GetPhysicals();

		///
		///Metoda zwraca wska�nik na obiekt klasy CPhysical z kontenera na podstawie identyfikatora
		///
		///@param &physical_id - sta�a referencja na obiekt klasy std::wstring
		///
		CPhysical* GetPhysicalById(const std::wstring& physical_id);
				
		
		//metody p o m o c n i c z e

		///
		///Metoda zwraca sta�� referencj� na kontener, w kt�rym s� wska�niki na obiekty klasy CWindPowerStation
		////elektrownie wiatrowe
		///
		const std::vector<CWindPowerStation*>& GetWindPowerstations();

		///
		///Wirtualny interfejs - implementacja
		///
		virtual void Cleanup();
		

	private:
		
		//
		//Szablon metody tworzenia obiekt�w
		//
		template<class T> T* create(const std::wstring &uniqueId);
	    
		std::map<std::wstring, CPhysical*>	m_named_physicals;	//kontener <map> na nazwane obiekty klasy CPhysical
		std::vector<CPhysical*>				m_physicals;		//kontener <vector> na wska�niki na obiekty klasy CPhysical
		std::vector<CWindPowerStation*>		m_wind_powerstation;		//elektrownie wiatrowa
		//
		//Prywatna metoda sprawdzaj�ca jaki identyfikator nada� obiektowi przy utworzeniu
		//
		//@param &new_unique_id - referencja na obiekt klasy std::wstring
		//
		void CheckUniqueId(std::wstring& new_unique_id);
	};
}//namespace logic
#endif//H_PHYSICAL_MANAGER_JACK
