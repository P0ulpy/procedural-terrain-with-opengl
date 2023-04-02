# Procedural terrain with opengl

//

## Setting up Git dependencies

```bash
git submodule update --init --recursive
```

__Bootstrap vcpkg :__

_Windows_
```bash
.\vcpkg\bootstrap-vcpkg.bat
```

_Unix_
```bash
.\vcpkg\bootstrap-vcpkg.sh
```

## Installing dependencies

Install dependencies :

_Windows_
```bash
.\vcpkg\vcpkg.exe install --triplet x64-windows
```

_Linux_
```bash
./vcpkg/vcpkg install --triplet x64-linux
```
