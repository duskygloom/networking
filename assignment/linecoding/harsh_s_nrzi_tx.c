// #define DISPLAY

#define SAMPLES_PER_BIT	10
#if defined(DISPLAY)
#define N_BITS			10
#else
#define N_BITS			10000
#endif
#define CMD_LENGTH		100

#define NOISEFILE		"normal.dat"
#define PYTHON			"../../bin/python3"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char command[CMD_LENGTH];
	const double noiselevels[] = {0.5, 1.0, 2.0, 3.0, 5.0, 10.0, 20.0, 50.0, 100.0};
#if defined(DISPLAY)
	const int nlevels = 1;
#else
	const int nlevels = sizeof(noiselevels)/sizeof(double);
#endif
	// clear noise file
	FILE *noisefile = fopen(NOISEFILE, "w");
	fclose(noisefile);
	// generate noise values for different levels
	for (int i = 0; i < nlevels; ++i) {
		sprintf(command, "%s noise_gen.py %lf %d >> log.txt", 
				PYTHON, noiselevels[i], N_BITS*SAMPLES_PER_BIT);
		system(command);
	}
	// generating random bitstream
	char bitstream[N_BITS];
	for (int i = 0; i < N_BITS; ++i)
		bitstream[i] = (rand() > RAND_MAX/2) + '0';
	FILE *bitsfile = fopen("bitstream.dat", "w");
	fputs(bitstream, bitsfile);
	fclose(bitsfile);
#ifdef DISPLAY
	printf("Bitstream: %s\n", bitstream);
#endif
	// writing values
	double noise, noiselevel;
	char DATAFILE[20];
	FILE *datafile;
	noisefile = fopen(NOISEFILE, "r");
	for (int i = 0; i < nlevels; ++i) {
		int state = 0;
		noiselevel = noiselevels[i];
		sprintf(DATAFILE, "data/datafile-%.1lf.dat", noiselevel);
		datafile = fopen(DATAFILE, "w");
		while (fgetc(noisefile) != '[' && !feof(noisefile));
		for (int j = 0; j < N_BITS; ++j) {
			int bit = bitstream[j] - '0';
			state = state^bit;
			for (int k = 0; k < SAMPLES_PER_BIT; ++k) {
				fscanf(noisefile, "%lf", &noise);
				fprintf(datafile, "%.4lf ", j+(double)k/SAMPLES_PER_BIT);
				fprintf(datafile, "%.4lf ", 2.0*state-1+noise);
				fputc('\n', datafile);
			}
			// printf("Wrote a bit. (%d)\n", j);
		}
		fclose(datafile);
		/** @note
		 * Instruction to plot and display graph.
		 * But make sure to decrease the value of N_BITS before uncommenting.
		 */
#ifdef DISPLAY
		sprintf(command, "%s plt.py %s %s >> log.txt", PYTHON, DATAFILE, bitstream);
		system(command);
#endif
	}
	fclose(noisefile);
	
	return 0;
}

