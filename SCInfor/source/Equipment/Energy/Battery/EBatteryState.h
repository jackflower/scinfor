//  _________________________________________________
// | EBatteryState.h - enumeration of states battery |
// | Jack Flower - May 2016                          |
// |_________________________________________________|
//

#ifndef H_E_BATTERY_STATE_JACK
#define H_E_BATTERY_STATE_JACK

namespace equipment
{
	///
	///Wyliczenie stan�w dla obiektu CBattery
	///
	enum EBatteryState
	{
		BATTERY_DEFAULT		= 0,//stan default - czas przed w��czeniem
		BATTERY_CHARGED		= 1,//bateria - na�adowana funkcjonuje
		BATTERY_RESERVE		= 2,//bateria - stan rezerwy energii
		BATTERY_DISCHARGED	= 3,//bateria roz�adowna - zero energii
		BATTERY_DAMAGE		= 4 //bateria uszkodzona - tylk wymiana 
	};
}//namespace equipment
#endif//H_E_BATTERY_STATE_JACK
