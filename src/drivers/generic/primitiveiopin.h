#ifndef DRIVERS_GENERIC_PRIMITIVEIOPIN_H
#define DRIVERS_GENERIC_PRIMITIVEIOPIN_H

namespace drv {
namespace generic {

class PrimitiveIoPin {
	//Implementation for a basic (do-nothing) GPIO pin
	public:
		static PrimitiveIoPin null() { return PrimitiveIoPin(); }
		//We want to use this PrimitiveIoPin on any architecture, 
		// so let it be constructed with whatever platform-specific arguments the config file uses with its IO pins
		template <typename ...T> PrimitiveIoPin(T ...args) {}

		//do-nothing implementations for basic functions
		inline GpioPinIdType id() const { return -1; }
		inline void makeDigitalOutput(IoLevel) {}
	    //configure the pin to be an input
	    inline void makeDigitalInput() {}
	    //read the pin's input value (assumes pin is configured as digital)
	    inline IoLevel digitalRead() const { return IoLow; }
	    inline void digitalWrite(IoLevel) {}
};

}
}


#endif