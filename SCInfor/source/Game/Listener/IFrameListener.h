//  ____________________________________________________________________________________________________
// | IFrameListener.h - interfejs abstrakcyjnej klasy bazowej z metodami aktulizującymi logikę obiektu  |
// | Jack Flower - February 2012                                                                        |
// |____________________________________________________________________________________________________|
//

#ifndef H_FRAME_LISTENER_JACK
#define H_FRAME_LISTENER_JACK

namespace listener
{
	///
	///Klasa bazowa reprezentuje publiczny interface dla obieków aktulizujących logikę w czasie rzeczywistym
	///
	class IFrameListener
	{
	public:

		///
		///Wirtualny destruktor
		///
		virtual ~IFrameListener() {};

		///
		///Wirtulana abstrakcyjna metoda aktualizująca logikę obiektu
		///
		///@param elapsed_time - upływający czas
		///
		virtual void frameStarted(float elapsed_time) = 0;
	};
}//namespace listener
#endif//H_FRAME_LISTENER_JACK
