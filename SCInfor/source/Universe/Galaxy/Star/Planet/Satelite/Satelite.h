//  _____________________________________
// | Satelite.h - class definition klasy |
// | Jack Flower - May 2014              |
// |_____________________________________|
//

#ifndef H_SATELITE_JACK
#define H_SATELITE_JACK

#include "../../../../../RTTI/RTTI.h"
#include "../../../../Interaction/EntityTemperature.h"
#include "../../../../Interaction/Gravity.h"

using namespace interaction;

namespace universe
{
	namespace galaxy
	{
		namespace star
		{
			namespace planet
			{
				namespace satelite
				{
			
					///
					///Klasa reprezentuje satelitę
					///
					class Satelite
					{
						RTTI_DECL;

					public:

						///
						///Knstruktor
						///
						Satelite();

						///
						///Konstruktor kopiujący
						///
						///@param copy - stała referecja na obiekt klasy Satelite
						///
						Satelite(const Satelite & copy);

						///
						///Konstruktor przenoszący
						///
						///@param other - referencja do r-wartości
						///
						Satelite(Satelite && other);

						///
						///Destruktor
						///
						~Satelite();

						///
						///Przeciążony operator przypisania kopiowania
						///
						///@param copy - stała referencja na obiekt klasy Satelite
						///
						Satelite & operator=(const Satelite & copy);

						///
						///Przeciążony operator przypisania przenoszenia
						///
						///@param other -  referencja do r-wartości
						///
						Satelite & operator=(Satelite && other);

						///
						///Metoda zwraca typ obiektu /RTTI/
						///
						const std::string getType() const;

						///
						///Metoda zwraca temperaturę satelity
						///
						const float getSateliteTemperature() const;

						///
						///Metoda ustawia temperaturę satelity
						///
						///@param satelite_temperature - temperatura satelity
						///
						void setSateliteTemperature(float satelite_temperature);

						///
						///Metoda zwraca grawitację satelity
						///
						const float getSateliteGravity() const;

						///
						///Metoda ustawia grawitację satelity
						///
						///@param satelite_gravity - grawitację satelity
						///
						void setSateliteGravity(float satelite_gravity);

					private:
					
						EntityTemperature m_satelite_temperature; //temperatura satelity
						Gravity m_satelite_gravity; //grawitacja
					};
				}//namespace satelite
			}//namespace planet
		}//namespace star
	}//namespace galaxy
}//namespace universe
#endif//H_SATELITE_JACK
