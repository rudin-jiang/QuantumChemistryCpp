# BasisFile

The main function of this subproject is to parse a basis file and resolve the basis information of each atom in the basis file into the class defined in the program. The basis set is then generated based on the information about the molecule system (types and coordinates of atoms in the system).

This subproject is part of `nhfint`. The reason for separating the work of parsing a basis file, instead of generating the base group directly from the molecular information and the base group file, is mainly due to two considerations:

* Separate the two jobs to reduce the difficulty of programming.
* Different molecular integrals require different basis sets of information, and it is easier to generate different basis sets with the information in the basis set file of these read-in programs.

## Download Basis Files
We can download basis file from [Basis Set Exchange](https://www.basissetexchange.org/), remembering to select the **Gaussian format** when downloading.