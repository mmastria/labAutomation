#include <LabRelay.h>

class LabSwitchOpenedWrapper {

	public:
	
	static void event(LabRelay relay);
	static void setRelay(LabRelay* relay);
	
	private:
	
	static LabRelay* _relay;

};