#ifndef WavHeader
#define WavHeader

typedef struct wav_header 
{
    // RIFF Header
    char riff_header[4];        // "RIFF"
    int wav_size;               // RIFF Chunk size 
    char wave_header[4];        // Wave Header 

    // Header information
    char fmt_header[4];         // "FMT"
    int fmt_chunk_size;         // FMT Chunk size
    short audio_format;         // Audio format: 1=PCM, 6=mulaw, 7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM 
    short num_channels;         // Number of channels: 1=Mono 2=Sterio
    int sample_rate;            // Sampling Frequency
    int byte_rate;              // bytes per second: sample_rate * num_channels * bytes per sample
    short sample_alignment;     // num_channels * bytes per sample 
    short bit_depth;            // Number of bits per sample 

    // Data
    char data_header[4];        // 
    int data_bytes;             // 

} wav_header;
#endif 
