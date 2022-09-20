This is the repository for the version of Chaste I used to generate the results for the following papers during my PhD:

  - Claire Miller, Edmund Crampin, James M. Osborne (2021). Maintaining the proliferative cell niche in multicellular models of epithelia, Journal of Theoretical Biology, Volume 527, 110807. https://doi.org/10.1016/j.jtbi.2021.110807.
  - Miller C, Crampin E, Osborne JM (2022) Multiscale modelling of desquamation in the interfollicular epidermis. PLoS Comput Biol 18(8): e1010368. https://doi.org/10.1371/journal.pcbi.1010368
  
This is to ensure reproducibility in case of a loss of backwards compatability with the core Chaste code base. Below is the standard usage information from the Chaste github readme. 

# Welcome to Chaste 

If you are new to Chaste please see [our Getting Started wiki page](https://chaste.cs.ox.ac.uk/trac/wiki/GettingStarted).

The files you have downloaded contain the source code for all Chaste functionality. 
Chaste makes use of a variety of external libraries and packages that need to be installed on your machine. 
The [Install Guide wiki page](https://chaste.cs.ox.ac.uk/trac/wiki/InstallGuides/InstallGuide) 
provides a comprehensive guide on how to install these external tools.

Chaste is distributed as open source software under the [3-clause BSD licence](https://opensource.org/licenses/BSD-3-Clause). 
For full details see the file [Copying.pdf](docs/Copying.pdf).
Chaste uses various third party libraries which have their own licences. 
For details of these licences and the impact they may have on your use of 
Chaste please see [Licences.html](docs/Licences.html).

Chaste includes a complete test suite covering all the source code. 
The easiest way to use existing source codes is to create a test file 
which can call upon any of the source files.  
The Chaste build system can build this file for you and handle 
all of the dependencies and library calls.

We suggest you use the projects directory in this manner to store your own 
source and test files if you do not wish to modify the Chaste source code. 
For more information, see the [User Projects wiki page](https://chaste.cs.ox.ac.uk/trac/wiki/ChasteGuides/UserProjects).

For more information please refer to the Chaste website at: http://www.cs.ox.ac.uk/chaste/

Information on changes in this release can be found in the file
[ReleaseNotes.html](docs/ReleaseNotes.html).

Tutorial examples for this release are available at:
https://chaste.cs.ox.ac.uk/chaste/tutorials/release_2017.1

API documentation generated from the code by Doxygen is available at:
https://chaste.cs.ox.ac.uk/chaste/docs/release_2017.1
