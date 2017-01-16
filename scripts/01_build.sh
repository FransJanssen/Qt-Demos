#!/bin/bash

SCRIPT=$(readlink -f $0)
SCRIPTPATH=`dirname $SCRIPT`
cd $SCRIPTPATH/../
PROJECTDIR=$(pwd)

export PROJECTDIR=$PROJECTDIR

rm -r -f ${PROJECTDIR}/build
mkdir -p ${PROJECTDIR}/build

cd ${PROJECTDIR}/build/
qmake ../Vfp.pro
make

