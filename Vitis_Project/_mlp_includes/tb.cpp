#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "mlp.h"

#define DAT_FILE_NAME "cppvars.dat"
#define NUM_INPUTS 100

using namespace std;

int main(void) {

	MLP_inp_arg_t imgInp [NUM_INPUTS][784];
	unsigned imgTag [NUM_INPUTS];

	MLP_out_arg_t mlpOut [10];

	ifstream img_vars;
	string parseLine;

	MLP_out_arg_t calib = 255.0;

	MLP_out_arg_t maxVal = 0.0;
	unsigned maxIndex = 0;

	float hitRate = 0.0;
	unsigned numCorrect = 0;

	img_vars.open(DAT_FILE_NAME);
	if (!img_vars.is_open()) {
		cout << "Could not open file: " << DAT_FILE_NAME << endl;
		exit(0);
	}
	else {
		cout << "File " << DAT_FILE_NAME << " opened successfully." << endl;
	}

	// Parse .dat file:
	// .dat file format should be 1 line per pixel...
	// followed by tag value
	unsigned pixel_val_tmp;

	for (unsigned i = 0; i < NUM_INPUTS; i++) {
		for (unsigned j = 0; j < 784; j++) {
			img_vars >> pixel_val_tmp;
			imgInp[i][j] = pixel_val_tmp;
		}
		img_vars >> pixel_val_tmp;
		imgTag[i] = pixel_val_tmp;
	}

	// DEBUG: DISPLAY IMAGE
	for (unsigned i = 0; i < NUM_INPUTS; i++) {
		for (unsigned j = 0; j < 784; j++) {
			// Pad with spaces if needed
			if (imgInp[i][j] < 10) {
				cout << "  ";
			}
			else if (imgInp[i][j] < 100) {
				cout << " ";
			}
			cout << imgInp[i][j] << " ";
			if (((j + 1) % 28 == 0)) {
				cout << endl;
			}
		}
		cout << endl << "TAG: " << imgTag[i] << endl << endl;
	}

	// re-calibrate imgInp
	for (unsigned i = 0; i < NUM_INPUTS; i++) {
		for (unsigned j = 0; j < 784; j++) {
			imgInp[i][j] /= (MLP_inp_arg_t)calib;
		}
	}

//	// DEBUG: DISPLAY IMAGE
//		for (unsigned i = 0; i < NUM_INPUTS; i++) {
//			for (unsigned j = 0; j < 784; j++) {
//				// Pad with spaces if needed
//				if (imgInp[i][j] < 10) {
//					cout << "  ";
//				}
//				else if (imgInp[i][j] < 100) {
//					cout << " ";
//				}
//				cout << imgInp[i][j] << " ";
//				if (((j + 1) % 28 == 0)) {
//					cout << endl;
//				}
//			}
//			cout << endl << "TAG: " << imgTag[i] << endl << endl;
//		}

	// TEST MLP
	for (unsigned i = 0; i < NUM_INPUTS; i++) {
		mlp(imgInp[i], mlpOut);
		for (unsigned j = 0; j < 10; j++) {
			if (mlpOut[j] > maxVal) {
				maxVal = mlpOut[j];
				maxIndex = j;
			}
		}
		cout << "MLP OUTPUT: ";
		for (unsigned j = 0; j < 10; j++) {
			cout << mlpOut[j] << " ";
		}
		cout << endl;
		cout << "MAX INDEX: " << maxIndex << endl;
		cout << "IMAGE TAG: " << imgTag[i] << endl;
		if (maxIndex == imgTag[i]) {
			cout << "TEST " << i + 1 << "/" << NUM_INPUTS << " PASSED "<< endl;
			++numCorrect;
		}
		else {
			cout << "TEST " << i + 1 << "/" << NUM_INPUTS << " FAILED "<< endl;
		}
		cout << "------------" << endl;
		maxIndex = 0;
		maxVal = 0;
	}

	cout << "PASS RATE: " << (float)numCorrect/(float)NUM_INPUTS << endl;

	return 0;
}
