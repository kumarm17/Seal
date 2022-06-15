# First fork Seal repository from https://github.com/Mishra1992/Seal.git <br />
git clone https://github.com/mishrag324/Seal.git <br />
cd Seal/ <br />
git init <br />
git remote add upstream https://github.com/Mishra1992/Seal.git <br />
git fetch upstream <br />
git diff master upstream/master <br />
git merge upstream/master <br />
# add changes <br />
git add . <br />
git commit -m "<message>" <br />
git push -u origin master <br />
git pull upstream master <br />
