/*
Copyright (c) 2010 Alberto Fajardo
Copyright (c) 2020 David Schatz (C port)

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

/*
 * C port of the C# implementation by Alberto Fajardo (version 0.5.0)
 * C# sources can be found here: https://code.google.com/archive/p/skeinfish/
 */

#ifndef THREEFISH_H
#define THREEFISH_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define THREEFISH_1024_WORDS 16
#define KEY_SCHEDULE_CONST 0x1BD11BDAA9FC1A22

typedef struct Threefish1024Key {
    uint64_t key[THREEFISH_1024_WORDS + 1];  // expanded key
} Threefish1024Key;

/// Initialize Threefish1024 key from 16 64bit words.
inline void threefish1024_set_key(Threefish1024Key* key, const uint64_t* words)
{
    uint64_t parity = KEY_SCHEDULE_CONST;
    size_t   i;
    for(i = 0; i < THREEFISH_1024_WORDS; ++i) {
        key->key[i] = words[i];
        parity ^= words[i];
    }
    key->key[i] = parity;
}

/// Overwrite Threefish1024 key with 0.
inline void threefish1024_clear_key(Threefish1024Key* key)
{
    memset(key, 0, (THREEFISH_1024_WORDS + 1) * sizeof(uint64_t));
}

/// in and out must both point to 16 64bit words.
void threefish1024_encrypt(
    const Threefish1024Key* key,
    const uint64_t          tweak[2],
    const uint64_t*         in,
    uint64_t*               out);

/// in and out must both point to 16 64bit words.
void threefish1024_decrypt(
    const Threefish1024Key* key,
    const uint64_t          tweak[2],
    const uint64_t*         in,
    uint64_t*               out);

#endif  // THREEFISH_H
