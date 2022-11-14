.PHONY:clean

all: template.tex
	xelatex template.tex
	xelatex template.tex
	find template.* gen | grep -v template.pdf | xargs rm

template.tex: gen

gen: main.cpp
	$(CXX) -std=c++11 -O2 $^ -o $@
	./$@

clean:
	rm template.* gen
