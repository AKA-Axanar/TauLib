rmdir /S /Q curl
git clone https://github.com/curl/curl.git
rmdir /S /Q include
xcopy /E /C /I /Q /H /R /Y curl\include\curl\* include\
