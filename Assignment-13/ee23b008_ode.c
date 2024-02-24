/*
Name: Arivoli Ramamoothy
Roll Number: ee23b008
Description:
This code solves the differential equations of the theta and phi derived from the landau-lifshiftz-gilbert equation using numerical methods like euler method, huen method and rk45 method
and calculates the R^2 values for euler and heun using rk45 as standard.  
Input: theta_start theta_stop alpha delta_t
Output: alpha delta_t R^2_Euler R^2_Huen
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
float derivs_theta(float theta,float alpha,float g,float H);
float euler(float theta,float h,float alpha,float H,float g);
float heun(float theta,float h,float alpha,float H,float g);
void rk45(float derivs_theta(float,float,float,float), float* t, float* theta, float h, float* epsilon,float alpha,float g,float H);
float r2_euler(int nre,int nrrk,FILE* fp4,FILE* fp5,float St);
float r2_heun(int nrh,int nrrk,FILE* fp7,FILE* fp8,float St);
float St_calc(int nrrk,FILE* fp10,float mean);
int main(int argc,char** argv){                          //main program
	float a,b;
	float theta_start=atof(argv[1]);
	float theta_stop=atof(argv[2]);
	float alpha=atof(argv[3]);
	float delta_t=atof(argv[4]);
        const float g=1.76e10;
	float h=delta_t;
	float t=0.0;
	float theta_old1=theta_start;
	float theta_old2=theta_start;
	float theta=theta_start;
	float dydx;
	const float H=1e-10;
	float theta_new1,theta_new2,e;
	float r=1.0;
	float sum=0.0;
	float time=0.01;
	FILE* euler_theta=fopen("euler_theta.txt","w");
	FILE* heun_theta=fopen("heun_theta.txt","w");
	FILE* rk45_theta=fopen("rk45_theta.txt","w");
	fprintf(euler_theta,"%f %f\n",t,theta_old1);
	fprintf(heun_theta,"%f %f\n",t,theta_old2);
	fprintf(rk45_theta,"%f %f\n",t,theta);
	int nre=1;                                        //no of rows in euler file
	int nrh=1;                                        //no of rows in heun file
	int nrrk=1;                                       //no of rows in rk45 file
	while(theta_old1<=theta_stop){
		theta_new1=euler(theta_old1,h,alpha,H,g);
		t+=h;
		fprintf(euler_theta,"%f %f\n",t,theta_new1);
		nre++;
		theta_old1=theta_new1;
	}
	t=0.0;
	while(theta_old2<=theta_stop){
		theta_new2=heun(theta_old2,h,alpha,H,g);
		t+=h;
		fprintf(heun_theta,"%f %f\n",t,theta_new2);
		nrh++;
		theta_old2=theta_new2;
	}
	t=0.0;
	while(theta<=theta_stop){
		sum+=theta;
		rk45(derivs_theta,&t,&theta,time,&e,alpha,g,H);
		fprintf(rk45_theta,"%f %f\n",t,theta);
		nrrk++;
		}
	fclose(euler_theta);
	fclose(heun_theta);
	fclose(rk45_theta);
	FILE* fp4=fopen("euler_theta.txt","r");
	FILE* fp10=fopen("rk45_theta.txt","r");
	float mean=(float)sum/nrrk;
	float St=St_calc(nrrk,fp10,mean);
	fclose(fp10);
	FILE* fp5=fopen("rk45_theta.txt","r");
	float R2_euler=r2_euler(nre,nrrk,fp4,fp5,St);
	fclose(fp5);
	FILE* fp7=fopen("heun_theta.txt","r");
	FILE* fp8=fopen("rk45_theta.txt","r");
	float R2_heun=r2_heun(nrh,nrrk,fp7,fp8,St);
	printf("%f %f %f %f",alpha,delta_t,R2_euler,R2_heun);
	fclose(fp4);
	fclose(fp7);
	fclose(fp8);
}
float derivs_theta(float theta,float alpha,float g,float H){                   //calculates the derivative of theta wrt t at a point
	return ((float)g*alpha*sin(theta)*H/(pow(alpha,2)+1));
}
float euler(float theta,float h,float alpha,float H,float g){                 //finds y(i+1) from xi and yi using euler method
	float dydx=derivs_theta(theta,alpha,g,H);
	return(theta+dydx*h);
}
float heun(float theta,float h,float alpha,float H,float g){                   //finds y(i+1) from xi and yi using simple heun method without iteration
	float dy1dx=derivs_theta(theta,alpha,g,H);
	float thetae=theta+dy1dx*h;
	float dy2dx=derivs_theta(thetae,alpha,g,H);
	float slope=(dy1dx+dy2dx)*0.5;		
	return(theta+slope*h);
}
void rk45(float derivs_theta(float,float,float,float), float* t, float* theta, float h, float* epsilon,float alpha,float g,float H)  //finds y(i+1) from xi and yi using rk45 method
{

  float c20 = 0.25, c21 = 0.25;
  float c30 = 0.375, c31 = 0.09375, c32 = 0.28125;
  float c40,c41, c42,c43;
  float c51, c52 = -8.0, c53, c54;
  float c60 = 0.5, c61, c62 = 2, c63, c64;
  float c65 = -0.275;
  float a1, a2 = 0, a3, a4, a5 = -0.2;
  float b1, b2 = 0, b3, b4, b5= -0.18, b6;
  float F1, F2, F3, F4, F5, F6, theta4;

  c40 = (float) 12/ (float) 13;
  c41 = (float) 1932/(float) 2197;
  c42 = (float) -7200/(float) 2197;
  c43 = (float) 7296/(float) 2197;
  c51 = c53 = (float) 439/ (float) 216;
  c54 = (float) -845/(float) 4104;
  c61 = (float) -8/(float) 27;
  c63 = (float) -3544/(float) 2565;
  c64 = (float) 1859/(float) 4104;
  a1 = (float) 25/(float) 216;
  a3 = (float) 1408/(float) 2565;
  a4 = (float) 2197/(float) 4104;
  b1 = (float) 16/(float) 135;
  b3 = (float) 6656/(float) 12825;
  b4 = (float) 28561/(float) 56430;
  b6 = (float) 2/(float) 55;


  F1 = h * derivs_theta(*theta,alpha,g,H);
  F2 = h * derivs_theta(*theta + c21 * F1,alpha,g,H);
  F3 = h * derivs_theta(*theta + c31 * F1 + c32 * F2,alpha,g,H);
  F4 = h * derivs_theta(*theta + c41 * F1 + c42 * F2 + c43 * F3,alpha,g,H);
  F5 = h * derivs_theta(*theta + c51 * F1 + c52 * F2 + c53 * F3 + c54 * F4,alpha,g,H );
  F6 = h * derivs_theta(*theta + c61 * F1 + c62 * F2 + c63 * F3 + c64 * F4 + c65 * F5,alpha,g,H);

  theta4 = *theta + a1 * F1 + a3 * F3 + a4 * F4 + a5 * F5;
  *theta += b1 * F1 + b3 * F3 + b4 * F4 + b5 * F5 + b6 * F6;
  *t += h;
  *epsilon = *theta - theta4;                                                     //the error between fourth order and fifth order rk estimates is added to fifth order estimate to increase accuracy
  *theta+=*epsilon;
}
float r2_euler(int nre,int nrrk,FILE* fp4,FILE* fp5,float St){                    //calculates the goodness of fit for euler taking rk45 as standard
	int i,j,k;
	float a,b,c,d;
	float e=0.0;
	float f=0.0;
	float Sr_euler;
	for(i=0;i<nre;i++){
		fscanf(fp4,"%f %f",&c,&d);
		if((int)c*100<nrrk){
			if(c<10){
				k=(int)(c*100);
				fseek(fp5,18*k,SEEK_SET);
				fscanf(fp5,"%f %f",&a,&b);
				f+=pow((b-d),2);
				}
			else if(c>=10 && c<100){
				fseek(fp5,1000*18,SEEK_SET);
				k=(int)(c*100)-1000;
				fseek(fp5,k*19,SEEK_CUR);
				fscanf(fp5,"%f %f",&a,&b);
				f+=pow((b-d),2);
				}
			else {
				fseek(fp5,0,SEEK_SET);
				for(j=1;j<=c*100;j++){
					fscanf(fp5,"%f %f",&a,&b);
					}
				f+=pow((b-d),2);
				}	
			}
		else{
			break;
			}
		}		
	Sr_euler=(float)f/nre;
	float R2_euler=1-Sr_euler/St;
	fseek(fp5,0,SEEK_SET);
	return(R2_euler);	
}
float r2_heun(int nrh,int nrrk,FILE* fp7,FILE* fp8,float St){            //calculates the goodness of fit for heun taking rk45 as standard
	int i,j,k;
	float a,b,c,d;
	float e=0.0;
	float f=0.0;
	float Sr_heun;
	for(i=0;i<nrh;i++){
		fscanf(fp7,"%f %f",&c,&d);
		if((int)c*100<nrrk){
			if(c<10){
				k=(int)(c*100);
				fseek(fp8,18*k,SEEK_SET);
				fscanf(fp8,"%f %f",&a,&b);
				f+=pow((b-d),2);
				}
			else if(c>=10 && c<100){
				fseek(fp8,1000*18,SEEK_SET);
				k=(int)(c*100)-1000;
				fseek(fp8,k*19,SEEK_CUR);
				fscanf(fp8,"%f %f",&a,&b);
				f+=pow((b-d),2);
				}
			else{
				fseek(fp8,0,SEEK_SET);
				for(j=1;j<=c*100;j++){
					fscanf(fp8,"%f %f",&a,&b);
					}
				f+=pow((b-d),2);
				}
			}
		else{
			break;
			}
		}		
	Sr_heun=(float)f/nrh;
	float R2_heun=1-Sr_heun/St;
	fseek(fp8,0,SEEK_SET);
	return(R2_heun);
}
float St_calc(int nrrk,FILE* fp10,float mean){                        //calculates the St values using the values derived from rk45 method
	int i;
	float a,b;
	float e=0.0;
	for(i=0;i<nrrk;i++){
		fscanf(fp10,"%f %f",&a,&b);
		e+=pow((b-mean),2);
	    }
	float St=(float)e/nrrk;
	return(St);
}	
