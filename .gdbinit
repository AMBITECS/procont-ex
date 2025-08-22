# Архитектура и формат
set architecture aarch64
set gnutarget elf64-littleaarch64

#set stop-on-solib-events 0

# Дизассемблирование
set disassembly-flavor intel

# Локальный путь к библиотекам
set sysroot /lib/aarch64-linux-gnu/sys-root
set solib-search-path  /usr/lib/gcc/aarch64-linux-gnu/14:/usr/lib/aarch64-linux-gnu/sys-root/usr/lib:/home/master/Ambi/Work/Projects/procont-ex/.deploy/lib:/home/master/Ambi/Work/Projects/procont-ex/.deploy/modules

# Обработка сигналов (важно для QEMU!)
handle SIGILL nostop noprint pass
#handle SIGTRAP nostop noprint
#handle SIGBUS nostop noprint

# Каталог проекта
set substitute-path /project /home/master/Ambi/Work/Projects/procont-ex
directory /home/master/Ambi/Work/Projects/procont-ex

# Загрузка символов
#cd /home/master/Ambi/Work/Projects/procont-ex/.deploy/bin/
#file ./procont-ex

# Подключение к QEMU
#target remote localhost:12345

# Дополнительные настройки (опционально)
set print pretty on
set pagination off
