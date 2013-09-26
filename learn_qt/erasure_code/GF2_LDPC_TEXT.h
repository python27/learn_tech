#ifndef GF2_LDPC_TEXT_INCLUDE
#define GF2_LDPC_TEXT_INCLUDE

#include <iostream>
#include <string>

using namespace std;

void LDPCEncodeText(const char* filename);

void LDPCDecodeText(const char* filename, double p);

#endif // GF2_LDPC_TEXT_INCLUDE