// ImGui - binary_to_compressed_c.cpp
// Helper tool to turn a file into a C array, if you want to embed font data in your source code.

// The data is first compressed with stb_compress() to reduce source code size,
// then encoded in Base85 to fit in a string so we can fit roughly 4 bytes of compressed data into 5 bytes of source code (suggested by @mmalex)
// (If we used 32-bits constants it would require take 11 bytes of source code to encode 4 bytes, and be endianness dependent)
// Note that even with compression, the output array is likely to be bigger than the binary file..
// Load compressed TTF fonts with ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF()

// Build with, e.g:
//   # cl.exe binary_to_compressed_c.cpp
//   # gcc binary_to_compressed_c.cpp
// You can also find a precompiled Windows binary in the binary/demo package available from https://github.com/ocornut/imgui

// Usage:
//   binary_to_compressed_c.exe [-base85] [-nocompress] <inputfile> <symbolname>
// Usage example:
//   # binary_to_compressed_c.exe myfont.ttf MyFont > myfont.cpp
//   # binary_to_compressed_c.exe -base85 myfont.ttf MyFont > myfont.cpp

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "miniz.h"

// stb_compress* from stb.h - declaration
typedef unsigned int stb_uint;
typedef unsigned char stb_uchar;
stb_uint stb_compress(stb_uchar *out, stb_uchar *in, stb_uint len) {
    mz_ulong sz = compressBound(len);

    compress(out, &sz, in, len);

    return sz;
}

static bool binary_to_compressed_c(const char* filename, const char* symbol, bool use_base85_encoding, bool use_compression);

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printf("Syntax: %s [-base85] [-nocompress] <inputfile> <symbolname>\n", argv[0]);
        return 0;
    }

    int argn = 1;
    bool use_base85_encoding = false;
    bool use_compression = true;
    if (argv[argn][0] == '-')
    {
        if (strcmp(argv[argn], "-base85") == 0) { use_base85_encoding = true; argn++; }
        else if (strcmp(argv[argn], "-nocompress") == 0) { use_compression = false; argn++; }
        else
        {
            printf("Unknown argument: '%s'\n", argv[argn]);
            return 1;
        }
    }

    binary_to_compressed_c(argv[argn], argv[argn+1], use_base85_encoding, use_compression);
    return 1;
}

char Encode85Byte(unsigned int x) 
{
    x = (x % 85) + 35;
    return (x>='\\') ? x+1 : x;
}

bool binary_to_compressed_c(const char* filename, const char* symbol, bool use_base85_encoding, bool use_compression)
{
    // Read file
    FILE* f = fopen(filename, "rb");
    if (!f) return false;
    int data_sz;
    if (fseek(f, 0, SEEK_END) || (data_sz = (int)ftell(f)) == -1 || fseek(f, 0, SEEK_SET)) { fclose(f); return false; }
    char* data = new char[data_sz+4];
    if (fread(data, 1, data_sz, f) != (size_t)data_sz) { fclose(f); delete[] data; return false; }
    memset((void *)(((char*)data) + data_sz), 0, 4);
    fclose(f);

    // Compress
    //int maxlen = data_sz + 512 + (data_sz >> 2) + sizeof(int); // total guess
    int maxlen = compressBound(data_sz);
    char* compressed = use_compression ? new char[maxlen] : data;
    int compressed_sz = use_compression ? stb_compress((stb_uchar*)compressed, (stb_uchar*)data, data_sz) : data_sz;
    if (use_compression)
		memset(compressed + compressed_sz, 0, maxlen - compressed_sz);

    // Output as Base85 encoded
    FILE* out = stdout;
    fprintf(out, "// File: '%s' (%d bytes)\n", filename, (int)data_sz);
    fprintf(out, "// Exported using binary_to_compressed_c.cpp\n");
	const char* compressed_str = use_compression ? "compressed_" : "";
    if (use_base85_encoding)
    {
        fprintf(out, "static const char %s_%sdata_base85[%d+1] =\n    \"", symbol, compressed_str, (int)((compressed_sz+3)/4)*5);
        char prev_c = 0;
        for (int src_i = 0; src_i < compressed_sz; src_i += 4)
        {
            // This is made a little more complicated by the fact that ??X sequences are interpreted as trigraphs by old C/C++ compilers. So we need to escape pairs of ??.
            unsigned int d = *(unsigned int*)(compressed + src_i);
            for (unsigned int n5 = 0; n5 < 5; n5++, d /= 85)
            {
                char c = Encode85Byte(d);
                fprintf(out, (c == '?' && prev_c == '?') ? "\\%c" : "%c", c);
                prev_c = c;
            }
            if ((src_i % 112) == 112-4)
                fprintf(out, "\"\n    \"");
        }
        fprintf(out, "\";\n\n");
    }
    else
    {
        fprintf(out, "static const unsigned int %s_%ssize = %d;\n", symbol, compressed_str, (int)compressed_sz);
        fprintf(out, "static const unsigned int %s_%sdata[%d/4] =\n{", symbol, compressed_str, (int)((compressed_sz+3)/4)*4);
        int column = 0;
        for (int i = 0; i < compressed_sz; i += 4)
        {
            unsigned int d = *(unsigned int*)(compressed + i);
            if ((column++ % 12) == 0)
                fprintf(out, "\n    0x%08x, ", d);
            else
                fprintf(out, "0x%08x, ", d);
        }
        fprintf(out, "\n};\n\n");
    }

    // Cleanup
    delete[] data;
    if (use_compression)
	    delete[] compressed;
    return true;
}