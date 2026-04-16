#pragma once
#include "../libs/miniaudio/miniaudio.h"

extern ma_decoder explosionDecoder;
extern ma_int16 buffer_music[4800];
extern ma_int16 buffer_explosion[4800];

extern ma_decoder pDecoder;
extern ma_device device;

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
int InitalizeAudio();
void ShutdownAudio();