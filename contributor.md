#First fork Seal repository from https://github.com/Mishra1992/Seal.git
git clone https://github.com/mishrag324/Seal.git
cd Seal/
git init 
git remote add upstream https://github.com/Mishra1992/Seal.git
git fetch upstream
git diff master upstream/master
git merge upstream/master
#add changes
git add .
git commit -m "<message>"
git push -u origin master
git pull upstream master 
