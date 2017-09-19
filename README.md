# C language Scanner

This is a C-scanner built with the tool `flex`, it outputs syntax highlighting and a histogram of tokens to a pdf presentation (compiled with latex)

Relevant files are:

*  `scanner.l`: file used to build the flex scanner (lex.yy.c).

*  `scanner.c`: this is the main program, it executes everything.

*  `beamer.tex`: this is the beamer presentation.

*  `source.tex`: this is the automatically generated code by scanner.c, it writes the syntax-highlighted code onto the beamer presentation.

*  `lex.yy.c`: this is the automatically generated code by flex.

*  `datafile.dat`: automatically generated file to plot the histogram.

*  `histogram_script.gnu`: script used to create the histogram.

*  `histogram.png`: output png histogram from gnuplot.

*  `beamer.pdf`: output pdf presentation.

*  `\tests`: folder with C source files to test the scanner with.

To build just run `make` and then to run the program `./scanner < file_to_be_scanned`, for example: `./scanner < tests/linuxmain.c`

# Dependencies

The code is written such that it assumes you have installed `gnuplot`, `pdflatex` and `okular`. The commands run by the program are declared in an array inside `scanner.c` at the beginning and can be edited accordingly.
The least important of programs is `okular` which is a pdf-viewer, you may run the program without okular and load the pdf with your pdf-viewer of choice.

# Screenshots

![Screenie3](https://i.imgur.com/Nbmbx5E.png)
![Screenie2](https://i.imgur.com/oF1HXJF.png)
![Screenie1](https://i.imgur.com/SwqEzSw.png)
