FROM ubuntu:20.04
ENV DEBIAN_FRONTEND noninteractive
RUN apt update && apt install -y wget gnupg
RUN wget -qO - https://packages.lunarg.com/lunarg-signing-key-pub.asc | apt-key add - &&\
    wget -qO /etc/apt/sources.list.d/lunarg-vulkan-1.2.162-focal.list https://packages.lunarg.com/vulkan/1.2.162/lunarg-vulkan-1.2.162-focal.list &&\
    apt update -y && \
apt install g++-10 -y  gcc-10&& \
update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-10 20 && \
update-alternatives --install /usr/bin/cc cc /usr/bin/gcc-10 20 && \
apt install cmake -y && \
apt install git -y && \
apt install spirv-tools -y && \
apt install libx11-dev xorg-dev libglu1-mesa-dev -y &&\
apt install glslang-tools -y &&\
apt install -y vulkan-sdk
RUN apt-get install -y --no-install-recommends libx11-xcb-dev libxcb-dri3-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-render-util0-dev libxcb-render0-dev libxcb-shape0-dev libxcb-sync-dev libxcb-util-dev libxcb-xfixes0-dev libxcb-xinerama0-dev libxcb-xkb-dev
#the line above is for glfw
RUN apt install -y rsync gdb
RUN apt install -y python3-pip && \
python3 -m pip install ninja &&\
python3 -m pip install conan &&\
python3 -m pip install sphinx_rtd_theme &&\
python3 -m pip install breathe &&\
python3 -m pip install Sphinx &&\
python3 -m pip install recommonmark
RUN apt install -y openssh-server ssh doxygen
RUN apt update && \
    apt install -y software-properties-common &&\
    apt-key adv --keyserver keyserver.ubuntu.com --recv-key C99B11DEB97541F0 &&\
    apt-add-repository https://cli.github.com/packages &&\
    apt install -y gh
RUN apt clean
RUN useradd -m user && yes password | passwd user

EXPOSE 22
ENTRYPOINT service ssh restart && bash