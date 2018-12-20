#include "grid/cartesian1D.h"
#include "run.h"

scalar U[];
scalar F[];
double dt;  
double dx;
double cDelta;
double CFL; //Courant Friedrich Lewy number, condition on the stability

U[left] = neumann(0);
U[right] = neumann(0);

int main() {
	  L0 = 12.;
	    X0 = -L0/4;
	      N = 128;
	      dx=L0/N;
              CFL=0.8;
	      DT = (dx)*CFL;
		  run();
}

event init (t = 0) {
	  foreach()
		      U[] = exp(-x*x);
	    boundary ({U});
	      }


event printdata (t += 1; t <=3) {
	  foreach()
		      fprintf (stdout, "%g %g %g  \n", x, U[], t);
	    fprintf (stdout, "\n\n");
}

event integration (i++) {
	  double dt = DT;
	    dt = dtnext (dt);
	     foreach() {
		        cDelta = Delta/dt;// Lax-Friedrich”
			//cDelta = 0;//Average flux
			//cDelta = 1;//upwind flux
			F[] = (U[0,0]+U[-1,0])/2.  - cDelta *(U[0,0]-U[-1,0])/2;}
			boundary ({F});
			 foreach()
				     U[] +=  - dt* ( F[1,0] - F[0,0] )/dx;
			   boundary ({U});
}
