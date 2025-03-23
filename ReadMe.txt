 #--------------------------------------
# (-A-) Сборка на системе хоста x86
#--------------------------------------
# (0) создание каталога сборки
cd <path-to-procont-ex>
mkdir cmake-build-debug-master 
cd cmake-build-debug-master

# (1) сборка cmake
# 1. параметр ST_FILE - путь к файлу ST либо абсолютный,
# либо имя файла в папке "<path-to-procont-ex>/st_files/"
# 2. по умолчанию - generator 'Unix Makefiles'
# для сборки ninja нужно указать явно параметр -G Ninja

cmake -DCMAKE_BUILD_TYPE=Debug ../ -DST_FILE=plc.st -G Ninja

# (2) сборка целей
# (2.1) цель "build-iec"
# собирает артефакты в каталоге "<path-to-procont-ex>/iec"

cmake --build . --target build-iec

# (2.2) цель "procont-ex" 
# собирает исполняемый модуль procont-ex 
# (в каталоге <path-to-procont-ex>/cmake-build-debug-master)

cmake --build . --target procont-ex

# (!) Примечания:
# 1. Цели (2.1) и (2.2) зависимы и их можно собрать за один шаг (2.2)
# 2. Для сборки с предварительной очисткой набрать:

cmake --build . --target procont-ex --clean-first

#--------------------------------------
# (-B-) Сборка на целевой системе arm64
#--------------------------------------
# (-2) установка docker в вашу систему
# (в соответствии с нормами системы)

# (-1) установка dockcross и сборка контейнера
git clone https://github.com/dockcross/dockcross.git
cd dockcross
docker run --rm dockcross/linux-arm64 > ./dockcross-linux-arm64
chmod +x ./dockcross-linux-arm64
mv ./dockcross-linux-arm64 /usr/local/bin/	
# вместо "/usr/local/bin/" можно любой каталог из $PATH

# (0) создание каталога сборки
mkdir dockcross-linux-arm64

# (1) сборка cmake (--fresh - очистка кеша) 
# (!) Внимание: ключ '-S' со значением '.' - запуск из текущего каталога проекта (procont-ex)
dockcross-linux-arm64 cmake -Bdockcross-linux-arm64 -S. -DCMAKE_BUILD_TYPE=Debug -DST_FILE=plc.st -G Ninja --fresh

# (2) сборка целей (ninja)
dockcross-linux-arm64 ninja -Cdockcross-linux-arm64

# (!) Результат:
# - в каталоге dockcross-linux-arm64 появился исполняемый файл procont-ex

#======================
# Общее примечание:
#======================
1. в каталоге procont-ex/cmake/find находятся файлы cmake для поиска библиотек (например, Findmodbus.cmake)
2. библиотеки среды procont-ex устанавливаются в ./utils/<имя-каталога-библиотеки>/$install
3. каталог $install содержит:
 - include/ - каталог заголовочных файлов
 - lib/     - каталог библиотеки aarch64
 - lib64/   - каталог библиотеки (по умолчанию) x86

(!) при сборке под arm64 каталог "lib64" переименовать, иначе библиотека при сборке cmake будет взята из него (а там- x86)
