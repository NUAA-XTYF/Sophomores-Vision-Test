FROM osrf/ros:humble-desktop

ENV DEBIAN_FRONTEND=noninteractive

# Install core dependencies
RUN apt-get update && apt-get install -y \
    git \
    build-essential \
    cmake \
    can-utils \
    libopencv-dev \
    libfmt-dev \
    libeigen3-dev \
    libspdlog-dev \
    libyaml-cpp-dev \
    libusb-1.0-0-dev \
    nlohmann-json3-dev \
    openssh-server \
    screen \
    googletest \
    libceres-dev \
    curl \
    unzip \
    lsb-release \
    python3-pip \
    ros-humble-plotjuggler-ros \
    wget \
    nano \
    sudo \
    && rm -rf /var/lib/apt/lists/*

# Install OpenVINO 2024.6.0
# Using exact version from script logic for Ubuntu 22.04
RUN mkdir -p /tmp/openvino && cd /tmp/openvino \
    && curl -L "https://storage.openvinotoolkit.org/repositories/openvino/packages/2024.6/linux/l_openvino_toolkit_ubuntu22_2024.6.0.17404.4c0f47d2335_x86_64.tgz" --output openvino.tgz \
    && tar -xf openvino.tgz \
    && mkdir -p /opt/intel \
    && mv l_openvino_toolkit_ubuntu22_2024.6.0.17404.4c0f47d2335_x86_64 /opt/intel/openvino_2024.6.0 \
    && ln -s /opt/intel/openvino_2024.6.0 /opt/intel/openvino_2024 \
    && cd /opt/intel/openvino_2024/install_dependencies \
    && ./install_openvino_dependencies.sh -y \
    && pip3 install -r ../python/requirements.txt \
    && rm -rf /tmp/openvino

# Install Hikrobot MVS SDK (Optional)
# Using direct link from script
ARG INSTALL_MVS=false
RUN if [ "$INSTALL_MVS" = "true" ]; then \
    mkdir -p /tmp/mvs && cd /tmp/mvs \
    && curl -fSL "https://www.hikrobotics.com/cn2/source/support/software/MvCamCtrlSDK_STD_V4.7.0_251113.zip" -o sdk.zip \
    && unzip sdk.zip -d extracted \
    && cd extracted/MvCamCtrlSDK_STD \
    && dpkg -i MvCamCtrlSDK_Runtime-4.7.0_x86_64_20251113.deb || apt-get install -f -y \
    && rm -rf /tmp/mvs; \
    fi

# Set up user
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Create the user
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME \
    && usermod -aG dialout,video $USERNAME

# Setup environment
USER $USERNAME
WORKDIR /home/$USERNAME

# Add sources to bashrc
RUN echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc \
    && echo "source /opt/intel/openvino_2024/setupvars.sh" >> ~/.bashrc

CMD ["/bin/bash"]
