#!/bin/bash

BUILD_DIR="build"
INSTALL_DIR="install"
VENV_DIR="env"

rm -rf $BUILD_DIR $INSTALL_DIR $VENV_DIR

mkdir -p $BUILD_DIR
cd $BUILD_DIR || exit

install_system_dependencies() {
    echo "Installing system dependencies..."

    if [[ "$(uname)" == "Linux" ]]; then
        sudo apt update
        sudo apt install -y build-essential cmake g++ make \
            python3-pip git curl wget
    elif [[ "$(uname)" == "Darwin" ]]; then
        brew install cmake gcc python@3.10
    else
        echo "Error: Unsupported operating system."
        exit 1
    fi
}

check_system_dependencies() {
    local missing=0

    for cmd in cmake g++ make python3 pip3; do
        if ! command -v $cmd &>/dev/null; then
            echo "Warning: $cmd is not installed."
            missing=1
        fi
    done

    if [ $missing -eq 1 ]; then
        read -p "Do you want to install missing system dependencies? [y/n]: " choice
        if [[ "$choice" == "y" || "$choice" == "Y" ]]; then
            install_system_dependencies
        else
            echo "Please install the required dependencies manually and rerun the script."
            exit 1
        fi
    fi
}

check_system_dependencies

install_python_3_10() {
    PY_VERSION="3.10.0"

    if ! command -v pyenv &>/dev/null; then
        echo "Installing pyenv..."
        curl https://pyenv.run | bash
        export PYENV_ROOT="$HOME/.pyenv"
        export PATH="$PYENV_ROOT/bin:$PATH"
        eval "$(pyenv init --path)"
        eval "$(pyenv virtualenv-init -)"
    fi

    if ! pyenv versions | grep -q "$PY_VERSION"; then
        echo "Installing Python $PY_VERSION..."
        pyenv install $PY_VERSION
        pyenv global $PY_VERSION
    fi

    PYTHON_CMD=$(pyenv which python)
    echo "Using Python: $PYTHON_CMD"
}

install_python_3_10

if [ ! -d "../$VENV_DIR" ]; then
    echo "Creating virtual environment..."
    if ! $PYTHON_CMD -m venv ../$VENV_DIR; then
        echo "Error: Failed to create virtual environment."
        exit 1
    fi
fi

source ../$VENV_DIR/bin/activate

if ! command -v pip &>/dev/null; then
    echo "Installing pip inside the virtual environment..."
    curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
    python get-pip.py
    rm get-pip.py
fi

echo "Installing Python dependencies..."
pip install -r ../requirements.txt

cmake .. -DCMAKE_INSTALL_PREFIX=$(realpath ../$INSTALL_DIR)

make

if [ $? -ne 0 ]; then
    echo "Error: Build failed."
    exit 1
fi

make install

find ../$INSTALL_DIR -type f \( -name "*.sh" -o -perm /u=x \) -exec chmod +x {} \;

echo "Build completed successfully. Files installed to $(realpath ../$INSTALL_DIR)."
