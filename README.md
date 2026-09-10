# Workshop 1: CMake Environment Setup

**Author:** [Change this to your name]

This workshop will guide you through setting up a modern C++ development environment using CMake and FetchContent to manage external dependencies natively. By the end of this session, you will have a simple GUI C++ program running SFML and Dear ImGui to render stuff on the screen.

### Technical Objectives Checklist
Before submitting your completion status, ensure you have checked off all operational stages below:

Install native compiler and low-level system development packages

- [ ] Install CMake on your host platform
- [ ] Clone the bootcamp repository and check out the `w1` branch
- [ ] Successfully generate the build tree and compile the project from source
- [ ]  Modify the application source code to display your personal diagnostic card
- [ ] Verify that your local repository ignores temporary build directory tracking

## 1. Pre-requisites & System Dependency Installation
Follow the instructions below for your respective operating system.

### Linux (Ubuntu / Debian Only)
Open a terminal and execute the following commands to update your package registries and install the standard development toolchain alongside the required windowing, graphics, and audio system libraries:

```BASH
sudo apt update

sudo apt install build-essential cmake libgl1-mesa-dev libglu1-mesa-dev libopenal-dev libxrandr-dev libxcursor-dev libudev-dev libfreetype-dev libflac-dev libvorbis-dev
```

### Windows
1. Download and run the official [Visual Studio 2026](https://visualstudio.microsoft.com/downloads/) Installer.
2. Select the Desktop development with C++ workload. Ensure that the MSVC v143 build tools and the latest Windows 11 SDK (or Windows 10 SDK) are checked in the installation details panel.
3. Download the official [CMake Installer](https://cmake.org/download/) for Windows. Run the executable and ensure you select the option to "Add CMake to the system PATH for all users" during the setup wizard.
Ensure your GPU drivers (NVIDIA, AMD, or Intel) are updated to their latest stable releases to enable full OpenGL runtime context execution.


## 2. Project Retrieval & Branch Configuration
Clone this repo if you do not have it already.
Open your terminal or Git Bash and clone your personal fork repository locally:
```BASH
git clone https://github.com/your-username/cpp-bootcamp

cd cpp-bootcamp
```
Check out the dedicated branch where the Workshop 1 project scaffold is isolated:

```BASH
git checkout w1
```

## 3. Configuration & Compilation Pipeline
The GIT_REPOSITORY parameters inside the root CMakeLists.txt file have been intentionally redacted with placeholders. 

1. Open CMakeLists.txt in your text editor.
2. Locate the FetchContent_Declare blocks for SFML, imgui, and ImGui-SFML.
3. Search GitHub to find the official repository cloning URLs for these frameworks, replace the text placeholders, and save your changes.
4. Generate the localized build tree and build the project structure by executing the following standard commands in your root terminal window:

```BASH
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Linux
cmake --build build

#Windows
cmake --build build --config Release
```

## 4. Coding Assignment: Personal Diagnostic Display
Once your compilation pipeline successfully runs the default blueprint window, personalize the application layer to verify that state modification functions correctly.
1. Open src/main.cpp.
2. Locate the section where the ImGui text layout parameters are constructed.
3. Modify the rendering buffer strings to display your personal information matching the format specification pattern below:

```
Name: [Your Full Name Here]
OS:   [Windows 11 / Ubuntu 22.04 LTS / etc.]
Favorite Game: [Dark Souls III]
```

4. Save your modifications, re-run cmake --build build in your terminal to incrementally compile your changes, and execute the final binary to verify the visual layout:

`Linux: ./build/BootcampWorkshop1`

`Windows: .\build\Release\BootcampWorkshop1.exe`

5. Commit and push your changes.