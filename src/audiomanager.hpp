#pragma once
#ifndef _audiomanager_hpp
#define _audiomanager_hpp

#include "common.hpp"

class audiomanager {
public:
  audiomanager() = default;
  virtual ~audiomanager() = default;

  void preload(const std::vector<std::string> &filename) {}

  void play(std::string_view filename) {

    // // https://stackoverflow.com/questions/55438697/playing-sound-from-a-video-using-ffmpeg-and-sdl-queueaudio-results-in-high-pitch

    // const auto codec = avcodec_find_decoder(AV_CODEC_ID_AAC);
    // if (!codec) {
    //   throw std::runtime_error(fmt::format("[avcodec_find_decoder] error finding decoder for file: {}. reason: {}", name, strerror(errno)));
    // }

    // const auto parser = av_parser_init(codec->id);
    // if (!parser) {
    //   throw std::runtime_error(fmt::format("[av_parser_init] error initializing parser for file: {}. reason: {}", name, strerror(errno)));
    // }

    // const auto ctx = avcodec_alloc_context3(codec);
    // if (!ctx) {
    //   throw std::runtime_error(fmt::format("[avcodec_alloc_context3] error allocating codec context for file: {}. reason: {}", name, strerror(errno)));
    // }

    // std::cout << "codec: " << codec->name << std::endl;
    // std::cout << "codec->sample_rate: " << ctx->sample_rate << std::endl;
    // std::cout << "codec->channels: " << ctx->channels << std::endl;

    // SDL_AudioSpec want{}, have{};
    // want.format = AUDIO_S16SYS;
    // want.samples = 1024;
    // want.freq = ctx->sample_rate;
    // want.channels = ctx->channels;
    // // want.freq = ctx->sample_rate;
    // // want.format = AUDIO_S16SYS;
    // // want.channels = ctx->channels;
    // // want.samples = 1024;
    // // want.callback = nullptr;

    // const auto device_id = SDL_OpenAudioDevice(nullptr, 0, &want, &have, 0);
    // if (device_id < 0) {
    //   throw std::runtime_error(fmt::format("[SDL_OpenAudio] error opening audio device. reason: {}", SDL_GetError()));
    // }

    // SDL_PauseAudioDevice(device_id, 0);

    // //     const auto ret = avcodec_open2(ctx, codec, nullptr);
    // //     std::cout << "ret: " << ret << std::endl;
    // //     // if (!ret) {
    // //     //   throw std::runtime_error(fmt::format("[avcodec_open2] error opening codec for file: {}. reason: {}", name, strerror(errno)));
    // //     // }

    // //     const auto f = fopen(name, "rb");
    // //     if (!f) {
    // //       throw std::runtime_error(fmt::format("[fopen] error opening file: {}. reason: {}", name, strerror(errno)));
    // //     }

    // // #define AUDIO_INBUF_SIZE 20480
    // // #define AUDIO_REFILL_THRESH 4096

    // //     uint8_t inbuf[AUDIO_INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];

    // //     uint8_t *data;
    // //     size_t data_size;

    // //     data = inbuf;
    // //     data_size = fread(inbuf, 1, AUDIO_INBUF_SIZE, f);
    // //     AVPacket *pkt;
    // //     pkt = av_packet_alloc();

    // //     AVFrame *decoded_frame = NULL;
    // //     int len;
    // //     while (data_size > 0) {
    // //       if (!decoded_frame) {
    // //         if (!(decoded_frame = av_frame_alloc())) {
    // //           fprintf(stderr, "Could not allocate audio frame\n");
    // //           exit(1);
    // //         }
    // //       }

    // //       auto ret = av_parser_parse2(parser, ctx, &pkt->data, &pkt->size, data, data_size, AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);
    // //       if (ret < 0) {
    // //         fprintf(stderr, "Error while parsing\n");
    // //         exit(1);
    // //       }
    // //       data += ret;
    // //       data_size -= ret;

    // //       if (pkt->size) {
    // //         // decode(c, pkt, decoded_frame, outfile);
    // //         ret = avcodec_send_packet(ctx, pkt);
    // //         if (ret < 0) {
    // //           fprintf(stderr, "Error submitting the packet to the decoder\n");
    // //           exit(1);
    // //         }

    // //         ret = avcodec_receive_frame(ctx, decoded_frame);
    // //         if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
    // //           return;
    // //         else if (ret < 0) {
    // //           fprintf(stderr, "Error during decoding\n");
    // //           exit(1);
    // //         }
    // //         data_size = av_get_bytes_per_sample(ctx->sample_fmt);
    // //         if (data_size < 0) {
    // //           /* This should not occur, checking just for paranoia */
    // //           fprintf(stderr, "Failed to calculate data size\n");
    // //           exit(1);
    // //         }
    // //         for (auto i = 0; i < decoded_frame->nb_samples; i++) {
    // //           for (auto ch = 0; ch < ctx->ch_layout.nb_channels; ch++) {
    // //             // fwrite(frame->data[ch] + data_size * i, 1, data_size, outfile);
    // //             std::cout << "device: " << device << "frame->data[ch] + data_size * i: " << decoded_frame->data[ch] + data_size * i << std::endl;
    // //             SDL_QueueAudio(device, decoded_frame->data[ch], data_size);
    // //           }
    // //         }
    // //       }
    // //       // std::cout << "pkt->size: " << pkt->size << std::endl;
    // //     }

    // //     if (data_size < AUDIO_REFILL_THRESH) {
    //       memmove(inbuf, data, data_size);
    //       data = inbuf;
    //       len = fread(data + data_size, 1,
    //                   AUDIO_INBUF_SIZE - data_size, f);
    //       if (len > 0)
    //         data_size += len;
    //     }
  }
};
// Begin

// https://ffmpeg.org/doxygen/trunk/decode_audio_8c-example.html
/*
AVFormatContext *ctx = avformat_alloc_context();
if (avformat_open_input(&ctx, arquivo, nullptr, nullptr) != 0) {
  throw std::runtime_error(fmt::format("[avformat_open_input] error opening file: {}. reason: {}", arquivo, strerror(errno)));
}

if (avformat_find_stream_info(ctx, nullptr) < 0) {
  throw std::runtime_error(fmt::format("[avformat_find_stream_info] error finding stream information for file: {}. reason: {}", arquivo, strerror(errno)));
}

auto index = -1;
for (auto i = 0; i < ctx->nb_streams; i++) {
  if (ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO && ctx->streams[i]->codecpar->codec_id == AV_CODEC_ID_AAC) {
    index = i;
    break;
  }
}

if (index == -1) {
  throw std::runtime_error(fmt::format("[avformat_find_stream_info] error finding audio stream for file: {}. reason: {}", arquivo, strerror(errno)));
}

const auto codec = avcodec_find_decoder(ctx->streams[index]->codecpar->codec_id);
if (!codec) {
  throw std::runtime_error(fmt::format("[avcodec_find_decoder] error finding decoder for file: {}. reason: {}", arquivo, strerror(errno)));
}

const auto codecContext = avcodec_alloc_context3(codec);
if (avcodec_open2(codecContext, codec, nullptr) < 0) {
  throw std::runtime_error(fmt::format("[avcodec_open2] error opening codec for file: {}. reason: {}", arquivo, strerror(errno)));
}

std::cout << "codecContext->channels: " << codecContext->channels << std::endl;

SDL_AudioSpec desired, obtained;
desired.freq = codecContext->sample_rate;
desired.format = AUDIO_S16SYS;
desired.channels = codecContext->channels;
desired.samples = 1024;
desired.callback = nullptr;

if (SDL_OpenAudio(&desired, &obtained) < 0) {
  throw std::runtime_error(fmt::format("[SDL_OpenAudio] error opening audio device for file: {}. reason: {}", arquivo, SDL_GetError()));
}



std::cout << "freq: " << obtained.freq << std::endl;
std::cout << "format: " << obtained.format << std::endl;
std::cout << "channels: " << obtained.channels << std::endl;
std::cout << "samples: " << obtained.samples << std::endl;

AVPacket packet;
while (av_read_frame(ctx, &packet) >= 0) {
  if (packet.stream_index == index) {
    AVFrame *frame = av_frame_alloc();
    int got_frame;
    avcodec_decode_audio4(codecContext, frame, &got_frame, &packet);
    if (got_frame) {
      SDL_QueueAudio(1, frame->data[0], frame->linesize[0]);
    }
    av_frame_free(&frame);
  }
  // if (packet.stream_index == audioStream)
  //   packet_queue_put(&audioq, &packet);
  // else
  std::cout << "packet.stream_index: " << packet.stream_index << std::endl;
  // av_free_packet(&packet);
}
*/
// AVPacket packet;
// av_init_packet(&packet);
// SDL_PauseAudio(0);

// bool isPlanar = av_sample_fmt_is_planar(static_cast<AVSampleFormat>(packet->audioFrame->format)) == 1;
// std::cout << "isPlanar: " << isPlanar << std::endl;

//   const auto codec = avcodec_find_decoder(formatContext->streams[stream_index]->codecpar->codec_id);
//   if (!codec) {
//     fprintf(stderr, "Não foi possível encontrar o codec para AAC.\n");
//     return -1;
//   }

//   AVCodecContext *codecContext = avcodec_alloc_context3(codec);
//   if (avcodec_open2(codecContext, codec, NULL) < 0) {
//     fprintf(stderr, "Não foi possível abrir o codec.\n");
//     return -1;
//   }

//   // Configure o contexto de áudio SDL
//   SDL_AudioSpec desejado, obtido;
//   desejado.freq = codecContext->sample_rate;
//   desejado.format = AUDIO_S16SYS;
//   desejado.channels = codecContext->channels;
//   desejado.samples = 1024; // Escolha um valor adequado para o tamanho do buffer
//   desejado.callback = NULL;

//   if (SDL_OpenAudio(&desejado, &obtido) < 0) {
//     fprintf(stderr, "Erro ao abrir o dispositivo de áudio: %s\n", SDL_GetError());
//     return -1;
//   }

//   // Leitura e decodificação de frames AAC
//   AVPacket pacote;
//   av_init_packet(&pacote);
//   SDL_PauseAudio(0); // Inicie a reprodução

//   while (av_read_frame(formatContext, &pacote) >= 0) {
//     if (pacote.stream_index == stream_index) {
//       AVFrame *frame = av_frame_alloc();
//       int got_frame;
//       // avcodec_decode_audio4(codecContext, frame, &got_frame, &pacote);
//       if (got_frame) {
//         SDL_QueueAudio(1, frame->data[0], frame->linesize[0]);
//       }
//       av_frame_free(&frame);
//     }
//     av_packet_unref(&pacote);
//   }

#endif