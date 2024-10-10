#include "mlp.h"

#define ZMIN_LOC -4
#define ZMAX_LOC 4

MLP_out_arg_t Activation(MLP_out_arg_t z)
{

	MLP_out_arg_t result;
	MLP_out_arg_t abval;

    abval = abs(float(z));
    result = sig_c[0] + sig_c[1]*abval + (sig_c[2] * abval * abval);


	if (abval > ZMAX_LOC) {
		result = 1;
	}

	if (z < 0) {
		result = 1 - result;
	}

    return result;

}

void mlp(MLP_inp_arg_t x[784], MLP_out_arg_t y[10]) {

	MLP_out_arg_t hidden_layer[25];
	MLP_out_arg_t sumA = 0.0;
	MLP_out_arg_t sumB = 0.0;

	// DEBUG
	cout << "SUM + BIASES: ";
	//

	for (unsigned i = 0; i < 25; i++) {
		for (unsigned j = 0; j < 784; j++) {
			sumA = sumA + (x[j] * weights_1[j][i]);
		}
		hidden_layer[i] = Activation(sumA + biases_1[i]);

		// DEBUG
		//cout << sumA + biases_1[i] << " ";
		cout << (sumA + biases_1[i]).to_double() << " ";
		//

		sumA = 0;
	}

	// DEBUG
	cout << endl << "HIDDEN LAYER: ";
	for (unsigned i = 0; i < 25; i++) {
		//cout << hidden_layer[i] << " ";
		cout << hidden_layer[i].to_double() << " ";
	}
	cout << endl;
	//

	for (unsigned i = 0; i < 10; i++) {
		for (unsigned j = 0; j < 25; j++) {
			sumB = sumB + (hidden_layer[j] * weights_2[j][i]);
		}
		y[i] = Activation(sumB + biases_2[i]);
		sumB = 0;
	}

	// DEBUG
	cout << "LOCAL OUTPUT: ";
	for (unsigned i = 0; i < 10; i++) {
		//cout << y[i] << " ";
		cout << y[i].to_double() << " ";
	}
	cout << endl;
	//
}
