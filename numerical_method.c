#include <stdio.h>
#include <math.h>
int sign(double y)
{
  if(y>= 0.0) return 1;
  if(y<0) return -1;
  return 0;
}

int main()
{
  double x,y,r,px,py,fx,fy,fr,theta;
  double b, dphi0,ddphi0, dddphi0, alfa2,c;
  double e,l,k,m,t,u0,tmax,j;

  int voltes=0;
  
  FILE*f;
  f=fopen("Newton.txt","w");
  /*Parametre dentrada*/
  u0=0.05;
  m=1;
  k=-10;
  px=0;
  b=0.005;
  /*Parametres de discretitzacio*/
  e=0.00001;
  tmax=4; //nombre de mitges voltes
  /*Calculs*/
  l=sqrt(k*log(u0)/(m*u0*u0*u0*u0));
  dphi0= k/(m*l*l)*(-3*log(u0)+1)/(u0*u0*u0*u0);
  ddphi0=k/(m*l*l)*(12*log(u0)-7)/(u0*u0*u0*u0*u0);
  dddphi0= k/(m*l*l)*(-60*log(u0)+47)/(u0*u0*u0*u0*u0*u0);
  alfa2=1-dphi0;
  c= b+ddphi0*b*b*2/(12*alfa2)-(alfa2*dddphi0-ddphi0*ddphi0)
  *b*b*b/(192*alfa2*alfa2);
  x=1/(u0+c);
  y=0;
  py=(l*m+px*y)/x;
  fprintf(f,"#t\t#x\t#y\t#px\t#py\n");
  for(t=0;voltes<tmax||r>100/u0;t=t+e){
    j=y;
    r=sqrt(x*x+y*y);
    theta=atan2(y,x);
    fr=k*r*log(r);
    fx=fr*(cos(theta));
    fy=fr*(sin(theta));
    x=x+(e*px)/m;
    y=y+(e*py)/m;
    px=px+e*fx;
    py=py+e*fy;
    fprintf(f,"%f\t%f\t%f\t%f\t%f\n",t,x,y,r,theta);
    if(sign(y)!=sign(j)) voltes=voltes+1;
  }
  return 0;
}
