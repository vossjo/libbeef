# libbeef

libbeef is a package providing the class of BEEF-vdW functionals
and Bayesian error estimates to Fortran- or C-based DFT codes.


Basic installation instructions:
```bash
./configure CC=icc --prefix=yourbeefpath
make
make install
```

To link it to the DFT code, add the following to the linker flags:
-Lyourbeefpath/lib -lbeef


Error estimates can be calculated using the atomic simulation environment
(https://wiki.fysik.dtu.dk) or with the bee utility included in this
distribution:
```bash
yourbeefpath/bin/bee 1 H2/output.log -2 H/out.log
```
will e.g. calculate the Bayesian error estimate on the formation of H2
from 2H.
