/*
 * Geargrafx - PC Engine / TurboGrafx Emulator
 * Copyright (C) 2024  Ignacio Sanchez

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/
 *
 */

#include "emu.h"
#include "config.h"
#include "geargrafx.h"

#define RUNAHEAD_IMPORT
#include "runahead.h"

static u8* runahead_buffer = NULL;
static s16* runahead_audio = NULL;
static size_t runahead_buffer_size = 0;

static bool ensure_buffer(void);

void runahead_init(void)
{
    // Skip allocation entirely on PS2 to save memory and prevent state-cloning overhead
    runahead_audio = NULL;
    runahead_buffer = NULL;
    runahead_buffer_size = 0;
}

void runahead_destroy(void)
{
    SafeDeleteArray(runahead_audio);
    SafeDeleteArray(runahead_buffer);
    runahead_buffer_size = 0;
}

int runahead_get_frames(void)
{
    // Force run-ahead off on the PS2 to protect framerate performance
    return 0;
}

void runahead_run(int frames, u8* frame_buffer, s16* sample_buffer, int* sample_count)
{
    // Bypass speculative execution and execute a single standard frame
    GeargrafxCore* core = emu_get_core();
    core->RunToVBlank(frame_buffer, sample_buffer, sample_count);
}

static bool ensure_buffer(void)
{
    // Bypass save-state buffer allocations entirely on the PS2
    return false;
}
