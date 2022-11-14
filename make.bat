g++ -std=c++11 -O2 main.cpp -o gen.exe
gen.exe
XeLatex template.tex
XeLatex template.tex
for /F %%f in ('dir /b template.* gen.exe') do (
	if not %%f == template.pdf (del %%f )
)