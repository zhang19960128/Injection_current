make
./injection >./visual/injection.dat
matlab -nodesktop -r "run ./visualize/showspectrum.m;exit";
epstopdf ./visual/BTO.eps ./visualize/BTO.pdf
git add src
git add include 
git add visual
git commit -m "change"
git push -u origin master
