/*
 * usbwrite - dd wrapper for easily writing ISO to USB devices
 * Copyright (C) 2025  Connor Thomson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: usbwrite <iso pattern> <usb device>\n");
        return 1;
    }

    const char *pattern = argv[1];
    const char *device = argv[2];
    glob_t glob_result;

    if (glob(pattern, 0, NULL, &glob_result) != 0 || glob_result.gl_pathc == 0) {
        fprintf(stderr, "No file matches pattern: %s\n", pattern);
        return 1;
    }

    const char *iso_path = glob_result.gl_pathv[0];
    char command[1024];
    snprintf(command, sizeof(command),
        "sudo dd if='%s' of='/dev/%s' status=progress bs=4M conv=fsync",
        iso_path, device);

    printf("Executing: %s\n", command);
    int result = system(command);

    globfree(&glob_result);
    return result;
}
