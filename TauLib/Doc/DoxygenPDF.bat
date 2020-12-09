doxygen.exe Doxyfile
pushd latex
call make.bat
del /q TauLib.pdf
ren refman.pdf TauLib.pdf
popd
