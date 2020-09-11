FROM  csci3081f20/base as env

RUN groupdel dialout

RUN apt-get update && apt-get install -y \
    build-essential \
    gdb \
    libssl-dev \
    zlib1g-dev \
    dos2unix \
    rsync \
    doxygen

ENV project_port 8081
ENV USE_REPO_DIR 1

ARG USER_ID
ARG GROUP_ID

RUN addgroup --gid $GROUP_ID user
RUN adduser --disabled-password --gecos '' --uid $USER_ID --gid $GROUP_ID user

RUN mkdir -p /home/user
WORKDIR /home/user/repo

USER user
