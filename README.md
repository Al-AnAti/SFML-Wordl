# Wordl (SFML)

A Wordle clone written in C++20 using [SFML 2.6](https://www.sfml-dev.org/).

Guess the hidden five-letter word in six tries. After each guess the squares turn green (right letter, right place), yellow (right letter, wrong place) or gray (not in the word). The target is drawn from the original Wordle answer list, and a guess is accepted if it's in that list or the larger allowed-guesses list.

## Controls

| Key         | Action                       |
|-------------|------------------------------|
| `A`–`Z`     | Type a letter                |
| `Backspace` | Delete the last letter       |
| `Enter`     | Submit the guess             |
| `R`         | New word after the game ends |
| `Esc`       | Quit                         |

## Project layout

```
SFML-Wordl/
├── assets/
│   ├── data/         # answers.txt (possible targets), allowed.txt (extra valid guesses)
│   └── fonts/        # Font used for the letters and end-of-game text
├── src/              # Game source code
│   ├── main.cpp
│   ├── Game.*        # Window, main loop, guess checking
│   ├── Square.*      # One lettered square on the board
│   └── Words.*       # Word list loading and target selection
└── CMakeLists.txt
```

## Building

You need CMake 3.28 or newer and a C++20 compiler. SFML is downloaded and built automatically the first time you configure, so you don't need to install it.

```bash
cmake -B build
cmake --build build --config Release
```

The game ends up in `build/bin/` (or `build/bin/Release/` with Visual Studio), with the `assets` folder copied next to it. Run it from that folder.

### Visual Studio

Open the project folder with **File → Open → Folder**. Visual Studio detects `CMakeLists.txt`; pick `Wordl.exe` as the startup item and press F5. This needs the **C++ CMake tools for Windows** component, which you can add from the Visual Studio Installer.

### Using an installed SFML

To use an SFML 2.6 that's already on your system instead of downloading it:

```bash
cmake -B build -DWORDL_FETCH_SFML=OFF
```

On Linux, building SFML from source needs its system dependencies first. See the [SFML build guide](https://www.sfml-dev.org/tutorials/2.6/compile-with-cmake.php).

### Making a release folder

```bash
cmake --install build --config Release --prefix dist
```

This puts the executable and `assets/` in `dist/`, ready to zip and share.
