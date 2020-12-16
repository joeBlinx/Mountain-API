FROM ubuntu:20.04
ENV DEBIAN_FRONTEND noninteractive
RUN apt update -y && \
apt install g++-10 -y && \
update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-10 20 && \
apt install cmake -y && \
apt install git -y && \
apt install libvulkan-dev spirv-tools -y && \
apt install libx11-dev xorg-dev libglu1-mesa-dev -y