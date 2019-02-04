/*
 _____________________________________
| CPlayer.cpp - implementacja klasy.  |
| Jack Flower - March 2013.           |
|_____________________________________|

*/

#include "CPlayer.h"

namespace logic
{
	RTTI_IMPL(CPlayer, CActor);

	//Chroniony konstruktor domy�lny
	CPlayer::CPlayer(const std::wstring &uniqueId) 
	:	
		CActor	(uniqueId)	
	{
	}

	//Chroniony konstruktor kopiuj�cy
	CPlayer::CPlayer(const CPlayer &CPlayerCopy)
	:
		CActor	(CPlayerCopy)//konstruktor kopiuj�cy klasy bazowej
	{
	}

	//Chroniony destruktor wirtualny - u�ywany wy��cznie przez CPhysicalManager
	CPlayer::~CPlayer(void) 
	{
		//to do...
	}

	//Metoda zwraca typ obiektu /RTTI/
	const std::string CPlayer::GetType() const
	{
		return rtti.GetNameClass();
	}

	//Wirtualna metoda aktualizuj�ca obiekt
	void CPlayer::update(float dt)
	{
		CActor::update(dt);
	}

	//Wirtualan metoda zabija obiekt klasy CPlayer i wywo�uje odpowiednie czynno�ci z tym zwi�zane
	void CPlayer::Kill() 
	{
		//p�ki co b�dzie si� wywo�ywa�a metoda klasy bazowej
		CActor::Kill();
		//to do...
	}
}//namespace logic