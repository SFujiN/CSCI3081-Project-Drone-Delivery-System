#!/bin/bash

PORT=$1

if [ -z "$1" ]
then
    PORT=8081
fi

ROOTDIR=`git rev-parse --show-toplevel`
CONTAINER=csci3081f20-env-container

docker rm ${CONTAINER}
docker run --name=${CONTAINER} -p 127.0.0.1:$PORT:$PORT -v "${ROOTDIR}:/home/user/repo" -e project_port=$PORT -e USE_REPO_DIR=1 -it csci3081f20/env
