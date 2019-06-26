#pragma once

#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "myo/myo.hpp"

class DataCollector : public myo::DeviceListener {
public:
	DataCollector()
		: emgSamples()
	{
	}

	// onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
	void onUnpair(myo::Myo* myo, uint64_t timestamp);

	// onEmgData() is called whenever a paired Myo has provided new EMG data, and EMG streaming is enabled.
	void onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg);

	// There are other virtual functions in DeviceListener that we could override here, like onAccelerometerData().
	// For this example, the functions overridden above are sufficient.

	// We define this function to print the current values that were updated by the on...() functions above.
	void print();

	// The values of this array is set by onEmgData() above.
	std::array<int8_t, 8> emgSamples;
};