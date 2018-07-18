#!/bin/bash

numMPI=12

mpiexec --n $numMPI ./stoat-opt -i inputs/micro_cat.i \
	Mesh/file=../../mesh-files/micro/msri-cat-5um-1.inp \
	GlobalParams/s0=8138.3 \
	Executioner/nl_rel_tol=1e-5 \
	Executioner/l_tol=1e-3 \
	Outputs/exodus=true \
	Outputs/file_base=outputs/micro/msri-cat-5um-1

