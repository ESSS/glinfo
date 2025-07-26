glinfo
======

> [!IMPORTANT]
> This repository is no longer maintained, replaced by [ESSS/glinfo-rs](https://github.com/ESSS/glinfo-rs)

`glinfo` is a small utility to assess the OpenGL capabilities of the current environment. When called without parameters, the command will create a hidden OpenGL context using Qt and write to standard output contents similar to:

```
LibGL Vendor: NVIDIA Corporation
Renderer: GeForce GTX 980/PCIe/SSE2
Version: 4.6.0 NVIDIA 388.13
Shading Language: 4.60 NVIDIA
```

If the context can't be created, the command will output:

```
ERROR: Unable to create an OpenGL context.
```

Most of the (short) code is taken directly from the source code of Qt's `qtdiag` utility. Since standard output writing can have buffering issues on Windows (see `ETK-1517`, and the open Qt bug: https://bugreports.qt.io/browse/QTBUG-67860), the command includes a `-f` option to write the contents to a file (the contents are still written to standard output regardless). The contents of the file are UTF-8 encoded.

An `environment.devenv.yml` file is provided for local development, and the compilation itself should work fine on `conda build`. Currently the conda package can only be reliably built on win64 (seems to be a problem with the Qt package used on linux64 + py27).
