FILES = Debugger_Not_In_Depth.tex preface.tex frame.tex

SUBDIRS= frame

all: Debugger_Not_In_Depth.pdf

subdir_do:
	@for i in $(DODIRS); do \
		if [ -f ./$$i/Makefile ] ; then \
                        if 	(cd ./$$i; \
                                make $(DO)) ; then true ; \
                        else exit 1 ; fi ; \
                else true ; fi ; \
        done

build_subdir:
	@make DO=all "DODIRS=$(SUBDIRS)" subdir_do

figure:
	mpost figure.mp

clean:
	@make DO=clean "DODIRS=$(SUBDIRS)" subdir_do
	-rm -f Debugger_Not_In_Depth.pdf
	-rm -f *.aux *.dvi *.bbl *.blg *.out *.toc *.log

#%.dvi:%.tex
#	latex $<
#	bibtex $< 
#	latex $<
#	latex $<

Debugger_Not_In_Depth.dvi: build_subdir $(FILES) reference.bib figure
	latex Debugger_Not_In_Depth
	bibtex Debugger_Not_In_Depth
	latex Debugger_Not_In_Depth
	latex Debugger_Not_In_Depth


%.pdf:%.dvi
	dvipdf $<

%.txt:%.html
	w3m -T text/html -dump $< > $@
%.html:%.tex
	latex2html -split 0 -nonavigation -notop_navigation -nobottom_navigation -nosubdir $<


