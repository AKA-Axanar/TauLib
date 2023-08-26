rem ======================================================================
rem run using Visual Studio x86 Native Tools Developer Command Prompt
rem                              ***
rem ======================================================================
pause

pushd curl\winbuild
set RTLIBCFG=static
nmake /f Makefile.vc mode=static vc=17 machine=x86 debug=yes
nmake /f Makefile.vc mode=static vc=17 machine=x86
popd

rmdir /s /q x86
xcopy /e curl\builds\libcurl-vc17-x86-debug-static-ipv6-sspi-schannel\lib x86\Debug\lib\
xcopy /e curl\builds\libcurl-vc17-x86-release-static-ipv6-sspi-schannel\lib x86\Release\lib\

::rmdir /s /q curl\builds\libcurl-vc17-x86-debug-static-ipv6-sspi-schannel
::rmdir /s /q curl\builds\libcurl-vc17-x86-debug-static-ipv6-sspi-schannel-obj-curl
::rmdir /s /q curl\builds\libcurl-vc17-x86-debug-static-ipv6-sspi-schannel-obj-lib
::rmdir /s /q curl\builds\libcurl-vc17-x86-release-static-ipv6-sspi-schannel
::rmdir /s /q curl\builds\libcurl-vc17-x86-release-static-ipv6-sspi-schannel-obj-curl
::rmdir /s /q curl\builds\libcurl-vc17-x86-release-static-ipv6-sspi-schannel-obj-lib

