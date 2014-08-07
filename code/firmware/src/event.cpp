#include "event.h"
#include "common/timeutil.h" //for timespecLt


AxisIdType Event::stepperId() const {
	return this->_stepperNum;
}
StepDirection Event::direction() const {
	return this->_isForward ? StepForward : StepBackward;
}
/*timespec Event::time() const {
	return timepointToTimespec(this->_time);
}*/
EventClockT::time_point Event::time() const {
	return this->_time;
}

/*bool Event::isTime() const {
	//time to handle event if now >= _time
	return !timespecLt(timespecNow(), this->_time);
}*/

bool Event::isNull() const {
	return this->stepperId() == NULL_STEPPER_ID;
}

//Event::Event(const timespec &t, AxisIdType stepperNum, StepDirection dir) : _time(timespecToTimepoint<EventClockT::time_point>(t)), _stepperNum(stepperNum), _isForward(dir==StepForward) {}
Event::Event(EventClockT::time_point t, AxisIdType stepperNum, StepDirection dir) : _time(t), _stepperNum(stepperNum), _isForward(dir==StepForward) {}

Event Event::StepperEvent(float relTime, AxisIdType stepperNum, StepDirection dir) {
	struct timespec t;
	t.tv_sec = relTime;
	t.tv_nsec = (relTime-t.tv_sec)*1000000000;
	return Event(timespecToTimepoint<EventClockT::time_point>(t), stepperNum, dir);
}

/*void Event::offset(const struct timespec& offset) {
	this->offset(std::chrono::duration_cast<EventClockT::duration>(timespecToDuration(offset)));
}*/
void Event::offset(const EventClockT::duration &offset) {
	//timespec t = durationToTimespec(offset);
	//this->offset(t);
	this->_time += offset;
}
void Event::offsetNano(unsigned nsec) {
	this->offset(std::chrono::duration_cast<EventClockT::duration>(std::chrono::nanoseconds(nsec)));
	/*this->_time.tv_nsec += nsec;
	if (this->_time.tv_nsec > 999999999) {
        this->_time.tv_sec += 1;
        this->_time.tv_nsec -= 1000000000;
    }*/
}

bool Event::operator<(const Event &other) const {
	return this->time() < other.time();
	//return timespecLt(this->time(), other.time());
}

bool Event::operator>(const Event &other) const {
	return this->time() > other.time();
	//return timespecLt(other.time(), this->time());
}

