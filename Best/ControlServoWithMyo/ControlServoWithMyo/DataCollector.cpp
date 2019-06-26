#include "stdafx.h"
#include "DataCollector.h"

// onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.

void DataCollector::onUnpair(myo::Myo * myo, uint64_t timestamp)
{
	// We've lost a Myo.
	// Let's clean up some leftover state.
	emgSamples.fill(0);
}

// onEmgData() is called whenever a paired Myo has provided new EMG data, and EMG streaming is enabled.

void DataCollector::onEmgData(myo::Myo * myo, uint64_t timestamp, const int8_t * emg)
{
	for (int i = 0; i < 8; i++) {
		emgSamples[i] = emg[i];
	}
}

// We define this function to print the current values that were updated by the on...() functions above.

void DataCollector::print()
{
	// Clear the current line
	std::cout << '\r';

	// Print out the EMG data.
	for (size_t i = 0; i < emgSamples.size(); i++) {
		std::ostringstream oss;
		oss << static_cast<int>(emgSamples[i]);
		std::string emgString = oss.str();

		std::cout << '[' << emgString << std::string(4 - emgString.size(), ' ') << ']';
	}

	std::cout << std::flush;
}
