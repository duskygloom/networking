#define SAMPLES_PER_BIT	10
#define N_BITS			10000

#include <stdio.h>

int main()
{
	const double noiselevels[] = {0.5, 1.0, 2.0, 3.0, 5.0, 10.0, 20.0, 50.0, 100.0};
	const int nlevels = sizeof(noiselevels)/sizeof(double);
	// reading noisy values
	char rxbits[N_BITS];
	char DATAFILE[20];
	double sample, sample_avg, noiselevel;
	FILE *datafile, *bitsfile;
	for (int i = 0; i < nlevels; ++i) {
		noiselevel = noiselevels[i];
		sprintf(DATAFILE, "data/datafile-%.1lf.dat", noiselevel);
		datafile = fopen(DATAFILE, "r");
		for (int j = 0; j < N_BITS; ++j) {
			sample_avg = 0.0;
			for (int k = 0; k < SAMPLES_PER_BIT; ++k) {
				fscanf(datafile, "%lf", &sample);
				fscanf(datafile, "%lf", &sample);						// second double is the signal
				sample_avg += sample;
			}
			rxbits[j] = (sample_avg/SAMPLES_PER_BIT > 0) + '0';
		}
		// puts(rxbits);
		fclose(datafile);
		// finding error in rx bits
		bitsfile = fopen("bitstream.dat", "r");
		int errorbits = 0;
		for (int i = 0; i < N_BITS; ++i)
			if (fgetc(bitsfile) != rxbits[i]) ++errorbits;
		printf("\nError level: %.2lf\n", noiselevel);
		printf("Error percentage: %.4lf\n", 100.0*errorbits/N_BITS);
		fclose(bitsfile);
	}

	return 0;
}
