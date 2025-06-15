//-----------------------------------------------------------------------------
// Copyright 2019 Thiago Alves
// This file is part of the OpenPLC Software Stack.
//
// OpenPLC is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// OpenPLC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with OpenPLC.  If not, see <http://www.gnu.org/licenses/>.
//------
//
// This file is responsible for the persistent storage on the OpenPLC
// Thiago Alves, Jun 2019
//
// Added modifications from gexod to include %MD and %ML into the persistent file
// See https://openplc.discussion.community/post/variable-retain-function-9914880?highlight=retain&trail=30
//-----------------------------------------------------------------------------

#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <ctime>

#include "ladder.h"

#define FILE_PATH "persistent.file"

uint8_t pstorage_read_complete = false;
uint32_t combined_checksum = 0; // Stored checksum for detecting changes

//-----------------------------------------------------------------------------
// Function to calculate a simple XOR-based checksum for all three arrays together
//-----------------------------------------------------------------------------
uint32_t calculate_combined_checksum()
{
    uint32_t checksum = 0;
//    for (auto & i : _MW)  if (i != nullptr) checksum ^= *i; // checksum for int_memory
//    for (auto & i : _MD) if (i != nullptr) checksum ^= *i; // checksum for dint_memory
//    for (auto & i : _ML) if (i != nullptr) checksum ^= (uint32_t)(*i ^ (*i >> 32)); // lint_memory

    for (const auto & i : MW) checksum ^= i; // checksum for int_memory
    for (const auto & i : MD) checksum ^= i; // checksum for dint_memory
    for (const auto & i : ML) checksum ^= (uint32_t)(i ^ (i >> 32)); // lint_memory

    return checksum;
}

//-----------------------------------------------------------------------------
// Main function for the thread. Should create a buffer for the persistent data,
// compare it with actual data and write back to the persistent file if changed.
//-----------------------------------------------------------------------------
void startPstorage()
{
    // Wait for persistent.file was read
    while (!pstorage_read_complete) sleepms(100);

    char log_msg[1000];
    sprintf(log_msg, "Starting Persistent Storage thread\n");
    log(log_msg);

    // Run the main thread
    while (run_pstorage) {

        // Calculate the combined checksum
        uint32_t new_checksum = calculate_combined_checksum();
        if (new_checksum != combined_checksum) {
            combined_checksum = new_checksum; // Update the stored checksum

            // Open persistent.file for writing
            FILE *file = fopen(FILE_PATH, "wb");
            if (file == nullptr) {
                sprintf(log_msg, "Persistent Storage: Error creating persistent memory file!\n");
                log(log_msg);
                return;
            }

            // Write the contents of int_memory
//            for (auto &i: _MW) {
//                uint16_t value = (i != nullptr) ? *i : 0;
            for (const auto &i: MW) {
                uint16_t value = i;
                if (fwrite(&value, sizeof(uint16_t), 1, file) != 1) {
                    sprintf(log_msg, "Persistent Storage: Error writing int_memory to file\n");
                    log(log_msg);
                }
            }

            // Write the contents of dint_memory
//            for (auto &i: _MD) {
//                uint32_t value = (i != nullptr) ? *i : 0;
            for (const auto &i: MD) {
                uint32_t value = i;
                if (fwrite(&value, sizeof(uint32_t), 1, file) != 1) {
                    sprintf(log_msg, "Persistent Storage: Error writing dint_memory to file\n");
                    log(log_msg);
                }
            }

            // Write the contents of lint_memory
//            for (auto &i: _ML) {
//                uint64_t value = (i != nullptr) ? *i : 0;
            for (const auto &i: ML) {
                uint64_t value = i;
                if (fwrite(&value, sizeof(uint64_t), 1, file) != 1) {
                    sprintf(log_msg, "Persistent Storage: Error writing lint_memory to file\n");
                    log(log_msg);
                }
            }

            // Flush and sync to ensure data is written to disk
            /* fflush(file); int fd = fileno(file); fsync(fd); */

            fclose(file);
        }

        sleepms(pstorage_polling*1000);             // time for thread sleep
    }
}

//-----------------------------------------------------------------------------
// This function reads the contents from persistent.file into OpenPLC internal
// buffers. Must be called when OpenPLC is initializing. If persistent storage
// is disabled, the persistent.file will not be found and function exit.
//-----------------------------------------------------------------------------
void readPersistentStorage()
{
    char log_msg[1000];
    FILE *file = fopen(FILE_PATH, "rb");
    if (file == nullptr) {
        sprintf(log_msg, "Persistent Storage is empty\n");
        log(log_msg);
        pstorage_read_complete = true;
        return;
    }

    {
        std::lock_guard<std::mutex> lock(bufferLock);

        // Read the contents into int_memory
        for (size_t i = 0; i < BUFFER_SIZE; i++) {
            uint16_t value;
            // Read each value individually
            if (fread(&value, sizeof(uint16_t), 1, file) != 1) {
                if (feof(file)) break; // Stop on end of file
                sprintf(log_msg, "Error reading int_memory from file");
                log(log_msg);

                bufferLock.unlock(); //unlock mutex

                fclose(file);
                pstorage_read_complete = true;
                return;
            }

            // Only assign if value is non-zero
            if (value != 0) {
                // Allocate memory if the pointer is nullptr
//            if (_MW[i] == nullptr) {
//                _MW[i] = static_cast<IEC_UINT *>(malloc(sizeof(uint16_t)));
//                if (_MW[i] == nullptr) {
//                    sprintf(log_msg, "Error allocating memory for int_memory[%d]", (int)i);
//                    log(log_msg);
//                    continue;
//                }
//            }
//            *_MW[i] = value; // Store the value
                MW[i] = value; // Store the value
            }
        }

        // Read the contents into dint_memory
        for (size_t i = 0; i < BUFFER_SIZE; i++) {
            uint32_t value;
            // Read each value individually
            if (fread(&value, sizeof(uint32_t), 1, file) != 1) {
                if (feof(file)) break; // Stop on end of file
                sprintf(log_msg, "Error reading dint_memory from file");
                log(log_msg);

                bufferLock.unlock(); //unlock mutex
                fclose(file);

                pstorage_read_complete = true;
                return;
            }

            // Only assign if value is non-zero
            if (value != 0) {
                // Allocate memory if the pointer is nullptr
//            if (_MD[i] == nullptr) {
//                _MD[i] = static_cast<IEC_UDINT *>(malloc(sizeof(uint32_t)));
//                if (_MD[i] == nullptr) {
//                    sprintf(log_msg, "Error allocating memory for dint_memory[%d]", (int)i);
//                    log(log_msg);
//                    continue;
//                }
//            }
//            *_MD[i] = value; // Store the value
                MD[i] = value; // Store the value
            }
        }

        // Read the contents into lint_memory
        for (size_t i = 0; i < BUFFER_SIZE; i++) {
            uint64_t value;
            // Read each value individually
            if (fread(&value, sizeof(uint64_t), 1, file) != 1) {
                if (feof(file)) break; // Stop on end of file
                sprintf(log_msg, "Error reading lint_memory from file");
                log(log_msg);

                bufferLock.unlock(); //unlock mutex
                fclose(file);

                pstorage_read_complete = true;
                return;
            }

            // Only assign if value is non-zero
            if (value != 0) {
                // Allocate memory if the pointer is nullptr
//            if (_ML[i] == nullptr) {
//                _ML[i] = static_cast<IEC_ULINT *>(malloc(sizeof(uint64_t)));
//                if (_ML[i] == nullptr) {
//                    sprintf(log_msg, "Error allocating memory for lint_memory[%d]", (int)i);
//                    log(log_msg);
//                    continue;
//                }
//            }
//            *_ML[i] = value; // Store the value
                ML[i] = value; // Store the value
            }
        }

    }

    fclose(file);

    sprintf(log_msg, "Persistent Storage: Finished reading persistent memory\n");
    log(log_msg);
    pstorage_read_complete = true;

}