#include "AudioDecoder.hpp"
#include "libavcodec/avcodec.h"
#include "libavcodec/packet.h"
#include "libavutil/frame.h"
#include "libavutil/mathematics.h"
#include "libavutil/samplefmt.h"
#include "libswresample/swresample.h"
#include <cstdint>

void AudioDecoder::clean() {
    if (swrContext) {
        swr_free(&swrContext);
    }
    if (codecContext) {
        avcodec_free_context(&codecContext);
    }
}

void AudioDecoder::decodeAudioPacket(AVPacket *packet) {
    // 发送packet给decode
    if (avcodec_send_packet(codecContext, packet) == 0) {
        av_packet_free(&packet);
        auto frame = av_frame_alloc();
        if (avcodec_receive_frame(codecContext, frame) == 0) {
            int64_t out_nb_samples =
                av_rescale_rnd(swr_get_delay(swrContext, frame->sample_rate) +
                                   frame->nb_samples,
                               44100, frame->sample_rate, AV_ROUND_UP);
            // 将音频帧转换成pcm
            // convertedSize：转换后音频数据的大小
            int convertedSize =
                swr_convert(swrContext,                    // 转换工具?
                            &convertedAudioBuffer,         // 输出
                            out_nb_samples,                // 输出大小
                            (uint8_t const **)frame->data, // 输入
                            frame->nb_samples);            // 输入大小

            if (convertedSize > 0) {
                int bufferSize = av_samples_get_buffer_size(
                    nullptr, frame->ch_layout.nb_channels, convertedSize,
                    AV_SAMPLE_FMT_S16, 1);
                double framePts = time_base_q2d_ms * frame->pts;
                // 将转化后的数据发送到音频io设备
                emit sendAudioBuffer(convertedAudioBuffer, bufferSize,
                                     framePts);
                av_frame_free(&frame);
            }
        }
    }
    packetIsUsed = true;
}
