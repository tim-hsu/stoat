#!/bin/bash
fileNamePattern="msri-largescale*"
filePath="proj/large"

#################### Loop through Multiple Domains ####################
for i in meshes/$filePath/$fileNamePattern*.inp
do	
	fileName=${i##*/}
	fileNameBase=${fileName%.inp}
	filePath=${i#meshes/}
	filePath=${filePath%/*}
	echo "------------------------------------------------------"	
	echo "File String: $i"
	echo "File Name:   $fileNameBase"
	echo "File Path:   $filePath"
	if [ ! -f $i ]; then
		echo "ERROR! FILE DOES NOT EXIST!"
		break
	fi	
	
	## Split Meshes
	#qsub \
	#-v fileNameBase=$fileNameBase,filePath=$filePath \
	#-N split-$fileNameBase \
	#-o job_logs/proj/large/\$JOB_NAME.log \
	#split_mesh.sh
	
	## Run ERMINE
	qsub \
	-v fileNameBase=$fileNameBase,filePath=$filePath \
	-N ermine-$fileNameBase \
	-o job_logs/proj/large/nltol-1e-4/\$JOB_NAME.log \
	run_ermine.sh
done

############################ No Loop ################################
## Split Meshes
#qsub \
#-N split-syn060-set1-doll50um-1536c \
#-o job_logs/\$JOB_NAME \
#split_mesh.sh

## Run ERMINE
#qsub \
#-N parmesh-syn060-set1-doll50um-relax-tol \
#-o job_logs/\$JOB_NAME \
#run_ermine.sh
