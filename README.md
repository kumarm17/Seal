# Installation of SEAL Library 
These implementation has written over C++ using SEAL library from microsoft therefore to use these codes first install dependencies and then install SEAL as per guidance from SEAL group
## Requirements/Dependencies 
Install Clang++ or GNU g++ and CMake using following commands: <br />
```
sudo apt update && sudo apt install clang
sudo apt update && sudo apt install build-essential
sudo snap install cmake --classic
```
## Install seal library
After installing abovementioned dependencies, install seal library using following commands:
```
git clone https://github.com/microsoft/SEAL.git
cd Seal
cmake -S . -B build
cmake --build build
sudo cmake --install build
```

# Run SealDemo files 
Now you are ready to use this implementation via following commands:
Clone <br/>
```git clone https://github.com/Mishra1992/SEAL.git ``` <br/>
Move to SEAL directory
```cd SEAL``` <br/>
Configure the files
```cmake . ``` <br/>
Compile the file
```make ``` <br/>
Check the output as following 
```./bin/sealexamples ``` <br/>

## Contribute to the project as following.
Clone and initialize git in current directory 
```git clone <git repository url>
git init ```

## Git configuration 
Set the name and email that will be attached to your commits and tags. <br />
```
git config --global user.name <user name> 
git config --global user.email <email id> 
```
Enable some colorization of Git output. <br />
```git config --global color.ui auto ```

## Git branch <br />
Check the branch <br />
```git branch``` <br />
To change the branch <br />
```git checkout -b <branch name> ``` <br />
or <br />
```git switch -c <new branch> ```<br />
To delete the branch
```git checkout -D <branch name> ```<br />

## Update your files then do the following <br />
Check for changes <br />
```git status ```<br />
If changed, add changes to staging area <br />
```git add --all or git add <file name> ```<br />
Commit the changes made in staging area <br />
```git commit -m "description" ```<br />
Syncronize staging and git remote repository (use token as password) <br />
```git push origin <branch name> ```<br />
