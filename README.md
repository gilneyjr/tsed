# TSED
TSED is a tree transducer developed to modify treebanks using  powerful command-line tool for searching and filtering text, similar to grep.

## 🚀 Getting Started

### Required Software for Compilation
These are the required software to compile and run TSED:
- G++ compiler
- Flex
- Bison
- Make

Ensure you have them installed:
```sh
g++ --version
flex --version
bison --version
make --version
```

If any command fails or isn’t recognized, install the corresponding program as decribed bellow.

### Installation of Required Software
#### Windows (via MSYS2)
1. Download and install [MSYS2](https://www.msys2.org/).
2. Open MSYS2 terminal.
3. Synchronize the repository databases and update the system's packages using pacman:
   ```sh
   pacman -Syu
   ```
4. Install the required packages:
   ```sh
   pacman -S mingw-w64-x86_64-gcc make flex bison
   ```
5. Make sure the environment variables are set for all these tools.
6. Check the [Required Software for Compilation](#required-software-for-compilation) section to ensure the tools were successfuly installed.

#### Linux (Debian-based)
1. Run these comands to install the required tools:
   ```bash
   sudo apt update
   sudo apt install build-essential flex bison
   ```
2. Check the [Required Software for Compilation](#required-software-for-compilation) section to ensure the tools were successfuly installed.

#### MacOS (via Homebrew)
1. Run this command to install the required tools:
   ```sh
   brew install flex bison make
   ```
2. Check the [Required Software for Compilation](#required-software-for-compilation) section to ensure the tools were successfuly installed.

### Compilation & Usage

1. Clone this repository:
   ```sh
   git clone https://github.com/gilneyjr/tsed.git
   ```
2. Navigate to the project directory:
   ```sh
   cd tsed
   ```
3. Build the project:
   ```sh
   make
   ```
4. Run the following command to see usage:
   ```sh
   ./build/release/tsed --help
   ```

## 📌 Author

**Gilney Junior** - [LinkedIn](https://www.linkedin.com/in/gilneyjr) | [GitHub](https://github.com/gilneyjr)

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

