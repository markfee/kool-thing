#define WIN32
#define __WINDOWS_MM__

#pragma comment(lib, "winmm.lib") 

using namespace std; 
#include <iostream>
#include "rtmidi\RtMidi.h"

int main(int argc, char* argv[]) {
	RtMidiIn  *midiin = 0;
	RtMidiOut *midiout = 0;
	// RtMidiIn constructor
	try {
		midiin = new RtMidiIn();
	}
	catch (RtMidiError &error) {
		error.printMessage();
		exit(EXIT_FAILURE);
	}
	// Check inputs.
	unsigned int nPorts = midiin->getPortCount();
#ifdef WIN32
	std::cout << "\nThere are " << nPorts << " MIDI input sources available.\n";
#endif // WIN32

	std::cout << "\nThere are " << nPorts << " MIDI input sources available.\n";
	std::string portName;
	for (unsigned int i = 0; i<nPorts; i++) {
		try {
			portName = midiin->getPortName(i);
		}
		catch (RtMidiError &error) {
			error.printMessage();
			goto cleanup;
		}
		std::cout << "  Input Port #" << i + 1 << ": " << portName << '\n';
	}
	// RtMidiOut constructor
	try {
		midiout = new RtMidiOut();
	}
	catch (RtMidiError &error) {
		error.printMessage();
		exit(EXIT_FAILURE);
	}
	// Check outputs.
	nPorts = midiout->getPortCount();
	std::cout << "\nThere are " << nPorts << " MIDI output ports available.\n";
	for (unsigned int i = 0; i<nPorts; i++) {
		try {
			portName = midiout->getPortName(i);
		}
		catch (RtMidiError &error) {
			error.printMessage();
			goto cleanup;
		}
		std::cout << "  Output Port #" << i + 1 << ": " << portName << '\n';
	}
	cout << "Hello World" << endl;
	cout << "Press ENTER to continue...";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << '\n';
	// Clean up
cleanup:
	delete midiin;
	delete midiout;
	return 0;
}