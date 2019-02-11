/*
 ____________________________________________
| CPhysicalManager.cpp - implementacja klasy |
| Jack Flower - November 2012.               |
|____________________________________________|

*/

#include "CPhysicalManager.h"
#include "Physical/CPhysical.h"
#include "Physical/PhysicalInfo/CPhysicalInfo.h"
#include "Actor/Actor.h"
#include "Enemy/Enemy.h"
#include "Player/CPlayer.h"
#include "Bullet/Bullet.h"
#include "Monster/Monster.h"
#include "Flora/Flora.h"
#include "Unit/CombatUnit/Robot/CRobot.h"
#include "../Equipment/Engine/Engine.h"
#include "../Equipment/Engine/FuelTank/FuelTank.h"
#include "../Equipment/Engine/FuelBar/FuelBar.h"
#include "../Equipment/Energy/Energy.h"
#include "../Equipment/Energy/EnergyTank/EnergyTank.h"
#include "../Equipment/Energy/Battery/Battery.h"
#include "../Equipment/Energy/Battery/SolarBattery.h"
#include "../Equipment/Thermodynamics/Airconditioning/Airconditioning.h"
#include "../Equipment/Thermodynamics/ThermalInsulation/ThermalInsulation.h"
#include "../Equipment/Thermodynamics/Ventilator/Ventilator.h"
#include "../Equipment/Weapon/Ammo/Ammo.h"
#include "../Equipment/Weapon/Gun/Gun.h"
#include "../Equipment/Lightingequipment/LightingEquipment.h"
#include "../Equipment/Industrial/PowerModuleType/WindTurbine.h"
#include "../Equipment/Industrial/PowerModuleType/SolarCell.h"
#include "Industrial/PowerStation//PowerStation.h"
#include "Industrial/PowerStation/WindPowerStation/WindPowerStation.h"
#include "Industrial/PowerStation/WindPowerStation/WindPowerStationMultipled.h"
#include "Energetics/PowerRelay/RelayStation.h"
#include "Energetics/PowerRelay/PowerRelayStation.h"
#include "Energetics/PowerRelay/SlotsRate.h"
#include "Communication/Communication.h"
#include "../Map/Ground/CGround.h"
#include "../Utilities/StringUtils/StringUtils.h"
#include "../Game/Game.h"
#include <sstream>

using namespace game;

template<> CPhysicalManager* CSingleton<CPhysicalManager>::m_singleton = 0;

namespace logic
{
	//Konstruktor
	CPhysicalManager::CPhysicalManager()
	{
		fprintf(stderr, "CPhysicalManager::CPhysicalManager()\n");
		gGame.addFrameListener(this);
	}

	//Destruktor wirtualny
	CPhysicalManager::~CPhysicalManager()
	{
		fprintf(stderr, "CPhysicalManager::~CPhysicalManager()\n");
		Clear(true);
	}

	//Wirtualna metoda - czy�ci obiekty z kontenera
	void CPhysicalManager::frameStarted(float secondsPassed)
	{
		//Czyszczenie obiekt�w
		std::vector<CPhysical*>				dirty;		//kontener na obiekty do zniszczenia
		std::vector<CPhysical*>::iterator	it;			//iterator tego kontenera

		for (it = m_physicals.begin(); it != m_physicals.end(); it++)
		{
			if ((*it)->m_ready_for_destruction)			//je�li obiekt jest gotowy do zniszczaenia
				dirty.push_back(*it);					//wstawiamy go do kontenera "�mierci"
		}

		for (unsigned int i = 0; i < dirty.size(); i++)	//iterujemy po tym kontenerze
			DestroyPhysical(dirty[i]);					//i usuwamy obiekty

	}

	//Szablon metody tworzenia obiekt�w
	template<class T>
	T* CPhysicalManager::create(const std::wstring &uniqueId)
	{
		std::wstring new_unique_id = uniqueId;
		if (uniqueId != L"")
		{
			CheckUniqueId(new_unique_id);

			if (m_named_physicals.find(new_unique_id) != m_named_physicals.end())
			{
				fprintf(stderr, "PhysicalsManager::create<T> - %ls key already in m_named_physicals map", new_unique_id.c_str());
				return NULL;
			}

			m_named_physicals[new_unique_id] = NULL; // zarezerwowanie nazwy przed utworzeniem obiektu
		}

		T* obj = new T(new_unique_id);
		obj->m_physical_manager_index = (int)m_physicals.size();
		m_physicals.push_back(obj);
		if (uniqueId != L"")
			m_named_physicals[new_unique_id] = obj;
		return obj;
	}

	//Metoda tworzy obiekt klasy CPhysical i zwraca wska�nik na ten obiekt
	CPhysical *CPhysicalManager::CreatePhysical(const std::wstring& unique_id)
	{
		fprintf(stderr, "CPhysical created\n");
		return create<CPhysical>(unique_id);
	}

	//Metoda tworzy obiekt klasy Actor i zwraca wska�nik na ten obiekt
	Actor *CPhysicalManager::CreateActor(const std::wstring &uniqueId)
	{
		fprintf(stderr, "Actor created\n");
		return create<Actor>(uniqueId);
	}

	//Metoda tworzy obiekt klasy CRobot i zwraca wska�nik na ten obiekt
	CRobot *CPhysicalManager::CreateRobot(const std::wstring &uniqueId)
	{
		fprintf(stderr, "CRobot created\n");
		return create<CRobot>(uniqueId);
	}

	//Metoda tworzy obiekt klasy Enemy i zwraca wska�nik na ten obiekt
	Enemy *CPhysicalManager::CreateEnemy(const std::wstring &uniqueId)
	{
		fprintf(stderr, "Enemy created\n");
		return create<Enemy>(uniqueId);
	}

	//Metoda tworzy obiekt klasy CPlayer i zwraca wska�nik na ten obiekt
	CPlayer *CPhysicalManager::CreatePlayer(const std::wstring &uniqueId)
	{
		fprintf(stderr, "CPlayer created\n");
		return create<CPlayer>(uniqueId);
	}

	//Metoda tworzy obiekt klasy Bullet i zwraca wska�nik na ten obiekt
	Bullet *CPhysicalManager::CreateBullet(const std::wstring &uniqueId)
	{
		fprintf(stderr, "Bullet created\n");
		return create<Bullet>(uniqueId);
	}

	//Metoda tworzy obiekt klasy Engine i zwraca wska�nik na ten obiekt
	Engine *CPhysicalManager::CreateEngine(const std::wstring &uniqueId)
	{
		fprintf(stderr, "Engine created\n");
		return create<Engine>(uniqueId);
	}

	//Metoda tworzy obiekt klasy FuelTank i zwraca wska�nik na ten obiekt
	FuelTank *CPhysicalManager::CreateFuelTank(const std::wstring &uniqueId)
	{
		fprintf(stderr, "FuelTank created\n");
		return create<FuelTank>(uniqueId);
	}

	//Metoda tworzy obiekt klasy Energy i zwraca wska�nik na ten obiekt
	Energy *CPhysicalManager::CreateEnergy(const std::wstring &uniqueId)
	{
		fprintf(stderr, "Energy created\n");
		return create<Energy>(uniqueId);
	}

	//Metoda tworzy obiekt klasy EnergyTank i zwraca wska�nik na ten obiekt
	EnergyTank *CPhysicalManager::CreateEnergyTank(const std::wstring &uniqueId)
	{
		fprintf(stderr, "EnergyTank created\n");
		return create<EnergyTank>(uniqueId);
	}

	//Metoda tworzy obiekt klasy Monster i zwraca wska�nik na ten obiekt
	Monster *CPhysicalManager::CreateMonster(const std::wstring &uniqueId)
	{
		fprintf(stderr, "Monster created\n");
		return create<Monster>(uniqueId);
	}

	//Metoda tworzy obiekt klasy Flora i zwraca wska�nik na ten obiekt
	Flora *CPhysicalManager::CreateFlora(const std::wstring &uniqueId)
	{
		fprintf(stderr, "Flora created\n");
		return create<Flora>(uniqueId);
	}

	//Metoda tworzy obiekt klasy FuelBar i zwraca wska�nik na ten obiekt
	FuelBar *CPhysicalManager::CreateFuelBar(const std::wstring &uniqueId)
	{
		fprintf(stderr, "FuelBar created\n");
		return create<FuelBar>(uniqueId);
	}

	//Metoda tworzy obiekt klasy CPhysicalInfo i zwraca wska�nik na ten obiekt
	CPhysicalInfo *CPhysicalManager::CreatePhysicalInfo(const std::wstring &uniqueId)
	{
		fprintf(stderr, "CPhysicalInfo created\n");
		return create<CPhysicalInfo>(uniqueId);
	}

	//Metoda tworzy obiekt klasy Battery i zwraca wska�nik na ten obiekt
	Battery *CPhysicalManager::CreateBattery(const std::wstring &uniqueId)
	{
		fprintf(stderr, "Battery created\n");
		return create<Battery>(uniqueId);
	}

	//Metoda tworzy obiekt klasy SolarBattery i zwraca wska�nik na ten obiekt
	SolarBattery *CPhysicalManager::CreateSolarBattery(const std::wstring &uniqueId)
	{
		fprintf(stderr, "CBatteCSolarBatteryry created\n");
		return create<SolarBattery>(uniqueId);
	}

	//Metoda tworzy obiekt klasy Airconditioning i zwraca wska�nik na ten obiekt
	Airconditioning *CPhysicalManager::CreateAirconditioning(const std::wstring &uniqueId)
	{
		fprintf(stderr, "Airconditioning created\n");
		return create<Airconditioning>(uniqueId);
	}

	//Metoda tworzy obiekt klasy ThermalInsulation i zwraca wska�nik na ten obiekt
	ThermalInsulation *CPhysicalManager::CreateThermalInsulation(const std::wstring &uniqueId)
	{
		fprintf(stderr, "ThermalInsulation created\n");
		return create<ThermalInsulation>(uniqueId);
	}

	//Metoda tworzy obiekt klasy Ventilator i zwraca wska�nik na ten obiekt
	Ventilator *CPhysicalManager::CreateVentilator(const std::wstring &uniqueId)
	{
		fprintf(stderr, "Ventilator created\n");
		return create<Ventilator>(uniqueId);
	}

	//Metoda tworzy obiekt klasy Ammo i zwraca wska�nik na ten obiekt
	Ammo *CPhysicalManager::CreateAmmo(const std::wstring &uniqueId)
	{
		fprintf(stderr, "Ammo created\n");
		return create<Ammo>(uniqueId);
	}

	//Metoda tworzy obiekt klasy Gun i zwraca wska�nik na ten obiekt
	Gun *CPhysicalManager::CreateGun(const std::wstring &uniqueId)
	{
		fprintf(stderr, "Gun created\n");
		return create<Gun>(uniqueId);
	}

	//Metoda tworzy obiekt klasy Gun i zwraca wska�nik na ten obiekt
	WindTurbine *CPhysicalManager::CreateWindTurbine(const std::wstring &uniqueId)
	{
		fprintf(stderr, "WindTurbine created\n");
		return create<WindTurbine>(uniqueId);
	}


	//Metoda tworzy obiekt klasy SolarCell i zwraca wska�nik na ten obiekt
	SolarCell *CPhysicalManager::CreateSolarCell(const std::wstring &uniqueId)
	{
		fprintf(stderr, "SolarCell created\n");
		return create<SolarCell>(uniqueId);
	}

	//Metoda tworzy obiekt klasy PowerStation i zwraca wska�nik na ten obiekt
	PowerStation *CPhysicalManager::CreatePowerStation(const std::wstring &uniqueId)
	{
		fprintf(stderr, "PowerStation created\n");
		return create<PowerStation>(uniqueId);
	}

	//Metoda tworzy obiekt klasy WindPowerStation i zwraca wska�nik na ten obiekt
	WindPowerStation *CPhysicalManager::CreateWindPowerStation(const std::wstring &uniqueId)
	{
		fprintf(stderr, "WindPowerStation created\n");
		return create<WindPowerStation>(uniqueId);
	}

	//Metoda tworzy obiekt klasy WindPowerStationMultipled i zwraca wska�nik na ten obiekt
	WindPowerStationMultipled *CPhysicalManager::CreateWindPowerStationMultipled(const std::wstring &uniqueId)
	{
		fprintf(stderr, "WindPowerStationMultipled created\n");
		return create<WindPowerStationMultipled>(uniqueId);
	}

	//Metoda tworzy obiekt klasy RelayStation i zwraca wska�nik na ten obiekt
	RelayStation *CPhysicalManager::CreateRelayStation(const std::wstring &uniqueId)
	{
		fprintf(stderr, "RelayStation created\n");
		return create<RelayStation>(uniqueId);
	}

	//Metoda tworzy obiekt klasy PowerRelayStation i zwraca wska�nik na ten obiekt
	PowerRelayStation *CPhysicalManager::CreatePowerRelayStation(const std::wstring &uniqueId)
	{
		fprintf(stderr, "PowerRelayStation created\n");
		return create<PowerRelayStation>(uniqueId);
	}

	//Metoda tworzy obiekt klasy SlotsRate i zwraca wska�nik na ten obiekt
	SlotsRate* CPhysicalManager::CreateSlotsRate(const std::wstring &uniqueId)
	{
		fprintf(stderr, "SlotsRate created\n");
		return create<SlotsRate>(uniqueId);
	}

	//Metoda tworzy obiekt klasy Communication i zwraca wska�nik na ten obiekt
	Communication *CPhysicalManager::CreateCommunication(const std::wstring &uniqueId)
	{
		fprintf(stderr, "Communication created\n");
		return create<Communication>(uniqueId);
	}

	//Metoda tworzy obiekt klasy LightingEquipment i zwraca wska�nik na ten obiekt
	LightingEquipment *CPhysicalManager::CreateLightingEquipment(const std::wstring &uniqueId)
	{
		fprintf(stderr, "LightingEquipment created\n");
		return create<LightingEquipment>(uniqueId);
	}

	//Metoda tworzy obiekt klasy CGround i zwraca wska�nik na ten obiekt
	CGround *CPhysicalManager::CreateGround(const std::wstring &uniqueId)
	{
		fprintf(stderr, "CGround created\n");
		return create<CGround>(uniqueId);
	}
	
	//Metoda usuwa obiekt klasy CPhysical z kontenera
	void CPhysicalManager::DestroyPhysical(CPhysical* physical)
	{
		if (physical->m_physical_manager_index >= 0)
		{
			m_physicals[physical->m_physical_manager_index] = m_physicals[m_physicals.size()-1];
			m_physicals[physical->m_physical_manager_index]->m_physical_manager_index = physical->m_physical_manager_index;
			m_physicals.pop_back();
			physical->m_physical_manager_index = -1;
			fprintf(stderr, "PhysicalsManager::DestroyPhysical - %ls\n", physical->GetUniqueId().c_str());
			DestroyPhysical(physical->GetUniqueId());
			delete physical;
		}
	}

	//Metoda usuwa obiekt klasy CPhysical z kontenera
	void CPhysicalManager::DestroyPhysical(const std::wstring& id_physical)
	{
		if (m_named_physicals.find(id_physical) != m_named_physicals.end())
		{
			CPhysical* physical = m_named_physicals[id_physical];
			m_named_physicals.erase(m_named_physicals.find( id_physical));
			DestroyPhysical(physical);
		}
	}

	//Metoda usuwa wszystkie obiekty z kontenera
	void CPhysicalManager::Clear(bool force_destroy_instantly)
	{
		std::vector<CPhysical*>::iterator it;

		for (it = m_physicals.begin(); it != m_physicals.end(); it++)
		{
			(*it)->MarkForDelete();
		}

		if (force_destroy_instantly)
		{
			frameStarted(0.0f);
		}
	}

	//Metoda zwraca sta�� referencj� do kontenera z nazwami wszystkich zarejestorwanych obiekt�w CPhysical
	const std::map<std::wstring, CPhysical*>& CPhysicalManager::GetNamedPhysicals()
	{
		return m_named_physicals;
	}

	//Metoda zwraca sta�� referencj� do kontenera z wszystkimi wska�nikami zarejestorwanych obiekt�w CPhysical
	const std::vector<CPhysical *> &CPhysicalManager::GetPhysicals()
	{
		return m_physicals;
	}

	//Metoda zwraca wska�nik na obiekt klasy CPhysical z kontenera na podstawie identyfikatora
	CPhysical* CPhysicalManager::GetPhysicalById(const std::wstring& physical_id)
	{
		if (m_named_physicals.find(physical_id) != m_named_physicals.end())
			return m_named_physicals[physical_id];
		else
		{
			fprintf(stderr, "PhysicalsManager::GetPhysicalById - %ls key not found in m_named_physicals map", physical_id.c_str());
			return NULL;
		}
	}

	//metody p o m o c n i c z e	implementacja

	//Metoda zwraca sta�� referencj� na kontener, w kt�rym s� wska�niki na obiekty klasy WindPowerStation
	//elektrownie wiatrowe
	const std::vector<WindPowerStation*>& CPhysicalManager::GetWindPowerstations()
	{
		std::vector<CPhysical*>::iterator	it;	//iterator tego kontenera
		for (it = m_physicals.begin(); it != m_physicals.end(); it++)
		{
			if ((*it)->GetCategory() == PHYSICAL_WINDPOWERSTATION)
				m_wind_powerstation.push_back((WindPowerStation*)*it);
		}
		return m_wind_powerstation;
	}

	///
	///Wirtualny interfejs - implementacja
	///
	void CPhysicalManager::Cleanup()
	{
		fprintf(stderr, "CPhysicalManager::Cleanup()\n");

		//nie jestem do ko�ca pewien tego kodu...
		//std::vector<CPhysical*>::iterator it;
		//for (it = m_physicals.begin(); it != m_physicals.end(); it++)
		//	DestroyPhysical(*(it));
		Clear();
		fprintf(stderr, "CPhysicalManager::Cleanup() done...\n");
	}


	//implementajca metod private:

	//Prywatna metoda sprawdzaj�ca jaki identyfikator nada� obiektowi przy utworzeniu
	void CPhysicalManager::CheckUniqueId(std::wstring& new_unique_id)
	{
		static long physicalCount = 0;
		//je�li identyfikator jest ci�giem pustych znak�w
		//lub w kontenerze s� ju� jakie� nazwy
		if ((new_unique_id == L"" ) || (m_named_physicals.count(new_unique_id) > 0))
			do
			{
				//to tworzymy nazw� zsyntetyzowan�
				//do s�owa "physical" do dajemy warto�� licznika zamienion� na string
				new_unique_id = L"physical" + stringutils::ToWString(physicalCount++);
			}
			while (m_named_physicals.find(new_unique_id) != m_named_physicals.end());
	}
}//namespace logic
