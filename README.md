# Stochastic Nucleotide Cleavage Simulation
Simulation of oligonucleotide cleavage by nucleases.
The simulation allows to quantify gel electrophoresis experiments, where only a fraction of the oligonucleotides is labelled with a dye. You can compare the ensuing time dependent polymer mass distribution to the case of unlabelled oligonucleotides; see howto.txt.
The project compiles with GNU g++ (e.g. 7.5.0) and requires the GNU Scientific Library (>=2.7) for random numbers installed in the /usr/include and /usr/lib directories.
Please send me a message if you need help with this project. I do not actively maintain it.

## Running the program
usage:  ./cleavagesim.out [Int - polymer size] [Float - digestion rate] [Int - rng seed]
output: [time] [[Integer configuration array]] [average polymer size]


## References
Spoelstra et al, CRISPR-based DNA and RNA detection with liquid-liquid phase separation, [2021](https://doi.org/10.1016/j.bpj.2021.02.013)

