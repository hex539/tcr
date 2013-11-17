# Mostly just calls cat.pl

tcr.pdf:
	perl link.pl > tcr.tex
	convert -density 10 bath.eps bath.png
	pdflatex tcr.tex # toc
	convert -density 1800 bath.eps bath.png
	pdflatex tcr.tex # contents

all:\
  tcr.pdf

show:\
  all
	@ xdg-open tcr.pdf

cruft:
	rm -f tcr.aux\
	      tcr.toc\
	      tcr.out\
	      tcr.log\

clean:\
  cruft
	rm -f tcr.tex\
				bath.png\
	      tcr.pdf
