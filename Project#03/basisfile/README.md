# BasisFile

The main function of this subproject is to convert the text-structured basis file into the corresponding data structures defined in the program. By reading the parameters in the class, the basis set can then be generated based on the information about the molecule system (types and coordinates of atoms).

This subproject is part of `nhfint`. The reason for separating the work of parsing a basis file, instead of generating the base group directly from the molecular information and the base group file, is two-fold:
* Separate the two jobs to reduce the difficulty of programming.
* Considering different molecular integral algorithms require different information of basis sets, it will be more convenient for different molecular integral algorithms to call the required parameters from the data structures than from the text-structured basis file.

## Download Basis Files
We can download basis file from [Basis Set Exchange](https://www.basissetexchange.org/), remembering to select the **Gaussian format** when downloading.