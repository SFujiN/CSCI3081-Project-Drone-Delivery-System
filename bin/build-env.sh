#!/bin/bash

docker pull csci3081f20/base

CONTAINER=csci3081f20-env-container
ROOTDIR=`git rev-parse --show-toplevel`
docker build $1 \
	--target env \
	--build-arg USER_ID=$(id -u) \
	--build-arg GROUP_ID=$(id -g) \
	-t csci3081f20/env "$ROOTDIR"
mkdir -p .dependencies
docker rm ${CONTAINER}
docker run --name=${CONTAINER} -v "${ROOTDIR}:/home/user/repo" csci3081f20/env cp -r ../../../project/grades/Fall-2020/csci3081/dependencies/include .dependencies

