#include "grid/cartesian1D.h"
#include "run.h"

scalar h[];
scalar Q[];
double dt;
double dx;

int main() {
  L0 = 10.;
  X0 = -L0/2;
  N = 128;
  DT = (L0/N)*(L0/N)/10 ;
  dx=L0/N;
  run();
}

event init (t = 0) {
  foreach(){
    h[] = (fabs(x)<1) ;
    Q[]=0;
    }
  boundary ({h,Q});
  }
event printdata (t += 10; t <= 500) {
  foreach()
    fprintf (stdout, "%g %g %g %g \n", x, h[], Q[], t);
  fprintf (stdout, "\n");
}
event integration (i++) {
  double dt = DT;
 dt = dtnext (dt);
 foreach_face()
    Q[] = 1./3 * (( h[0,0] - h[-1,0] )/dx) * pow((h[0,0] + h[-1,0])/2,3);
  boundary ({Q});
foreach(){
    h[] +=  dt*( Q[1,0] - Q[0,0] )/dx;
  }
  boundary ({h});  
}
