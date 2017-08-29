#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define nbuf 65536

static inline double sq(double x) {return x*x;}

void fileerror(const char *filename, FILE *file)
{
    fclose(file);
    fprintf(stderr, "error reading file %s\n", filename);
    exit(4);
}

void openerror(const char *filename)
{
    fprintf(stderr, "error opening file %s\n", filename);
    exit(3);
}

FILE *openandfindlastbeefens(const char *filename, char *buf)
{
    FILE *f;
    unsigned long int u,lastu;
    
    f = fopen(filename, "r");
    if(!f) openerror(filename);
    
    u = 1;
    while(fgets(buf,nbuf,f) && !strstr(buf,"BEEFens")) u++;
    if(!strstr(buf,"ensemble energies")) fileerror(filename, f);

    do {
	lastu = u;
	u++;
	while(fgets(buf,nbuf,f) && !strstr(buf,"BEEFens")) u++;
    } while(strstr(buf,"ensemble energies"));
    
    if(fseek(f,0,SEEK_SET)) fileerror(filename, f);
    
    for(u=0;u<lastu;u++) fgets(buf,nbuf,f);
    
    return f;
}


int main(int argc, char **argv)
{
    char buf[nbuf];
    double *samples;
    FILE *dftout;
    double d,e;
    int nsamples;

    if(argc < 3)
    {
	fprintf(stderr, "usage: %s factor1 outputfile1 ... factorN outputfileN\n", argv[0]);
	return 1;
    }

    dftout = openandfindlastbeefens(argv[2], buf);
    nsamples = strtol(strstr(buf,"BEEFens")+7, NULL, 10);

    samples = (double *) malloc(nsamples*sizeof(double));
    if(!samples)
    {
	fclose(dftout);
	fputs("not enough memory for ensemble energies\n", stderr);
	return 2;
    }

    d = strtod(argv[1], NULL);
    for(int j=0;j<nsamples;j++)
    {
	if(!fgets(buf,nbuf,dftout)) fileerror(argv[2], dftout);
	samples[j] = d*strtod(buf, NULL);
    }
    fclose(dftout);
    for(int i=3;i<argc;i+=2)
    {
	d = strtod(argv[i], NULL);
	dftout = openandfindlastbeefens(argv[i+1], buf);
	for(int j=0;j<nsamples;j++)
	{
	    if(!fgets(buf,nbuf,dftout)) fileerror(argv[i+1], dftout);
	    samples[j] += d*strtod(buf, NULL);
	}
	fclose(dftout);
    }

    d = samples[0];
    for(int i=1;i<nsamples;i++) d += samples[i];
    d /= (double) nsamples;
    e = sq(samples[0]-d);
    for(int i=1;i<nsamples;i++) e += sq(samples[i]-d);
    free(samples);

    printf("%.5g standard deviation\n", sqrt(e/nsamples));

    return 0;
}
