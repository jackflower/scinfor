﻿//  __________________________________
// | CAIDemo.h - class definition     |
// | Jack Flower April 2015           |
// |__________________________________|
//

#ifndef H_AIDEMO_JACK
#define H_AIDEMO_JACK

#include <string>
#include "../../RTTI/RTTI.h"
//#include "../../Utils/Memory/CSafePtr.h"
//#include "ActorAI.h" //czy to pomoże?
// - jakkolwiek, uporządkować kod, aby nie byłó, aby więcej
//   jak jedna klas abyła w jednym pliku...

class CAISchemeManager;	//zapowiedź wobec powyższego...
namespace logic
{
	class ActorAI;			//zapowiedź wobec powyższego...
}
class ActorAIData;		//zapowiedź wobec powyższego...

using namespace logic;

namespace artificialintelligence
{
	///
	///Klasa reprezentuje skalę bazową definiującą interfejs
	///
	class CAIScheme
	{
		RTTI_DECL;

	public:	

		CAIScheme()
		{
			//RTTI_IMPL_NOPARENT(CAIScheme);
		}
		
		virtual ~CAIScheme() {};
		
		//virtual void RegisterAI(Memory::CSafePtr<ActorAI> ai) {}
		//virtual void UnregisterAI(Memory::CSafePtr<ActorAI> ai) {}

		//bez żadnych wynalazków...wskaźnik...po prostu...
		virtual void RegisterAI(ActorAI* ai) {};
		virtual void UnregisterAI(ActorAI* ai) {};


		virtual void update(float dt) {};
		virtual void UpdateAI(ActorAIData *ai, float dt) = 0;
		virtual std::string GetName() const = 0;

		virtual void Init(CAISchemeManager &sm) = 0;
	};
}//namespace artificialintelligence
#endif//H_AIDEMO_JACK
