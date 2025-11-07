# tail engine
tail engine is a game engine designed to be a game engine (built off of [furry-framework](https://github.com/viylouu/furry-framework))  
it is built using c++ (gnu++17)

# license
this project is licensed under the LGPLv3 copyleft,  
for more information, see [here](LICENSE.LGPL)

## usage
to use this framework in your project, its pretty "simpleh  
heres some steps (there are 2 routes you can take: with and without git):
- USING GIT:
    - in your project root:
        - run `git submodule add https://github.com/viylouu/tail-engine.git`
        - run `git mv tail-engine tail`
    - then, do the `GENERAL` steps
- WITHOUT GIT:
    - clone the repo `git clone https://github.com/viylouu/tail-engine.git`
    - in your project, copy the `tail-engine` folder over to it
    - rename `tail-engine`to `tail`
    - then, do the `GENERAL` steps
- GENERAL:
    - copy a few files and folders from `tail` to your project root:
        - `build.sh`
        - `data`
        - `.gitignore` (optionally)
        - `.gitattributes` (optionally)`

## building
when building, you can do one of 2 things:
- build your own project
- build an example

to build an example:
- in the `tail-engine` folder (or the `tail` folder) you *definitely* cloned already:
    - run `./build.sh EXAMPLE_NAME <options>`
        - for example, running the `window` example would be `./build.sh window`
> NOTE:  
> here are some options for you  
> -t   builds as a test using -O0 (or tcc)  
> -w   builds for windows (NOT NEEDED ON WINDOWS)  

to build your own project:
- in your project root:
    - run `./build.sh <options>`
