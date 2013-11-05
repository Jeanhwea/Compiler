DVICC := latex
PDFCC := dvipdf
VIEWR := evince
TEXFILE := pl0.tex
DVIFILE := pl0.dvi
PDFFILE := pl0.pdf

all: ${TEXFILE}
	${DVICC} ${TEXFILE} -o ${DVIFILE} && ${PDFCC} ${DVIFILE} ${PDFFILE}

love:
	${DVICC} ${TEXFILE} -o ${DVIFILE} && ${PDFCC} ${DVIFILE} ${PDFFILE} && ${VIEWR} ${PDFFILE}

.PHONY: clean
clean:
	-rm *.dvi *.aux *.log
