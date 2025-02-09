# Point Parser System

This project is a system for parsing and visualizing points from files in different formats (text, binary, JSON). It consists of a C++ program, a Python script, and a Bash script. The system is designed to work on **Ubuntu 22.04** .

---

## Overview

The Point Parser System processes multiple input files containing point data in different formats and generates a scatter plot using the `matplotlib` library in Python. The parsed data is combined into a single JSON object, which is then passed to the Python script for visualization.

---

## Requirements

Before running the application, ensure that your environment meets the following requirements:
- **Operating System**: Ubuntu 22.04.
- **Compiler**: GCC version 11 or higher.
- **C++ Standard**: C++11 (or higher).
- **Python Version**: Python 3.10 or higher.
- **CMake Version**: CMake 3.16 or higher.

All additional dependencies (such as `nlohmann/json` for C++ and `matplotlib` for Python) will be installed automatically during the build process.

---

## Getting Started

### Step 1: Clone the Repository

To get started, clone the repository to your local machine:

```bash
https://github.com/TodayMueller/Point_Parser.git
cd Point_Parser
```

---

### Step 2: Set Execution Permissions for `build.sh`

Ensure that the `build.sh` script has execution permissions:

```bash
chmod +x build.sh
```

If you encounter any permission issues, repeat this step for all `.sh` scripts in the project:

```bash
find . -name "*.sh" -exec chmod +x {} \;
```

---

### Step 3: Build the Project

Run the `build.sh` script to build the project. This script will:
- Check and install all required system dependencies.
- Install Python dependencies in a virtual environment.
- Compile the C++ program using CMake.

```bash
./build.sh
```

This process may require `sudo` privileges for installing system packages.

---

### Step 4: Run the Application

After successful compilation, run the application using the provided `run.sh` script:

#### Using Example Input Files
To use the example input files provided in the `input_example/` directory:

```bash
./install/bin/run.sh input_example/*
```

#### Using Custom Input Files
You can also provide your own input files:

```bash
./install/bin/run.sh file1.txt file2.bin file3.json
```

---

## Usage

### Input File Formats

#### Text File (`*.txt`)
Each line contains a point in the format `<group>:<x>,<y>`:
```
t1:1,2
t2:3,4
```

#### Binary File (`*.bin`)
Each 32-bit block represents one point with the following structure:
- `group`: 8 bits
- `x`: 12 bits
- `y`: 12 bits

For example:
- Group `0`, `x=250`, `y=200` → Binary representation: `0x00FA00C8`.

#### JSON File (`*.json`)
Points are stored in an array under the `"points"` key:
```json
{
    "points": [
        {"group": "g1", "x": 100, "y": 200},
        {"group": "g1", "x": 150, "y": 250}
    ]
}
```

---

### Output Directory

The generated graph will be saved in the `output/` directory as `output.png`.

```
output/
└── output.png
```

---

