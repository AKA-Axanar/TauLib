doxygen.exe Doxyfile
pushd Doc\latex
call make.bat
del /y TauLib.pdf
ren refman.pdf TauLib.pdf
popd
