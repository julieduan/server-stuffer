FROM ubuntu:18.04

ARG Program
ARG Input
ARG Output
ARG Afl
ARG USER_ID
ARG GROUP_ID

# set a directory for the app
WORKDIR test

# copy all the files to the container
COPY $Program ./program
COPY $Input ./input
COPY $Output ./output
COPY $Afl ./afl-2.52b

# set up permissions
RUN addgroup --gid $GROUP_ID user
RUN adduser --disabled-password --gecos '' --uid $USER_ID --gid $GROUP_ID user
RUN touch entrance
USER user

# run the command
CMD ./afl-2.52b/afl-fuzz -i input -o output ./program -f entrance
