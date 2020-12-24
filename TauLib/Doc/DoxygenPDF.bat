doxygen.exe Doxyfile
pushd latex
del /q refman.pdf
del /q TauLib.pdf
call make.bat
copy /Y refman.pdf TauLib.pdf
popd
