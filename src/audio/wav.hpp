#ifndef MOGE_SRC_AUDIO_WAV_HPP_INCLUDED
#define MOGE_SRC_AUDIO_WAV_HPP_INCLUDED

#include <assert.h>
#include <stdint.h>

namespace moge {

struct AudioWav {

  struct RiffChunk {
    char chunk_id[4]; // "RIFF"
    uint32_t chunk_size;
    char form_type[4]; // "WAVE"

    struct FmtChunk {
      char chunk_id[4];    // "fmt "
      uint32_t chunk_size; // 16
      uint16_t wave_format_type;
      uint16_t channel;
      uint32_t samples_per_sec;
      uint32_t bytes_per_sec;
      uint16_t block_size;
      uint16_t bits_per_sample;
    } fmt_chunk;

    struct DataChunk {
      char chunk_id[4]; // "data"
      uint32_t chunk_size;
    } data_chunk;

  } riff_chunk;

  const uint8_t* data;
};

void wav_init(moge::AudioWav* wav, const uint8_t* data) {
  assert(wav);
  assert(sizeof(AudioWav::RiffChunk) == 44);

  auto _read = [](uint8_t* dst, const uint8_t* src, size_t num_bytes) {
    for (size_t i = 0; i < num_bytes; ++i) {
      dst[i] = src[i];
    }
  };

  _read((uint8_t*)&wav->riff_chunk, data, sizeof(AudioWav::RiffChunk));

  wav->data = &data[45];
}

} // namespace moge

#endif // MOGE_SRC_AUDIO_WAV_HPP_INCLUDED
