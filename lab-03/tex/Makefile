.PHONY: rep clean

FILE = main

rep:
	tectonic --keep-intermediates --reruns 0 $(FILE).tex
	bibtex $(FILE)
	tectonic $(FILE).tex
	mv $(FILE).pdf "3_ЛАБ-ЗИ-76Б_КовельАД.pdf"

clean:
	rm *.aux *.bbl *.blg *.log *.out *.toc pages/*.aux inc/*.aux inc/*.bbl inc/*.blg inc/*.log inc/*.out inc/*.toc
	echo "Clear:Ready"