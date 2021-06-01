# Get the GCC preinstalled image from Docker Hub
FROM ubuntu:bionic

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY . /usr/src/app

# Specify the working directory
WORKDIR /usr/src/app

# Use GCC to compile the Test.cpp source file
RUN apt-get update -y
RUN apt-get install build-essential manpages-dev gnuplot -y

RUN make clean
RUN make

RUN chmod +x ./build/application

# Run the program output from the previous step
CMD ["./build/application"]