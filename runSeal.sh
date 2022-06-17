sudo apt update && sudo apt install clang
sudo apt update && sudo apt install build-essential
sudo snap install cmake --classic
git clone https://github.com/microsoft/SEAL.git
cd Seal
cmake -S . -B build
cmake --build build
sudo cmake --install build
