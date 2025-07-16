#!/bin/bash
### -----------------------------------
# Startup script for PROCONT-EX service
### -----------------------------------

set -euo pipefail  # Безопасный режим выполнения

### Basic configuration
# -----------------------
APP_NAME="procont-ex"
INSTALL_DIR="$(dirname "$(dirname "$(realpath "$0")")")"  # Определение пути установки

# Проверка корректности определения INSTALL_DIR
if [ ! -d "$INSTALL_DIR" ]; then
    echo "ERROR: Cannot determine installation directory" >&2
    exit 1
fi

APP_PATH="${INSTALL_DIR}/bin/${APP_NAME}"
CONFIG_DIR="${INSTALL_DIR}/etc"
LOG_DIR="${INSTALL_DIR}/logs"

### Prepare environment
# -----------------------
mkdir -p "${CONFIG_DIR}" "${LOG_DIR}"
chmod 755 "${CONFIG_DIR}" "${LOG_DIR}"

# Создаем лог-файл с правильными правами
LOG_FILE="${LOG_DIR}/output.log"
touch "$LOG_FILE"
chmod 644 "$LOG_FILE"

# Load environment variables
if [ -f "${CONFIG_DIR}/environment" ]; then
    source "${CONFIG_DIR}/environment"
fi

### Verify prerequisites
# -----------------------
if [ ! -f "$APP_PATH" ]; then
    echo "ERROR: Application binary not found at $APP_PATH" >&2
    exit 1
fi

if [ ! -f "${CONFIG_DIR}/modules_config.json" ]; then
    echo "WARNING: Config file modules_config.json not found" >&2
fi

if [ ! -f "${CONFIG_DIR}/zmq.properties" ]; then
    echo "WARNING: Config file zmq.properties not found" >&2
fi

### Start application
# -----------------------
echo "Starting ${APP_NAME} from ${APP_PATH}" | tee -a "$LOG_FILE"
echo "Logging output to ${LOG_FILE}" | tee -a "$LOG_FILE"

exec "$APP_PATH" \
    --config "${CONFIG_DIR}/modules_config.json" \
    --properties "${CONFIG_DIR}/zmq.properties" \
    >> "$LOG_FILE" 2>&1

