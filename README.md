# parcial-software
parcial software 2022-1

build-wrapper-win-x86-64.exe --out-dir bw-output g++ main.cpp

sonar-scanner.bat -D"sonar.organization=mauricio-bernuy" -D"sonar.projectKey=Mauricio-Bernuy_parcial-software" -D"sonar.sources=." -D"sonar.cfamily.build-wrapper-output=bw-output" -D"sonar.host.url=https://sonarcloud.io"