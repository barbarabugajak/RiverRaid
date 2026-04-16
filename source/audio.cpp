#include "audio.h"
#include "globals.h"
#include <iostream>

ma_decoder explosionDecoder;
ma_int16 buffer_music[4800];
ma_int16 buffer_explosion[4800];

ma_decoder pDecoder;
ma_device device;

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
	ma_int16* output = (ma_int16*)(pOutput);

	ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;

	ma_uint64 framesRead = 0;
	ma_uint64 explosionFramesRead = 0;

	ma_result result = ma_decoder_read_pcm_frames(pDecoder, buffer_music, frameCount, &framesRead);

	if (framesRead < frameCount) {
		ma_decoder_seek_to_pcm_frame(pDecoder, 0);

		ma_uint64 extraFramesRead = 0;
		ma_decoder_read_pcm_frames(pDecoder,
			output + framesRead,
			frameCount - framesRead,
			&extraFramesRead);

		framesRead = +extraFramesRead;
	}


	for (int i = 0; i < framesRead * 2; i++) {
		output[i] = (ma_int16)(buffer_music[i] * 0.25f);
	}

	if (bIsExploding) {

		result = ma_decoder_read_pcm_frames(&explosionDecoder, buffer_explosion, frameCount, &explosionFramesRead);

		if (explosionFramesRead < frameCount) {
			bIsExploding = false;
			ma_decoder_seek_to_pcm_frame(&explosionDecoder, 0);
		}

		if (!bIsExploding) return;

		for (int i = 0; i < framesRead * 2; i++) {
			output[i] += (ma_int16)(buffer_explosion[i] * 0.25f);
		}
	}
}

int InitalizeAudio() {
	ma_device_config config = ma_device_config_init(ma_device_type_playback);

	config.playback.format = ma_format_s16;
	config.playback.channels = 2;
	config.sampleRate = 48000;
	config.dataCallback = data_callback;
	config.pUserData = &pDecoder;

	if (ma_device_init(NULL, &config, &device) != MA_SUCCESS) {
		std::cout << "\n Audio device initialization failed \n";
		return -1;
	}

	const char* BACKGROUND_MUSIC_ASSET_PATH = "assets/audio/background-music.wav";
	ma_result fileResult = ma_decoder_init_file(BACKGROUND_MUSIC_ASSET_PATH, NULL, &pDecoder);
	if (fileResult != MA_SUCCESS) {
		std::cout << "\n Wav import errors: " << fileResult << "\n";
		return -1;
	}

	const char* EXPLOSION_SOUND_ASSET_PATH = "assets/audio/explosion_sound.wav";
	fileResult = ma_decoder_init_file(EXPLOSION_SOUND_ASSET_PATH, NULL, &explosionDecoder);
	if (fileResult != MA_SUCCESS) {
		std::cout << "\n Wav import errors: " << fileResult << "\n";
		return -1;
	}

	ma_data_source_set_looping(&pDecoder, MA_TRUE);

	ma_device_start(&device);

	return 1;
}

void ShutdownAudio() {
	ma_decoder_uninit(&pDecoder);
	ma_device_uninit(&device);
}