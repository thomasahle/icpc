BASENAME  = lambda_doc
FILENAME  = lambda_doc
OUTDIR    = $(CURDIR)/output
OUTFILE   = $(OUTDIR)/$(FILENAME).pdf

COMPILE   = pdflatex -output-directory=output -file-line-error \
            -jobname $(FILENAME) $(BASENAME)

default: compile
compile:
	@mkdir -p "$(OUTDIR)"
	$(COMPILE) && $(COMPILE)

bibtex: compile
	cd "$(OUTDIR)"
	bibtex $(FILENAME).aux
	cd "$(CURDIR)"

print:
	cat $(OUTFILE) | ssh ask.diku.dk lpr -P m1b

clean:
	rm -r $(OUTDIR)

