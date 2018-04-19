#!/bin/csh
## Change into the current working directory
#$ -cwd
#$ -r n
##
## Queue Name
#$ -q general@@gen64
###$ -q serial
##
## Number of cores to request
#$ -pe mpi 16
###$ -pe serial 1
##
## Combining output/error messages into one file
#$ -j y

## Load Modules
module load gnu/6.1.0 openmpi/1.10.2_gnu6.1 anaconda/2.7

#set fname = "msri_cat_s1_${i}"
#set fpath = "micro/msri_cat/russiandoll/s1"

set fname = ${fileNameBase}
set fpath = ${filePath}

## Convert to ExodusII
#./ermine-opt -i inputs/dummy.i \
#Mesh/file=meshes/${fpath}/${fname}.inp \
#Outputs/exodus=true \
#Outputs/file_base=outputs/${fpath}/${fname} \
#--mesh-only \
#meshes/${fpath}/parmesh/${fname}.e

## Run Mesh Splitter
~/myprojects/moose/libmesh/installed/bin/splitter-opt \
--mesh=meshes/${fpath}/parmesh/${fname}.e \
--n-procs=256
