#  Simulate digestion of DNA by nucleases.
#  Adapt this file to your needs

if [ ! -z $(grep "makeSPLIT(i);" "cleavagesim.cpp") ]; then 
    echo "Using makeSPLIT algorithm."; 
    echo "Code for labelled DNA simulation." > codestate.txt;
fi

if [ ! -z $(grep "makeSPLITunlabelled(i);" "cleavagesim.cpp") ]; then 
    echo "Using makeSPLITunlabelled algorithm."; 
    echo "Code for UNlabelled DNA simulation." > codestate.txt;
fi

HOMEX=/home/louis
g++ -I/usr/include -I$HOMEX/lib/gsl/include -O3 -c main_cleavagesim.cpp 
g++ -I/usr/include -I$HOMEX/lib/gsl/include -O3 -c cleavagesim.cpp 
g++ -o cleavagesim.out cleavagesim.o main_cleavagesim.o -L$HOMEX/lib/gsl/lib/ -static -O3 -lgsl -lgslcblas -lm 

