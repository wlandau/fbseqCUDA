# fbseqCUDA

`fbseqCUDA` is the internal engine of the [`fbseq` package](https://github.com/wlandau/fbseq), and it is implemented in [CUDA](http://www.nvidia.com/object/cuda_home_new.html) to provide necessary acceleration for the underlying Markov chain Monte Carlo (MCMC) procedure. `fbseq` and `fbseqCUDA` are kept separate for convenience. A user may use `fbseq` on a personal laptop, for example, to set up a workflow and analyze results. `fbseqCUDA` is only necessary to actually run the Markov chain Monte Carlo (MCMC) procedure, which can be done remotely with a CUDA-enabled node on a shared cluster or a [cloud computing enterprise](http://www.nvidia.com/object/gpu-cloud-computing-services.html). `fbseqCUDA` is not meant to be directly accessed by the user, so there are no usage instructions. However, the following system requirements and installation instructions are important.

# System requirements

- R $\ge$ 3.2.0
- R packages `methods` and `knitr`, available through the [Comprehensive R Archive Network (CRAN](https://cran.r-project.org/).
- R [package `fbseq`](https://github.com/wlandau/fbseq), available through GitHub. (See the [`fbseq` package tutorial vignette](https://github.com/wlandau/fbseq/blob/master/vignettes/model.html) for installation instructions. For best viewing, download the html vignette to your desktop and open it with a browser).
- A [CUDA](http://www.nvidia.com/object/cuda_home_new.html)-capable [NVIDIA graphics processing unit (GPU)](https://developer.nvidia.com/cuda-gpus) with compute capability 2.0 or greater.
- [CUDA](http://www.nvidia.com/object/cuda_home_new.html) version 6.0 or greater.
- Optional: the code uses double precision values for computation, so GPUs that natively support double precision will be much faster than ones that do not.

More information about CUDA is available through [NVIDIA](http://www.nvidia.com/). If your computer does not have these features, you can rent GPU time from [cloud computing enterprises](http://www.nvidia.com/object/gpu-cloud-computing-services.html) such as [Amazon Web Services](http://aws.amazon.com/ec2/instance-types/). 

# Installation

## Option 1: install a stable release (recommended).

Navigate to a [list of stable releases](https://github.com/wlandau/fbseqCUDA/releases) on the project's [GitHub page](https://github.com/wlandau/fbseqCUDA). Download the desired `tar.gz` bundle, then install it either with `install.packages(..., repos = NULL, type="source")` from within R  `R CMD INSTALL` from the Unix/Linux command line.

## Option 2: use `install_github` to install the development version.

For this option, you need the `devtools` package, available from CRAN or GitHub. Open R and run 

```{r, eval=F}
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

but this may not be correct for your system. Replace `/usr/local/cuda` to the installation of CUDA on your computer.