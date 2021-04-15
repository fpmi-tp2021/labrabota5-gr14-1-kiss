#pragma once

#define HEADER_LENGTH 4

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>


uint16_t *farbfeld_read(void *farbfeld_data, uint32_t *ret_width, uint32_t *ret_height);
