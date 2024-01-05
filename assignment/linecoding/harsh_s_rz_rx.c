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
				fscanf(datafile, "%lf", &sample);						// skipping next two values
				fscanf(datafile, "%lf", &sample);						// time and noise for zero signal
			}
			sample_avg /= SAMPLES_PER_BIT;
			rxbits[j] = '2';											// default value, neither 0 or 1
			if (sample_avg > 0.45) rxbits[j] = '1';
			else if (sample_avg < -0.45) rxbits[j] = '0';				// a bit less space given to zero level
			// printf("Average: %lf\n", sample_avg);
		}
		// puts(rxbits);
		fclose(datafile);
		// finding error in rx bits
		bitsfile = fopen("bitstream.dat", "r");
		int errorbits = 0;
		for (int i = 0; i < N_BITS; ++i)
			if (fgetc(bitsfile) != rxbits[i]) ++errorbits;
		printf("\nError bits: %d\n", errorbits);
		printf("Error level: %.2lf\n", noiselevel);
		printf("Error percentage: %.4lf\n", 100.0*errorbits/N_BITS);
		fclose(bitsfile);
	}

	return 0;
}
