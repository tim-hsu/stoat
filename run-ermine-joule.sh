#!/bin/csh
## Change into the current working directory
#$ -cwd
#$ -r n
##
## Queue Name
#$ -q general
###$ -q general@@gen64
##
## Number of cores to request
#$ -pe mpi 256
##
## Combining output/error messages into one file
#$ -j y

## Load modules for MOOSE
module load gnu/6.1.0 openmpi/1.10.2_gnu6.1 anaconda/2.7

#set fname = "msri-cat-7p5um-fine-tuned1"
#set fpath = "micro/msri_cat/7p5um/fine-tuned"
set fname = ${fileNameBase}
set fpath = ${filePath}

## Run ERMINE 
#mpirun ermine-opt -i inputs/micro_cat.i \
#Mesh/file=meshes/${fpath}/${fname}.inp \
#GlobalParams/s0=8138.3 \
#Outputs/file_base=outputs/${fpath}/${fname} \
#Outputs/exodus=true


## RUN ERMINE (Distributed Mesh)
mpirun ermine-opt -i inputs/micro_cat.i \
Mesh/file=meshes/${fpath}/parmesh/${fname}.256.cpr \
Mesh/parallel_type=DISTRIBUTED \
Outputs/file_base=outputs/${fpath}/nltol-1e-4/${fname} \
Outputs/exodus=true \
GlobalParams/s0=3472.6 \
Executioner/nl_rel_tol=1e-4 \
Executioner/l_tol=1e-2
