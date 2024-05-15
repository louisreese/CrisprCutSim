# Stochastic Nucleotide Cleavage Simulation
The simulation was used to quantify the dynamics of a CRISPR-based DNA and RNA detection assay by compaing it to time-dependent gel electrophoresis experiments. Thereby only a fraction of the oligonucleotides is labelled with dye and fluorescence signals vanish much quicker as compared to turbidity in LLPS experiments. The code produces time dependent polymer mass distributions for the fluorescently labelled DNA as well as for the unlabelled DNA.


The project is written in C++ and compiles under Ubuntu 18 with GNU g++ (e.g. 7.5.0). It also requires the GNU Scientific Library (>=2.7) for random numbers. A standard installation in the /usr/include and /usr/lib directories was used.

Please send me a message if you need help with this project. I do not actively maintain it.

## Running the program
You can call the program from the commandline with three parameters:
    ./cleavagesim.out [Int - polymer size] [Float - digestion rate] [Int - rng seed]

The output files will be `LABEL_$Size_$k1_RanInit.csv` and contain the following data in CSV:

    [time] [[Integer configuration array]] [average polymer size]


## References
Spoelstra et al, CRISPR-based DNA and RNA detection with liquid-liquid phase separation, [2021](https://doi.org/10.1016/j.bpj.2021.02.013)

