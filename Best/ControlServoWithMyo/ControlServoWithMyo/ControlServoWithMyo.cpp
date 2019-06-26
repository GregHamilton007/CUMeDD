#include "stdafx.h"

#include "DataCollector.h"


using namespace System;
using namespace System::IO::Ports;
int main(array<System::String ^> ^args)
{
	SerialPort port("COM3", 9600);
 	port.Open();

	try {
		myo::Hub hub("com.example.emg-data-sample");
		std::cout << "Attempting to find a Myo..." << std::endl;
		// Next, we attempt to find a Myo to use. If a Myo is already paired in Myo Connect, this will return that Myo
		// immediately.
		// waitForMyo() takes a timeout value in milliseconds. In this case we will try to find a Myo for 10 seconds, and
		// if that fails, the function will return a null pointer.
		myo::Myo* myo = hub.waitForMyo(10000);

		// If waitForMyo() returned a null pointer, we failed to find a Myo, so exit with an error message.
		if (!myo) {
			throw std::runtime_error("Unable to find a Myo!");
		}

		// We've found a Myo.
		std::cout << "Connected to a Myo armband!" << std::endl << std::endl;

		// Next we enable EMG streaming on the found Myo.
		myo->setStreamEmg(myo::Myo::streamEmgEnabled);
		int sum = 0;
		// Next we construct an instance of our DeviceListener, so that we can register it with the Hub.
		DataCollector collector;

		// Hub::addListener() takes the address of any object whose class inherits from DeviceListener, and will cause
		// Hub::run() to send events to all registered device listeners.
		hub.addListener(&collector);
		// Finally we enter our main loop.
		int avg;
		while (1) {
			// In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
			// In this case, we wish to update our display 50 times a second, so we run for 1000/20 milliseconds.
			hub.run(1000);
			// After processing events, we call the print() member function we defined above to print out the values we've
			// obtained from any events that have occurred.
			collector.print();

			sum = 0;
			int val = 0;
			for (int i = 0; i < 8; i++) {
				val = collector.emgSamples[i];
				if (val > 0) {
					sum += val;
				}
				else {
					sum -= val;
				}
			}
			avg = sum / 80;
			port.Write(avg.ToString());
			//std::cout << port.Read <<std::endl;
			//port.Write(average(collector.emgSamples, collector.emgSamples.size()));	
		}

		// If a standard exception occurred, we print out its message and exit.
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::cerr << "Press enter to continue.";
		std::cin.ignore();
		return 1;
	}
	//

	return 0;
}