#!/bin/bash
### -----------------------------------
# Startup script for PROCONT-EX service (local installation)
### -----------------------------------

### Basic configuration
# -----------------------
APP_NAME="PROCONT-EX"
# Путь относительно домашней директории
#INSTALL_DIR="$HOME/procont-ex/.install"   
INSTALL_DIR="$(dirname "$(dirname "$(realpath "$0")")"
#INSTALL_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)  # Автоматическое определение

APP_PATH="${INSTALL_DIR}/bin/${APP_NAME}" # Новый путь к бинарнику
CONFIG_DIR="${INSTALL_DIR}/etc"           # Конфиги теперь в .install/etc
LOG_DIR="${INSTALL_DIR}/logs"             # Логи в .install/logs

### Prepare environment
# -----------------------

# Create directories if they don't exist
mkdir -p ${CONFIG_DIR} ${LOG_DIR}
chmod 755 ${CONFIG_DIR} ${LOG_DIR}

# Load environment variables if needed
if [ -f "${CONFIG_DIR}/environment" ]; then
    . "${CONFIG_DIR}/environment"
fi

### Wait for dependencies
# -----------------------

### Example: wait for network
#for i in {1..10}; do
#    if ping -c 1 google.com &>/dev/null; then
#        break
#    fi
#    sleep 1
#done


### Start application
# -----------------------
exec ${APP_PATH} \
    --config ${CONFIG_DIR}/modules_config.json \
    --properties ${CONFIG_DIR}/zmq.properties \
    >> ${LOG_DIR}/output.log 2>&1

