FROM ubuntu:20.04
ENV DEBIAN_FRONTEND noninteractive
RUN apt update -y && \
apt install g++-10 -y  gcc-10&& \
update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-10 20 && \
update-alternatives --install /usr/bin/cc cc /usr/bin/gcc-10 20 && \
apt install cmake -y && \
apt install git -y && \
apt install libvulkan-dev spirv-tools -y && \
apt install libx11-dev xorg-dev libglu1-mesa-dev -y &&\
apt install glslang-tools -y
RUN apt install -y rsync gdb
RUN apt install -y python3-pip && \
python3 -m pip install ninja &&\
python3 -m pip install conan
RUN apt install -y openssh-server ssh
RUN apt clean
RUN useradd -m user && yes password | passwd user

EXPOSE 22
ENTRYPOINT service ssh restart && bash