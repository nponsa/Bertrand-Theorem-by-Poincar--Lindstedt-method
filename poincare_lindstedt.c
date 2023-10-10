#include <stdio.h>
#include <math.h>
#define PI 3.1415926535897932384626433832795

double xi(double t,double ddphi0, double dddphi0, double alfa2, double b,double w)
{
  double p;
  p=b*cos(w*t)+ddphi0*b*b*(3-cos(2*w*t))/(12*alfa2)-(alfa2*dddphi0-ddphi0*ddphi0)
  *b*b*b*cos(3*w*t)/(192*alfa2*alfa2);
  return p;
}

double radi(double t,double u0,double ddphi0, double dddphi0, double alfa2,
double b,double w)
{
  double j;
  j=1/(u0+xi(t,ddphi0,dddphi0,alfa2,b,w));
  return j;
}

int main()
{
  double x,y,r,theta=0;
  double b, dphi0,ddphi0, dddphi0, alfa2,beta22,w;
  double e,l,k,m,u0,imax,op;
  FILE*f;
  f=fopen("Newton4.txt","w");
  /*Parametre d'entrada*/
  u0=0.05;
  m=1;
  k=-10;
  b=0.005; //b=A
  /*Parametres de discretitzacio*/
  e=0.00001;
  imax=2; //Nombre de voltes
  
  /*Calculs*/
  l=sqrt(k*log(u0)/(m*u0*u0*u0*u0));
  dphi0= k/(m*l*l)*(-3*log(u0)+1)/(u0*u0*u0*u0);
  ddphi0=k/(m*l*l)*(12*log(u0)-7)/(u0*u0*u0*u0*u0);
  dddphi0= k/(m*l*l)*(-60*log(u0)+47)/(u0*u0*u0*u0*u0*u0);
  alfa2=1-dphi0;
  beta22= -(5*ddphi0*ddphi0+3*alfa2*dddphi0)*b*b/(24*alfa2);
  w=sqrt(alfa2+beta22);
  
  fprintf(f,"#t\t#r\t#theta\n");
  for(op=0;theta<=imax*2*PI;op=op+e){
    theta=op;
    r=radi(theta,u0,ddphi0,dddphi0,alfa2,b,w);
    x=r*cos(theta);
    y=r*sin(theta);
    fprintf(f,"%f\t%f\n",x,y);
  }
return 0;
}
