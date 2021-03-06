﻿//  __________________________________________
// | EnemyTemplate.h - class definition       |
// | Jack Flower - November 2012              |
// |__________________________________________|
//

#ifndef H_ENEMY_TEMPLATE_JACK
#define H_ENEMY_TEMPLATE_JACK

#include "ActorTemplate.h"
#include "../Logic/Enemy/Enemy.h"
#include <string>
#include <vector>

namespace factory
{
	///
	///Klasa reprezentuje generyczny wzorzec wrogiej jednostki
	///
	class EnemyTemplate : public ActorTemplate
	{
		RTTI_DECL;

	public:

		///
		///Konstruktor
		///
		EnemyTemplate();

		///
		///Destruktor wirtualny
		///
		virtual ~EnemyTemplate();

		///
		///Metoda zwraca typ obiektu /RTTI/
		///
		const std::string getType() const;

		///
		///Wirtualna metoda zwalniająca zasób - implementacje w klasach pochodnych
		///
		void drop();

		///
		///Metoda ładująca dane
		///
		///@param name - stała referencja na std::string
		///
		bool load(const std::string & name);

		///
		///Wirtualna metoda ładująca dane z xml
		///
		///@param xml - referencja na obiekt klasy Xml
		///
		bool load(Xml & xml);

		///
		///Metoda tworzy obiekt klasy Enemy
		///
		///@param id - nazwa identyfikatora - obiekt klasy std::wstring
		///
		Enemy *create(std::wstring id = L"");

	protected:

		///
		///Wirtualna metoda wypełniająca danymi obiekt klasy Enemy
		///
		///@param *enemy - wskaźnik na obiekt klasy Enemy
		///
		virtual void fill(Enemy *enemy);


	private:

		std::vector<std::wstring> m_enemy_AI; //kontener nazw dostępnych schematów AI wroga...to do...
		//lepszym rozwiązaniem byłoby posiadanie kontenera
		//zawierającego obiekty (wskaźniki) klasy, która stanowiłaby
		//opakowanie funkcjonaności, jaką jest schemat AI, i/lub
		//innych zachować
	};
}//namespace factory
#endif //H_ENEMY_TEMPLATE_JACK
