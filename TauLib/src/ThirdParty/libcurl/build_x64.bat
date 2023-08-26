rem ======================================================================
rem run using Visual Studio x64 Native Tools Developer Command Prompt
rem                              ***
rem ======================================================================
pause

pushd curl\winbuild
set RTLIBCFG=static
nmake /f Makefile.vc mode=static vc=17 machine=x64 debug=yes
nmake /f Makefile.vc mode=static vc=17 machine=x64
popd

rmdir /s /q x64
xcopy /e curl\builds\libcurl-vc17-x64-debug-static-ipv6-sspi-schannel\lib x64\Debug\lib\
xcopy /e curl\builds\libcurl-vc17-x64-release-static-ipv6-sspi-schannel\lib x64\Release\lib\

::rmdir /s /q curl\builds\libcurl-vc17-x64-debug-static-ipv6-sspi-schannel
::rmdir /s /q curl\builds\libcurl-vc17-x64-debug-static-ipv6-sspi-schannel-obj-curl
::rmdir /s /q curl\builds\libcurl-vc17-x64-debug-static-ipv6-sspi-schannel-obj-lib
::rmdir /s /q curl\builds\libcurl-vc17-x64-release-static-ipv6-sspi-schannel
::rmdir /s /q curl\builds\libcurl-vc17-x64-release-static-ipv6-sspi-schannel-obj-curl
::rmdir /s /q curl\builds\libcurl-vc17-x64-release-static-ipv6-sspi-schannel-obj-lib
