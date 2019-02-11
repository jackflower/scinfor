/*
 ____________________________________
| CLogic.h - definicja klasy.        |
| Jack Flower - January 2013.        |
|____________________________________|

*/

#ifndef H_LOGIC_JACK
#define H_LOGIC_JACK

#include "../Utilities/Singleton/CSingleton.h"
#include "../Game/Listener/IFrameListener.h"
#include "../Game/Listener/IKeyListener.h"
#include "../Game/Listener/IMouseListener.h"
#include <string>
#include <map>

using namespace listener;

#define gLogic CLogic::GetSingleton()

namespace logic
{
	///
	///Klasa reprezentuje mechanizm logiki rozgrywki
	///
	class CLogic : public CSingleton<CLogic>, IFrameListener, IKeyListener, IMouseListener
	{
	public:

		///
		///Konstruktor
		///
		CLogic();

		///
		///Destruktor wirtualny
		///
		virtual ~CLogic();

		///
		///Wirtualna metoda aktualizuj�ca logik� obiekt�w
		///
		virtual void frameStarted(float secondsPassed);

		///
		///Wirtualna metoda aktualizuj�ca logik� gry - zdarzenia klawiatury
		///
		///@param &e - sta�a referencja na obiekt klasy sf::Event::KeyEvent
		///
		virtual void KeyPressed(const sf::Event::KeyEvent &e);
	    
		///
		///Wirtualna metoda aktualizuj�ca logik� gry - zdarzenia myszy
		///
		///@param &e - sta�a referencja na obiekt klasy sf::Event::MouseButtonEvent
		///
		virtual void MousePressed(const sf::Event::MouseButtonEvent &e);

		///
		///Metoda zwraca stan logiki gry
		///
		const std::wstring& GetState();

		///
		///Metoda ustawia stan logiki gry
		///
		///@param &state - sta�a referencja na obiekt klasy std::wstring
		///
		void SetState(const std::wstring& state);

		///
		///Metoda uruchamia now� rozgrywk�
		///
		///@param &start_file - sta�a referncja na obiekt klasy std::wstring
		///
		void StartNewGame(const std::wstring& start_file = L"new-game");
		
		///
		///Metoda restaruje rozgrywk�
		///
		void CheckRestart();
		
		///
		///Metoda powrotu do g��wnego menu ustawie� gry
		///
		void ExitToMainMenu();
		
		///
		///Metoda czy�ci stan rozgrywki
		///
		void Clear();

		///
		///Metoda zapisuje stan gry
		///
		///@param name - sta�a referencja na obiekt klasy std::string
		///
		void SaveGame(const std::string &name);

		///
		///Metoda odczytuje stan zapisanej gry
		///
		///@param name - sta�a referencja na obiekt klasy std::string
		///
		void LoadGame(const std::string& name);

		///
		///Metoda aktualizuje wszystkie obiekty dziedzicz�ce po Physical
		///
		///@param secondsPassed - up�ywaj�cy czas gry
		///
		void UpdatePhysicals(float secondsPassed);

		///
		///Metoda aktualizuje wszystkie obiekty dziedzicz�ce po CMapPhysical
		///
		///@param secondsPassed - up�ywaj�cy czas gry
		///
		void UpdateMapPhysicals(float secondsPassed);

	private:
		
		std::wstring m_state;				//stan logiki gry
	};
}//namespace logic
#endif//H_LOGIC_JACK
