[![DOI](https://zenodo.org/badge/22809/wlandau/fbseqCUDA.svg)](https://zenodo.org/badge/latestdoi/22809/wlandau/fbseqCUDA)

# Purpose

The [`fbseqCUDA` package](https://github.com/wlandau/fbseqCUDA) is an internal backend of [`fbseq` package](https://github.com/wlandau/fbseq) that runs the Markov chain Monte Carlo (MCMC) procedure behind the scenes. It is implemented with [CUDA](http://www.nvidia.com/object/cuda_home_new.html) for acceleration with parallel computing. For installation, CUDA must be installed. To use [`fbseqCUDA` package](https://github.com/wlandau/fbseqCUDA) in an MCMC, [`fbseq` package](https://github.com/wlandau/fbseq) must be installed, and a CUDA-capable general-purpose graphics processing unit (GPU) must be installed on your machine. 

# System requirements

- The R version and R packages listed in the  "Depends", "Imports", and "Suggests" fields of the "package's [DESCRIPTION](https://github.com/wlandau/fbseqCUDA/blob/master/DESCRIPTION) file.
- A [CUDA](http://www.nvidia.com/object/cuda_home_new.html)-capable [NVIDIA graphics processing unit (GPU)](https://developer.nvidia.com/cuda-gpus) with compute capability 2.0 or greater.
- [CUDA](http://www.nvidia.com/object/cuda_home_new.html) version 6.0 or greater. More information about CUDA is available through [NVIDIA](http://www.nvidia.com/).
- Optional: the code uses double precision values for computation, so GPUs that natively support double precision will be much faster than ones that do not.

# Installation

## Option 1: install a stable release (recommended).

Navigate to a [list of stable releases](https://github.com/wlandau/fbseqCUDA/releases) on the project's [GitHub page](https://github.com/wlandau/fbseqCUDA). Download the desired `tar.gz` bundle, then install it either with `install.packages(..., repos = NULL, type="source")` from within R  `R CMD INSTALL` from the Unix/Linux command line.

## Option 2: use `install_github` to install the development version.

For this option, you need the `devtools` package, available from CRAN or GitHub. Open R and run 

```
library(devtools)
install_github("wlandau/fbseqCUDA")
```

## Option 3: build the development version from the source.

Open a command line program such as Terminal in Mac/Linux and enter the following commands.

```
git clone git@github.com:wlandau/fbseqCUDA.git
R CMD build fbseqCUDA
R CMD INSTALL ...
```

where `...` is replaced by the name of the tarball produced by `R CMD build`. 

## Troubleshooting

If CUDA is not found, open  `fbseqCUDA/src/Makevars` in a text editor. The top line reads

```
CUDA_HOME = /usr/local/cuda
```

but this may not be correct for your system. Replace `/usr/local/cuda` with the correct path to the installation of CUDA on your computer.