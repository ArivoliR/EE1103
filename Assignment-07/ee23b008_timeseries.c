/*
Roll Numbers, Names : EE23B008, Arivoli Ramamoorthy
                      EE23B065, Rohita Datta 
version: 1.0
description: 
- Program generates a time series of Lorentzian/Gaussian peaks with varying widths and amplitudes
- Normal noise is added to the location of peaks and widths
= Average and standard devations of time and width are computed to analyze the effects of noise on parameter estimation 
inputs: M, T, a and type of peak "Gaussian" or "Lorentzian"
outputs: avg(T) avg(a) stdev(T) stdev(a)
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>

#define MAX_SIZE 1000000 

struct Peak{
  double hpeak;       //x coord of peak
  double amplitude;   //y coord of peak
  double width;       //(r-l)/2
  struct Peak* next;
};


//noise function defined this way to make it easier for when noise needs to be added
float noise(){

	float u1 = random() / (RAND_MAX + 1.0);       //always less than 1
	float u2 = random() / (RAND_MAX + 1.0);
	float z0 = sqrt(-2*log(u1))*cos(2*M_PI*u2); 
        return z0;
}

//Defining the lorentz fn for the lorentzian curves
double lorentz(float m, float T, float a){
	float time;
	float lorentz = (pow(a,2)) / (pow((time-(m*T)),2) + pow(a,2));
	return lorentz;
}

//Defining gauss fn for the gaussian curves
double gauss(float m, float T, float a){
	float time;
	float gauss = exp(((-1)*pow((time-m*T),2)) / (2*pow(a,2)));
	return gauss;
}


//Function to generate graph(curve) based on input
double graph(float M, float T, float a, double gx[], double gy[], char c){
	
	double mean = 0;
	double rms = 0;
	double temp = a;
	double sd = 0;
	double var = 0;
	int ind = 0;
	int i =0;

	for(int m=1; m<=M; m++){
		for(double time = ((T*m) - (T/2)); time < ((T*m) + (T/2)); time += 0.1){
			a = temp;
			a += noise();  //adding noise to amplitude
			var = noise();
			if (ind < MAX_SIZE){
				if(c=='L'||c=='l'){
					gy[ind] = lorentz(m, T+noise(), a);   //adding noise to the time in the graph (shifts position of peak which we will use later to find average and stdev of T)
				}                                            
				else if(c=='G'||c=='g'){
					gy[ind] = gauss(m, T+noise(), a);
				}
			
				gy[ind] += var;                                
				gx[ind] = time;
				ind++;
				//printf("Width (a) at ind %d: %f\n", ind, a);
			}
		}
	}
}

//window filter
void window(double gx[], double gy[], double T, double M){ 
	int ind = 0;
	for (int m = 1; m <= M; m++) {
    		for (double time = ((T * m) - (T / 2)); time < ((T * m) + (T / 2)); time += 0.1) {
			if (ind < (MAX_SIZE - 10)) {
            			for (int i = 1; i <= 9; i++) {
                			int nextIndex = ind + i;
                			if (nextIndex < MAX_SIZE) {
                    				gy[ind] += gy[nextIndex];
					}
				}
			}
			gy[ind] = gy[ind] / 10;
			ind++;
		}
	}

}

//Function defined to search and find all the details of the struct Peak from the graph.
double search (float sv, double gx[], double gy[], double peak[], double fwhm[], char c, double T, double M){

	struct Peak* head = NULL;
	for(int i=0; i<M; i++){
		struct Peak* ptr= (struct Peak*)malloc(sizeof(struct Peak));
		ptr->next=head;
		head=ptr;
	}
	
	int ind = 0;
	float l,r;
	float max = 0;
	float a = 0;
	int peakind = 0;
	int tmp;


	for(int m = 1; m<=M; m++){
                peakind = 0;                                                                     //index of peak
		for(double time = ((T * m) - (T / 2)); time < ((T * m) + (T / 2)); time += 0.1){
			if(gy[ind]>max){
				max=gy[ind];
				peakind = ind;
			}
			ind++;
		}
		if(head!=NULL){
			head->hpeak=gx[peakind];                                                 //storing it to the struct
			head->amplitude=max;
		}
		peak[m-1]=gx[peakind];
		max = 0;
		tmp = peakind;

		while(gy[peakind] > sv){
			peakind--;
		}
		l = gx[peakind];
		peakind = tmp;
		while(gy[peakind] > sv){
			peakind++;
		}
		r = gx[peakind];
		if(c=='L'||c=='l'){                                  //Lorentzian
			head->width=(r-l)/2; 
                  	fwhm[m-1]=(r-l)/2;
                	a += (r - l) / 2;
		}
		else if(c=='G'||c=='g'){                             //Gaussian
			head->width= (r-l) / (2*sqrt(log(4.0)));
                  	fwhm[m-1]= (r-l) / (2*sqrt(log(4.0)));
                  	a+=fwhm[m-1];
		}  
		//printf("Width (a) for peak %d: %f\n", m, fwhm[m-1]);
                head=head->next;
	}
	return a/M;                                //average of a
}


int main(int argc, char* argv[]){

	int M = atoi(argv[1]);
	float T = atof(argv[2]);
	float a = atof(argv[3]);
	char c = '\0';
        if (argv[4]!=NULL) {
           c = argv[4][0];
	}
        else {
           c = 'L'; //Lorentzian
        }

	double *gx =(double*)malloc(sizeof(double) * MAX_SIZE);
    	double *gy =(double*)malloc(sizeof(double) * MAX_SIZE);
    	double peak[M];
  	double fwhm[M];
	double avgT=0;
  	double rmsT=0;
    	double stddevT=0;
    	double avga=0;
    	double rmsa=0;
    	double stddeva=0;

    	int i = 0;
    	double sd = graph(M, T, a, gx, gy, c);
    
    	window(gx, gy, T, M);
    	
	avga=search(0.5, gx, gy, peak, fwhm, c, T, M); //sv=0.5
    	
	for(int j=0;j<M;j++){
		rmsa+=pow(fwhm[j],2);
	}
	rmsa = rmsa/M;                                          //rms here is the term in stddev formula, sum of n squares of x divided by n.


	for(int j=M-1;j>=1;j--){
		avgT+=(peak[j]-peak[j-1]);                      //The distance between two adjacent peaks
      		rmsT+=(peak[j]-peak[j-1])*(peak[j]-peak[j-1]);
	}

    avgT=avgT/(M-1); 
    rmsT=rmsT/((M-1));
    stddevT=sqrt(rmsT-(avgT*avgT));                             //standard deviation of T and a
    stddeva=sqrt(rmsa-(avga*avga));
   
    printf("%f ", avgT);
    printf("%f ", avga);
    printf("%f ", stddevT);
    printf("%f \n", stddeva);
    
    free(gx);
    free(gy);

    return 0;
}







