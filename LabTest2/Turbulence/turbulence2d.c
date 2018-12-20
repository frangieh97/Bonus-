#include "grid/multigrid.h"
#include "navier-stokes/stream.h"

//The domain is square of size unity by default. The resolution is constant at 256^2
int main() {
  init_grid (64);
  run();
}

//The initial condition for vorticity is just a white noise in the range [−1:1]
event init (i = 0) {
  foreach()
    omega[] = noise();
}
//We generate images of the vorticity field every 8 timesteps up to t=1000. We fix the colorscale to [−0.3:0.3]
event output (i += 8; t <= 1000) {
  static FILE * fp = fopen ("omega.ppm", "w");
  output_ppm (omega, fp, min = -0.3, max = 0.3);
}
