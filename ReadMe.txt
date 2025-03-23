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
# (тестируется ...)


