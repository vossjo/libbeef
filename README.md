# libbeef

libbeef is a package providing the class of BEEF-vdW functionals
and Bayesian error estimates to Fortran- or C-based DFT codes.


Basic installation instructions:
```bash
./configure CC=icc --prefix=yourbeefpath
make
make install
```
You can add <tt>--enable-optmax</tt> to the configure flags, but this may break the code if it is run on older or different CPUs than the library was compiled on.

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

# DFT codes with interfaces to <tt>libbeef</tt>
- All recent versions of [VASP](https://www.vasp.at/) (V5.4.x and up) have interfaces to <tt>libbeef.</tt> Add <tt>-Dlibbeef</tt> to the preprocessor flags and <tt>-Lyourbeefpath/lib -lbeef</tt> to the linker library flags to enable <tt>libbeef.</tt> Instructions on where to define these variables for V6.x.x can be found at this [link](https://www.vasp.at/wiki/index.php/Makefile.include#Libbeef_.28optional.29).
- <tt>libbeef</tt> is automatically enabled in [Quantum ESPRESSO](https://www.quantum-espresso.org/) version 6.6. or higher (use `input_dft = 'BEEF-vdW'`). For usage of <tt>libbeef</tt> with earlier versions: QE 5.x source code [here](https://github.com/vossjo/ase-espresso/wiki#installation) and QE 6.x source code [here](https://github.com/vossjo/q-e).
