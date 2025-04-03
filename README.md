# rdkit-cpp-utils

## Description
rdkit is the goto toolkit for anything related to cheminformatics and data science applications in Chemistry. It is mostly used in python which shouldn't be uderestimated performance-wise. Still for large amounts of data getting some help from C++ which is the native language of rdkit makes sense. Some good sources to start are: https://www.rdkit.org/docs/GettingStartedInC%2B%2B.html and https://github.com/iwatobipen/rdkit_cpp/tree/main. The aim of this repo is to collect some standard functionality in C++ when increased efficiency is required.

## Installation
This is the hard and less fun part. This is what worked for me:
1. Compile **rdkit** from source following https://greglandrum.github.io/rdkit-blog/posts/2023-03-17-setting-up-a-cxx-dev-env2.html One can also look at https://github.com/rdkit/rdkit/tree/master/.azure-pipelines. After a successful set-up you should have a conda environment and all the environmental variables set as described in the links.
2. Clone the repository, and activate the conda environment that was created in Step 1
   ```
   git clone https://github.com/Arhs99/rdkit-cpp-utils.git
   cd rdkit-cpp-utils
   conda activate py310_rdkit_build
   ```
4. Environmental variables: At least ```RDBASE``` and ```LD_LIBRARY_PATH``` should be set, if not:
```
export LD_LIBRARY_PATH=${RDBASE}/lib:${CONDA_PREFIX}/lib:${LD_LIBRARY_PATH}
```
5. Create a ```build``` directory and run to compile and link:
```
cmake ..
make
```
This should create the executable ```morganfp```

## Usage
One can use either ```morganfp``` or ```fingerprint.py``` to calculate Morgan fingerprints from an sdf file and store them as numpy array files ```*.npy```. Additional arguments are the fingerprint radius and the number of bits
### C++ example
Run as: 
```
./morganfp ../data/ChEMBL_set.sdf  ../data/arr_cpp.npy 3 2048
```

### python example
```
python fingerprints.py data/ChEMBL_set.sdf  data/arr_py.npy 3 2048
```
## Acknowledgment
The files ```cnpy.cpp``` and ```cnpy.h``` used for loading/saving C++ data as numpy ```.npy``` files were copied from the **cnpy** library https://github.com/rogersce/cnpy
