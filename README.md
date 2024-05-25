# What is this?

SOGE (Study Only Game Engine) is the game engine making for study purposes with DirectX11 in ITMO university.

# Create build

First of first, run *git submodule update --init --recursive* to initialize all submodule dependencies. 

**Currently I'm using builded DirectXTK lib files located in SOGEEngine/3rdparty/DirectXTK/lib.rar so you need to unpack it manually in the root of DirectXTK directory**

Then, to create build of the engine you need to run **generateProject.bat** located in the root of the project, MSVS project will be created.
