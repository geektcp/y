# example for C++ projects



## Structure
``` text
.
├── CMakeLists.txt
├── app
│   └── main.cpp
├── include
│   ├── example.h
│   └── exampleConfig.h.in
├── src
│   └── example.cpp
└── tests
    ├── dummy.cpp
    └── main.cpp
```

Sources go in [src/](src/), header files in [include/](include/), main programs in [app/](app), and
tests go in [tests/](tests/) (compiled to `unit_tests` by default).

If you add a new executable, say `app/hello.cpp`, you only need to add the following two lines to [CMakeLists.txt](CMakeLists.txt):

```cmake
add_executable(main app/main.cpp)   # Name of exec. and location of file.
target_link_libraries(main PRIVATE ${LIBRARY_NAME})  # Link the executable to lib built from src/*.cpp (if it uses it).
```

You can find the example source code that builds the `main` executable in [app/main.cpp](app/main.cpp) under the `Build` section in [CMakeLists.txt](CMakeLists.txt).
If the executable you made does not use the library in [src/](src), then only the first line is needed.



## Building

Build by making a build directory (i.e. `build/`), run `cmake` in that dir, and then use `make` to build the desired target.

Example:

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=[Debug | Coverage | Release]
make
./main
make test      # Makes and runs the tests.
make coverage  # Generate a coverage report.
make doc       # Generate html documentation.
```

## .gitignore

The [.gitignore](.gitignore) file is a copy of the [Github C++.gitignore file](https://github.com/github/gitignore/blob/master/C%2B%2B.gitignore),
with the addition of ignoring the build directory (`build/`).

## Services

If the repository is activated with Travis-CI, then unit tests will be built and executed on each commit.
The same is true if the repository is activated with Appveyor.

If the repository is activated with Coveralls/Codecov, then deployment to Travis will also calculate code coverage and
upload this to Coveralls.io and/or Codecov.io

## Setup

### Using the GitHub template
Click the `Use this template` button to make a new repository from this template.

### From command line
When starting a new project, you probably don't want the history of this repository. To start fresh you can use
the [setup script](setup.sh) as follows:
```bash
git clone https://github.com/bsamseth/cpp-project  # Or use ssh-link if you like.
cd cpp-project
bash setup.sh
```
The result is a fresh Git repository with one commit adding all files from the boiler plate.
