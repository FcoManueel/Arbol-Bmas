cd %~dp0
del "ArbolB+.exe" "ArbolB+_archivos.exe"
g++ -c -g agregar.cpp auxiliares.cpp buscar.cpp constructores.cpp borrar.cpp
g++ -g -o "ArbolB+.exe" main.cpp *.o -static-libstdc++
g++ -g -o "ArbolB+_archivos.exe" main_archivos.cpp *.o -static-libstdc++
del *.o