////#include <iostream>
////#include <string>
////#include <memory>
////#include <thread>
////#include "pch.h"

////using namespace std;

////AVFormatContext *inputContext = nullptr;
////AVFormatContext *outputContext;
////int64_t lastReadPacktTime;
////int64_t packetCount = 0;
////#define STREAM_PIX_FMT    AV_PIX_FMT_YUV420P /* default pix_fmt */

////static int interrupt_cb(void *ctx)
////{
////    int timeout = 3;
////    if(av_gettime() - lastReadPacktTime > timeout * 1000 * 1000)
////    {
////        return -1;
////    }
////    return 0;
////}

////int openInput(string inputUrl)
////{
////    inputContext = avformat_alloc_context();
////    lastReadPacktTime = av_gettime();
////    inputContext->interrupt_callback.callback = interrupt_cb;

////    AVInputFormat *ifmt = av_find_input_format("video4linux2");
////    AVDictionary *format_opts = nullptr;
////    av_dict_set_int(&format_opts,"rtbufsize",18432000, 0);

////    int ret = avformat_open_input(&inputContext, inputUrl.c_str(),ifmt, &format_opts);
////    if(ret < 0)
////    {
////        av_log(NULL, AV_LOG_ERROR, "Input file open input failed\n");
////        return ret;
////    }
////    ret = avformat_find_stream_info(inputContext, nullptr);
////    if(ret < 0)
////    {
////        av_log(NULL, AV_LOG_ERROR, "Find input file stream inform failed\n");
////    }else {
////        av_log(NULL, AV_LOG_FATAL, "Open input file %s success\n", inputUrl.c_str());
////    }
////    int videoindex = -1;
////    for(int i=0; i<inputContext->nb_streams; i++){//find video stream index
////        if(inputContext->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO){
////            videoindex=i;
////            break;
////        }
////        if(i == inputContext->nb_streams-1){
////            printf("Couldn't find a video stream.\n");
////            return -1;
////        }
////    }
////    return videoindex;
////}

////shared_ptr<AVPacket> ReadPacketFromSource()
////{
////    shared_ptr<AVPacket> packet(static_cast<AVPacket *>(av_malloc(sizeof(AVPacket))),[&](AVPacket *p){av_packet_free(&p); av_freep(&p);});
////    av_init_packet(packet.get());
////    lastReadPacktTime = av_gettime();
////    //    packet.get() = av_packet_alloc();
////    int ret = av_read_frame(inputContext, packet.get());
//////    AVFrame *frame = av_frame_alloc();
//////    int got;
//////    ret = avcodec_decode_video2(inputContext->streams[0]->codec,frame,&got,packet.get());
////    if(ret >= 0){
////        return packet;
////        cout<<"packet\n";
////    }else {
////        return nullptr;
////    }
////}

////int OpenOutput(string outUrl, AVCodecContext *encodeCodec){
////    int ret = avformat_alloc_output_context2(&outputContext, nullptr, "flv", outUrl.c_str());
////    if(ret < 0){
////        av_log(NULL, AV_LOG_ERROR, "open output context failed\n");
////        goto Error;
////    }
////    cout<<"opensuccess"<<endl;
////    ret = avio_open2(&outputContext->pb, outUrl.c_str(), AVIO_FLAG_WRITE, nullptr, nullptr);
////    if(ret < 0){
////        av_log(NULL, AV_LOG_ERROR, "open avio failed\n");
////        goto Error;
////    }

////    for(int i = 0; i < inputContext->nb_streams; i++){
////        if(inputContext->streams[i]->codecpar->codec_type == AVMediaType::AVMEDIA_TYPE_AUDIO){
////            continue;
////        }
////        AVStream *stream = avformat_new_stream(outputContext, encodeCodec->codec);
////        //        AVCodecContext *inCodecCtx=avcodec_alloc_context3(encodeCodec->codec);
////        ////        ret = avcodec_parameters_to_context(inCodecCtx,inputContext->streams[i]->codecpar);
////        //        if(ret < 0){
////        //            cout<<"dslf\n";
////        //            goto Error;
////        //        }
////        ret = avcodec_parameters_from_context(stream->codecpar, encodeCodec);
////        //        ret = avcodec_copy_context(stream->codec,encodeCodec);
////        if(ret < 0){
////            av_log(NULL, AV_LOG_ERROR, "copy coddec context failed\n");
////            goto Error;
////        }
////    }
////    ret = avformat_write_header(outputContext, nullptr);
////    if(ret < 0){
////        av_log(NULL, AV_LOG_ERROR, "format write header failed\n");
////        goto Error;
////    }

////    av_log(NULL, AV_LOG_FATAL, "Open output file success %s\n", outUrl.c_str());
////    return ret;
////Error:
////    if(outputContext){
////        for(int i = 0; i < outputContext->nb_streams; i++){
////            AVCodecParameters *par = outputContext->streams[i]->codecpar;
////            AVCodec *inCodec=avcodec_find_decoder(par->codec_id);
////            AVCodecContext *inCodecCtx=avcodec_alloc_context3(inCodec);
////            avcodec_parameters_to_context(inCodecCtx,par);
////            avcodec_close(inCodecCtx);
////        }
////        avformat_close_input(&outputContext);
////    }
////    return ret;
////}

////void Init(){
////    av_register_all();
////    avfilter_register_all();
////    avformat_network_init();
////    avdevice_register_all();
////    av_log_set_level(AV_LOG_WARNING);
////}

////void CloseInput(){
////    if(inputContext != nullptr){
////        avformat_close_input(&inputContext);
////    }
////}

////void CloseOutput(){
////    if(outputContext != nullptr){
////        int ret = av_write_trailer(outputContext);
////        for(int i = 0; i < outputContext->nb_streams; i++){
////            AVCodecParameters *par = outputContext->streams[i]->codecpar;
////            AVCodec *inCodec=avcodec_find_decoder(par->codec_id);
////            AVCodecContext *inCodecCtx=avcodec_alloc_context3(inCodec);
////            avcodec_parameters_to_context(inCodecCtx,par);
////            avcodec_close(inCodecCtx);
////        }
////        avformat_close_input(&outputContext);
////    }
////}

////int WritePacket(shared_ptr<AVPacket> packet){
////    auto inputStream = inputContext->streams[packet->stream_index];
////    auto outputStream = outputContext->streams[packet->stream_index];
////    return av_interleaved_write_frame(outputContext, packet.get());
////}

////int InitDecodeContext(AVStream *inputStream){
////    auto codecId = inputStream->codecpar->codec_id;
////    auto codec = avcodec_find_decoder(codecId);
////    if(!codec){
////        return -1;
////    }
////    AVCodecContext *vc = inputStream->codec; // avcodec_alloc_context3(codec);
//////    avcodec_parameters_to_context(vc, inputStream->codecpar);
////    int ret = avcodec_open2(vc, codec, NULL);
////    return ret;
////}

////int initEncoderCodec(AVStream *inputStream, AVCodecContext **encodeContext){
////    AVCodec *picCodec;

////    picCodec = avcodec_find_encoder(AV_CODEC_ID_H264);
////    (*encodeContext) = avcodec_alloc_context3(picCodec);
////    av_opt_set((*encodeContext)->priv_data, "tune", "zerolatency", 0);

////    (*encodeContext)->codec_id = picCodec->id;
////    (*encodeContext)->time_base.num = 1/*inputStream->time_base.num*/;
////    (*encodeContext)->time_base.den = 25/*inputStream->time_base.den*/;
////    (*encodeContext)->pix_fmt = *picCodec->pix_fmts;
////    (*encodeContext)->width = inputStream->codecpar->width;
////    (*encodeContext)->height = inputStream->codecpar->height;
////    (*encodeContext)->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
////    int ret = avcodec_open2((*encodeContext),picCodec,nullptr);
////    if(ret < 0){
////        std::cout<<"open video codec failed\n";
////        return ret;
////    }
////    return 1;
////}

////bool Decode(AVStream *inputStream, AVPacket *packet, AVFrame *frame){
////    int gotFrame = 0;
////    auto hr = avcodec_decode_video2(inputStream->codec, frame, &gotFrame, packet);
////    if(hr >= 0 && gotFrame != 0){
////        return true;
////    }
////    return false;
////}

////std::shared_ptr<AVPacket> Encode(AVCodecContext *encodeContext, AVFrame *frame, AVPacket *pack){
////    int gotOutput = 0;
////    std::shared_ptr<AVPacket> pkt(static_cast<AVPacket*>(av_malloc(sizeof (AVPacket))),[&](AVPacket *p){av_packet_free(&p);av_freep(&p);});
////    av_init_packet(pkt.get());
////    pkt->data = NULL;
////    pkt->size = 0;
////    frame->pts = frame->pkt_dts = frame->pkt_pts =30 *packetCount;
////    packetCount++;

////        int ret = avcodec_encode_video2(encodeContext, pkt.get(), frame, &gotOutput);
//////    int ret = avcodec_send_frame(encodeContext,frame);
//////    ret = avcodec_receive_packet(encodeContext,pack);
////    if(ret >= 0 && gotOutput){
////        return pkt;
////    }else {
////        return nullptr;
////    }
////}

////int main()
////{
////    Init();
////    int ret = openInput("/dev/video0");

////    AVCodecContext *encodeContext = nullptr;
////    AVFrame *videoFrame = av_frame_alloc();
////    AVFrame *pframe = av_frame_alloc();
////    if(ret >= 0){
////        InitDecodeContext(inputContext->streams[ret]);
////        initEncoderCodec(inputContext->streams[ret],&encodeContext);
////    }
////    AVCodecContext *codecContext = inputContext->streams[ret]->codec;
////    if(ret >= 0){
////        ret = OpenOutput("rtmp://localhost/videotest", encodeContext);
////    }
////    if(ret < 0){
////        CloseInput();
////        CloseOutput();

////        while (true) {
////            this_thread::sleep_for(chrono::seconds(100));
////        }
////        return 0;
////    }
////    while (true) {
////        AVPacket *pack1 = av_packet_alloc();
////        auto packet = ReadPacketFromSource();
////        if(packet && packet->stream_index == 0){
////            AVCodec *codec = avcodec_find_decoder(inputContext->streams[packet->stream_index]->codecpar->codec_id);
////            AVCodecContext *context = avcodec_alloc_context3(codec);
////            int got;
//////            cout<<avcodec_decode_video2(codecContext,videoFrame,&got,pack)<<endl;
////            cout<<avcodec_send_packet(codecContext,packet.get())<<endl;
////            cout<<avcodec_receive_frame(codecContext,videoFrame)<<endl;
////            cout<<packetCount<<endl;
////            struct SwsContext *img_convert_ctx = sws_getContext(codecContext->width, codecContext->height, codecContext->pix_fmt, codecContext->width, codecContext->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
////            pframe->format = encodeContext->pix_fmt;
////            pframe->width  = encodeContext->width;
////            pframe->height = encodeContext->height;
////            ret = av_frame_get_buffer(pframe, 32);  //为音频或视频数据分配新的缓冲区。
////            if (ret < 0) {
////                fprintf(stderr, "Could not allocate frame data.\n");
////                exit(1);
////            }
////            if (av_frame_make_writable(pframe) < 0)cout<<"dslf"<<endl;
////            sws_scale(img_convert_ctx, (const unsigned char* const*)videoFrame->data, videoFrame->linesize, 0, videoFrame->height, pframe->data,  pframe->linesize);
//////            pframe->pts = pframe->pkt_dts = pframe->pkt_pts =40 *packetCount;
//////            av_opt_set(encodeContext->priv_data, "tune", "zerolatency", 0);
//////            cout<<avcodec_send_frame(encodeContext,pframe)<<endl;
//////            cout<<avcodec_receive_packet(encodeContext,pack1)<<endl;
//////            int gotOutput = 0;
//////            ret = avcodec_encode_video2(encodeContext, pack1, pframe, &gotOutput);
////            //            Decode(inputContext->streams[packet.get()->stream_index],packet.get(),videoFrame);
////            auto packetEncode = Encode(encodeContext, pframe, packet.get());
////            if(packetEncode){
////                ret = WritePacket(packetEncode);
////                cout<<"ret: "<<ret<<endl;
////            }
////        }
////    }
////    cout<<"Get Picture End"<<endl;
////    av_frame_free(&videoFrame);
////    avcodec_close(encodeContext);
////    CloseInput();
////    CloseOutput();

////    while (true) {
////        this_thread::sleep_for(chrono::seconds(100));
////    }
////    return 0;
////}



































//#include <stdlib.h>
//#include <stdio.h>
//#include <iostream>
//#include <string.h>
//#include <math.h>
//#include <time.h>
//#include <fcntl.h>
//#include <poll.h>
//#include <pthread.h>
//#include <signal.h>
//#include <unistd.h>
//extern "C"{
//    #include <libavutil/avassert.h>
//    #include <libavutil/channel_layout.h>
//    #include <libavutil/opt.h>
//    #include <libavutil/mathematics.h>
//    #include <libavutil/timestamp.h>
//    #include <libavformat/avformat.h>
//    #include <libswscale/swscale.h>
//    #include <libswresample/swresample.h>
//    #include <libavcodec/avcodec.h>
//    #include <libavcodec/packet.h>
//}

//#include <sys/ioctl.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <sys/mman.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <arpa/inet.h>
//#include <linux/videodev2.h>
//#include <alsa/asoundlib.h>


////推流的服务器地址
//#define RTMP_SERVE_RADDR  "rtmp://localhost/videotest/"

//#define STREAM_DURATION   10000.0   /*录制10秒的视频，由于缓冲的原因，一般只有8秒*/
//#define STREAM_FRAME_RATE 25     /* 15 images/s   avfilter_get_by_name */
//#define STREAM_PIX_FMT    AV_PIX_FMT_YUV420P /* default pix_fmt */
//#define SCALE_FLAGS SWS_BICUBIC

////固定摄像头输出画面的尺寸
//#define VIDEO_WIDTH  1280
//#define VIDEO_HEIGHT 720

////存放从摄像头读出转换之后的数据
//unsigned char YUV420P_Buffer[VIDEO_WIDTH*VIDEO_HEIGHT*3/2];
//unsigned char YUV420P_Buffer_temp[VIDEO_WIDTH*VIDEO_HEIGHT*3/2];

///*一些摄像头需要使用的全局变量*/
//unsigned char *image_buffer[4];
//int video_fd;
//pthread_mutex_t mutex;
//pthread_cond_t cond;

///*一些audio需要使用的全局变量*/
//pthread_mutex_t mutex_audio;

//extern int capture_audio_data_init( char *audio_dev);
//extern int capture_audio_data(snd_pcm_t *capture_handle,int buffer_frames);
///*
// 进行音频采集，采集pcm数据并直接保存pcm数据
// 音频参数：
//     声道数：		2
//     采样位数：	16bit、LE格式
//     采样频率：	44100Hz
//*/
//#define AudioFormat SND_PCM_FORMAT_S16_LE  //指定音频的格式,其他常用格式：SND_PCM_FORMAT_U24_LE、SND_PCM_FORMAT_U32_LE
//#define AUDIO_CHANNEL_SET   2  			  //1单声道   2立体声
//#define AUDIO_RATE_SET 48000   //音频采样率,常用的采样频率: 44100Hz 、16000HZ、8000HZ、48000HZ、22050HZ
//FILE *pcm_data_file=NULL;

//int buffer_frames;
//snd_pcm_t *capture_handle;
//snd_pcm_format_t format=AudioFormat;


////保存音频数据链表
//struct AUDIO_DATA
//{
//    unsigned char* audio_buffer;
//    struct AUDIO_DATA *next;
//};

////定义一个链表头
//struct AUDIO_DATA *list_head=NULL;
//struct AUDIO_DATA *List_CreateHead(struct AUDIO_DATA *head);
//void List_AddNode(struct AUDIO_DATA *head,unsigned char* audio_buffer);
//void List_DelNode(struct AUDIO_DATA *head,unsigned char* audio_buffer);
//int List_GetNodeCnt(struct AUDIO_DATA *head);

//// 单个输出AVStream的包装器
//typedef struct OutputStream {
//    AVStream *st;
//    AVCodecContext *enc;

//    /* 下一帧的点数*/
//    int64_t next_pts;
//    int samples_count;

//    AVFrame *frame;
//    AVFrame *tmp_frame;

//    float t, tincr, tincr2;

//    struct SwsContext *sws_ctx; //图片格式转换
//    struct SwrContext *swr_ctx; //音频格式转换
//} OutputStream;


//static int write_frame(AVFormatContext *fmt_ctx, const AVRational *time_base, AVStream *st, AVPacket *pkt)
//{
//    /*将输出数据包时间戳值从编解码器重新调整为流时基 */
//    av_packet_rescale_ts(pkt, *time_base, st->time_base);
//    pkt->stream_index = st->index;

//    /*将压缩的帧写入媒体文件*/
//    return av_interleaved_write_frame(fmt_ctx, pkt);
//}


///* 添加输出流。 */
//static void add_stream(OutputStream *ost, AVFormatContext *oc,
//                       AVCodec **codec,
//                       enum AVCodecID codec_id)
//{
//    AVCodecContext *c;
//    int i;

//    /* find the encoder */
//    *codec = avcodec_find_encoder(codec_id);
//    if (!(*codec)) {
//        fprintf(stderr, "Could not find encoder for '%s'\n",
//                avcodec_get_name(codec_id));
//        exit(1);
//    }

//    ost->st = avformat_new_stream(oc, NULL);
//    if (!ost->st) {
//        fprintf(stderr, "Could not allocate stream\n");
//        exit(1);
//    }
//    ost->st->id = oc->nb_streams-1;
//    c = avcodec_alloc_context3(*codec);
//    if (!c) {
//        fprintf(stderr, "Could not alloc an encoding context\n");
//        exit(1);
//    }
//    ost->enc = c;

//    switch ((*codec)->type) {
//    case AVMEDIA_TYPE_AUDIO:
//        av_opt_set(c->priv_data, "tune", "zerolatency", 0);
//        c->sample_fmt  = (*codec)->sample_fmts ? (*codec)->sample_fmts[0] : AV_SAMPLE_FMT_S16;
//        c->bit_rate    = 192000;  //设置码率
//        c->sample_rate = 48000;  //音频采样率
//        c->channels= av_get_channel_layout_nb_channels(AV_CH_LAYOUT_STEREO);
//        c->channel_layout = AV_CH_LAYOUT_STEREO;// AV_CH_LAYOUT_MONO 单声道   AV_CH_LAYOUT_STEREO 立体声
//        ost->st->time_base = (AVRational){ 1, c->sample_rate };
//        break;

//    case AVMEDIA_TYPE_VIDEO:
//        av_opt_set(c->priv_data, "tune", "zerolatency", 0);
//        c->codec_id = codec_id;
//        //码率：影响体积，与体积成正比：码率越大，体积越大；码率越小，体积越小。
//        c->bit_rate = 400000; //设置码率 400kps
//        /*分辨率必须是2的倍数。 */
//        c->width    =VIDEO_WIDTH;
//        c->height   = VIDEO_HEIGHT;
//        /*时基：这是基本的时间单位（以秒为单位）
//         *表示其中的帧时间戳。 对于固定fps内容，
//         *时基应为1 / framerate，时间戳增量应为
//         *等于1。*/
//        ost->st->time_base = (AVRational){1,STREAM_FRAME_RATE};
//        c->time_base       = ost->st->time_base;
//        c->gop_size      = 12; /* 最多每十二帧发射一帧I帧 */
//        c->pix_fmt       = STREAM_PIX_FMT;
//        c->max_b_frames = 0;  //不要B帧
//        if (c->codec_id == AV_CODEC_ID_MPEG1VIDEO)
//        {
//            c->mb_decision = 2;
//        }
//        break;

//    default:
//        break;
//    }

//    /* 某些格式希望流头分开。 */
//    if (oc->oformat->flags & AVFMT_GLOBALHEADER)
//        c->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
//}

///**************************************************************/
///* audio output */

//static AVFrame *alloc_audio_frame(enum AVSampleFormat sample_fmt,
//                                  uint64_t channel_layout,
//                                  int sample_rate, int nb_samples)
//{
//    AVFrame *frame = av_frame_alloc();
//    frame->format = sample_fmt;
//    frame->channel_layout = channel_layout;
//    frame->sample_rate = sample_rate;
//    frame->nb_samples = nb_samples;
//    if(nb_samples)
//    {
//        av_frame_get_buffer(frame, 0);
//    }
//    return frame;
//}

//static void open_audio(AVFormatContext *oc, AVCodec *codec, OutputStream *ost, AVDictionary *opt_arg)
//{
//    AVCodecContext *c;
//    int nb_samples;
//    int ret;
//    AVDictionary *opt = NULL;
//    c = ost->enc;
//    av_dict_copy(&opt, opt_arg, 0);
//    ret = avcodec_open2(c, codec, &opt);
//    if(ret < 0){
//        printf("open faile\n");
//    }
//    av_dict_free(&opt);


//    /*下面3行代码是为了生成虚拟的声音设置的频率参数*/
//    ost->t     = 0;
//    ost->tincr = 2 * M_PI * 110.0 / c->sample_rate;
//    ost->tincr2 = 2 * M_PI * 110.0 / c->sample_rate / c->sample_rate;

//    //AAC编码这里就固定为1024
//    nb_samples = c->frame_size;

//    ost->frame     = alloc_audio_frame(c->sample_fmt, c->channel_layout,
//                                       c->sample_rate, nb_samples);
//    ost->tmp_frame = alloc_audio_frame(AV_SAMPLE_FMT_S16, c->channel_layout,
//                                       c->sample_rate, nb_samples);

//    /* copy the stream parameters to the muxer */
//    avcodec_parameters_from_context(ost->st->codecpar, c);

//    /* create resampler context */
//    ost->swr_ctx = swr_alloc();

//    /* set options */
//    printf("c->channels=%d\n",c->channels);
//    av_opt_set_int       (ost->swr_ctx, "in_channel_count",   c->channels,       0);
//    av_opt_set_int       (ost->swr_ctx, "in_sample_rate",     c->sample_rate,    0);
//    av_opt_set_sample_fmt(ost->swr_ctx, "in_sample_fmt",      AV_SAMPLE_FMT_S16, 0);
//    av_opt_set_int       (ost->swr_ctx, "out_channel_count",  c->channels,       0);
//    av_opt_set_int       (ost->swr_ctx, "out_sample_rate",    c->sample_rate,    0);
//    av_opt_set_sample_fmt(ost->swr_ctx, "out_sample_fmt",     c->sample_fmt,     0);

//    /* initialize the resampling context */
//    swr_init(ost->swr_ctx);
//}

///* 毫秒级 延时 */
//void Sleep(int ms)
//{
//    struct timeval delay;
//    delay.tv_sec = 0;
//    delay.tv_usec = ms * 1000; // 20 ms
//    select(0, NULL, NULL, NULL, &delay);
//}


///*
//准备虚拟音频帧
//这里可以替换成从声卡读取的PCM数据
//*/
//static AVFrame *get_audio_frame(OutputStream *ost)
//{
//    AVFrame *frame = ost->tmp_frame;
//    int j, i, v;
//    int16_t *q = (int16_t*)frame->data[0];
//    /* 检查我们是否要生成更多帧，用于判断是否结束*/
//    if (av_compare_ts(ost->next_pts, ost->enc->time_base,STREAM_DURATION, (AVRational){ 1, 1 }) >= 0)
//        return NULL;

//#if 1
//    //获取链表节点数量
//    int cnt=0;
//    while(cnt<=0)
//    {
//        cnt=List_GetNodeCnt(list_head);
//    }

//    pthread_mutex_lock(&mutex_audio); /*互斥锁上锁*/

//    //得到节点数据
//    struct AUDIO_DATA *tmp=list_head;
//    unsigned char *buffer;

//    tmp=tmp->next;
//    if(tmp==NULL)
//    {
//        printf("数据为NULL.\n");
//        exit(0);
//    }
//    buffer=tmp->audio_buffer;

//    //1024*16*1
//    memcpy(q,buffer,frame->nb_samples*sizeof(int16_t)*ost->enc->channels);//将音频数据拷贝进入frame缓冲区

//    List_DelNode(list_head,buffer);
//    free(buffer);
//    pthread_mutex_unlock(&mutex_audio); /*互斥锁解锁*/
//#endif

//    frame->pts = ost->next_pts;
//    ost->next_pts  += frame->nb_samples;
//    return frame;
//}


///*
// *编码一个音频帧并将其发送到多路复用器
// *编码完成后返回1，否则返回0
// */
//static int write_audio_frame(AVFormatContext *oc, OutputStream *ost)
//{
//    AVCodecContext *c;
//    AVPacket pkt = { 0 };
//    AVFrame *frame;
//    int ret;
//    int got_packet;
//    int dst_nb_samples;

//    av_init_packet(&pkt);
//    c = ost->enc;

//    frame = get_audio_frame(ost);

//    if(frame)
//    {
//        /*使用重采样器将样本从本机格式转换为目标编解码器格式*/
//        /*计算样本的目标数量*/
//        dst_nb_samples = av_rescale_rnd(swr_get_delay(ost->swr_ctx, c->sample_rate) + frame->nb_samples,
//                                        c->sample_rate, c->sample_rate, AV_ROUND_UP);
//        av_assert0(dst_nb_samples == frame->nb_samples);
//        av_frame_make_writable(ost->frame);
//        /*转换为目标格式 */
//        swr_convert(ost->swr_ctx,
//                    ost->frame->data, dst_nb_samples,
//                    (const uint8_t **)frame->data, frame->nb_samples);
//        frame = ost->frame;
//        frame->pts = av_rescale_q(ost->samples_count, (AVRational){1, c->sample_rate}, c->time_base);
//        ost->samples_count += dst_nb_samples;
//    }

//    avcodec_encode_audio2(c, &pkt, frame, &got_packet);

//    if (got_packet)
//    {
//        write_frame(oc, &c->time_base, ost->st, &pkt);
//    }
//    return (frame || got_packet) ? 0 : 1;
//}


//static AVFrame *alloc_picture(enum AVPixelFormat pix_fmt, int width, int height)
//{
//    AVFrame *picture;
//    int ret;
//    picture = av_frame_alloc();
//    picture->format = pix_fmt;
//    picture->width  = width;
//    picture->height = height;

//    /* allocate the buffers for the frame data */
//    av_frame_get_buffer(picture, 32);
//    return picture;
//}


//static void open_video(AVFormatContext *oc, AVCodec *codec, OutputStream *ost, AVDictionary *opt_arg)
//{
//    AVCodecContext *c = ost->enc;
//    AVDictionary *opt = NULL;
//    av_dict_copy(&opt, opt_arg, 0);
//    /* open the codec */
//    avcodec_open2(c, codec, &opt);
//    av_dict_free(&opt);
//    /* allocate and init a re-usable frame */
//    ost->frame = alloc_picture(c->pix_fmt, c->width, c->height);
//    ost->tmp_frame = NULL;
//    /* 将流参数复制到多路复用器 */
//    avcodec_parameters_from_context(ost->st->codecpar, c);
//}


///*
//准备图像数据
//YUV422占用内存空间 = w * h * 2
//YUV420占用内存空间 = width*height*3/2
//*/
//static void fill_yuv_image(AVFrame *pict, int frame_index,int width, int height)
//{
//    int y_size=width*height;
//    /*等待条件成立*/
//    pthread_mutex_lock(&mutex);
//    pthread_cond_wait(&cond,&mutex);
//    memcpy(YUV420P_Buffer_temp,YUV420P_Buffer,sizeof(YUV420P_Buffer));
//    /*互斥锁解锁*/
//    pthread_mutex_unlock(&mutex);

//    //将YUV数据拷贝到缓冲区  y_size=wXh
//    memcpy(pict->data[0],YUV420P_Buffer_temp,y_size);
//    memcpy(pict->data[1],YUV420P_Buffer_temp+y_size,y_size/4);
//    memcpy(pict->data[2],YUV420P_Buffer_temp+y_size+y_size/4,y_size/4);
//}


//static AVFrame *get_video_frame(OutputStream *ost)
//{
//    AVCodecContext *c = ost->enc;

//    /* 检查我们是否要生成更多帧---判断是否结束录制 */
//    if(av_compare_ts(ost->next_pts, c->time_base,STREAM_DURATION, (AVRational){ 1, 1 }) >= 0)
//        return NULL;

//    /*当我们将帧传递给编码器时，它可能会保留对它的引用
//    *内部； 确保我们在这里不覆盖它*/
//    if (av_frame_make_writable(ost->frame) < 0)
//        exit(1);

//    //制作虚拟图像
//    //DTS（解码时间戳）和PTS（显示时间戳）
//    fill_yuv_image(ost->frame, ost->next_pts, c->width, c->height);
//    ost->frame->pts = ost->next_pts++;
//    return ost->frame;
//}

///*
//*编码一个视频帧并将其发送到多路复用器
//*编码完成后返回1，否则返回0
//*/
//static int write_video_frame(AVFormatContext *oc, OutputStream *ost)
//{
//    int ret;
//    AVCodecContext *c;
//    AVFrame *frame;
//    int got_packet = 0;
//    AVPacket *pkt = { 0 };
//    c=ost->enc;
//    //获取一帧数据
//    frame = get_video_frame(ost);
//    pkt = av_packet_alloc();
////    av_init_packet(&pkt);

//    /* 编码图像 */
//    ret=avcodec_encode_video2(c, pkt, frame, &got_packet);

//    if(got_packet)
//    {
//        ret=write_frame(oc, &c->time_base, ost->st, pkt);
//    }
//    else
//    {
//        ret = 0;
//    }
//    return (frame || got_packet) ? 0 : 1;
//}


//static void close_stream(AVFormatContext *oc, OutputStream *ost)
//{
//    avcodec_free_context(&ost->enc);
//    av_frame_free(&ost->frame);
//    av_frame_free(&ost->tmp_frame);
//    sws_freeContext(ost->sws_ctx);
//    swr_free(&ost->swr_ctx);
//}


////编码视频和音频
//int video_audio_encode(char *filename)
//{
//    OutputStream video_st = { 0 }, audio_st = { 0 };
//    AVOutputFormat *fmt;
//    AVFormatContext *oc;
//    AVCodec *audio_codec, *video_codec;
//    int ret;
//    int have_video = 0, have_audio = 0;
//    int encode_video = 0, encode_audio = 0;
//    AVDictionary *opt = NULL;
//    int i;

//    /* 分配输出环境*/
//    avformat_alloc_output_context2(&oc,NULL,"flv",filename);
//    fmt=oc->oformat;
//    //指定编码器
//    fmt->video_codec=AV_CODEC_ID_H264;
//    fmt->audio_codec=AV_CODEC_ID_AAC;

//    /*使用默认格式的编解码器添加音频和视频流，初始化编解码器。 */
//    if(fmt->video_codec != AV_CODEC_ID_NONE)
//    {
//        add_stream(&video_st,oc,&video_codec,fmt->video_codec);
//        have_video = 1;
//        encode_video = 1;
//    }
//    if(fmt->audio_codec != AV_CODEC_ID_NONE)
//    {
//        add_stream(&audio_st, oc, &audio_codec, fmt->audio_codec);
//        have_audio = 1;
//        encode_audio = 1;
//    }

//    /*现在已经设置了所有参数，可以打开音频视频编解码器，并分配必要的编码缓冲区。 */
//    if (have_video)
//        open_video(oc, video_codec, &video_st, opt);

//    if (have_audio)
//        open_audio(oc, audio_codec, &audio_st, opt);

//    av_dump_format(oc, 0, filename, 1);

//    /* 打开输出文件（如果需要） */
//    if(!(fmt->flags & AVFMT_NOFILE))
//    {
//        ret = avio_open(&oc->pb, filename, AVIO_FLAG_WRITE);
//        if (ret < 0)
//        {
//            fprintf(stderr, "无法打开输出文件: '%s':\n", filename);
//            return 1;
//        }
//    }

//    /* 编写流头（如果有）*/
//    avformat_write_header(oc,&opt);

//    while(encode_video || encode_audio)
//    {
//        /* 选择要编码的流*/
//        if(encode_video &&(!encode_audio || av_compare_ts(video_st.next_pts, video_st.enc->time_base,audio_st.next_pts, audio_st.enc->time_base) <= 0))
//        {
//            //printf("视频编码一次----->\n");
//            encode_video = !write_video_frame(oc,&video_st);
//        }
//        else
//        {
//            //printf("音频编码一次----->\n");
//            encode_audio = !write_audio_frame(oc,&audio_st);
//        }
//    }

//    av_write_trailer(oc);

//    if (have_video)
//        close_stream(oc, &video_st);
//    if (have_audio)
//        close_stream(oc, &audio_st);

//    if (!(fmt->flags & AVFMT_NOFILE))
//        avio_closep(&oc->pb);
//    avformat_free_context(oc);
//    return 0;
//}


///*
//函数功能: 摄像头设备初始化
//*/
//int VideoDeviceInit(char *DEVICE_NAME)
//{
//    /*1. 打开摄像头设备*/
//    video_fd=open(DEVICE_NAME,O_RDWR);
//    if(video_fd<0)return -1;

//    /*2. 设置摄像头支持的颜色格式和输出的图像尺寸*/
//    struct v4l2_format video_formt;
//    memset(&video_formt,0,sizeof(struct v4l2_format));
//    video_formt.type=V4L2_BUF_TYPE_VIDEO_CAPTURE; /*视频捕获设备*/
//    video_formt.fmt.pix.height=VIDEO_HEIGHT; //480
//    video_formt.fmt.pix.width=VIDEO_WIDTH; //640
//    video_formt.fmt.pix.pixelformat=V4L2_PIX_FMT_YUYV;
//    if(ioctl(video_fd,VIDIOC_S_FMT,&video_formt))return -2;
//    printf("当前摄像头尺寸:width*height=%d*%d\n",video_formt.fmt.pix.width,video_formt.fmt.pix.height);

//    /*3.请求申请缓冲区的数量*/
//    struct v4l2_requestbuffers video_requestbuffers;
//    memset(&video_requestbuffers,0,sizeof(struct v4l2_requestbuffers));
//    video_requestbuffers.count=4;
//    video_requestbuffers.type=V4L2_BUF_TYPE_VIDEO_CAPTURE; /*视频捕获设备*/
//    video_requestbuffers.memory=V4L2_MEMORY_MMAP;
//    if(ioctl(video_fd,VIDIOC_REQBUFS,&video_requestbuffers))return -3;
//    printf("video_requestbuffers.count=%d\n",video_requestbuffers.count);

//    /*4. 获取缓冲区的首地址*/
//    struct v4l2_buffer video_buffer;
//    memset(&video_buffer,0,sizeof(struct v4l2_buffer));
//    int i;
//    for(i=0;i<video_requestbuffers.count;i++)
//    {
//        video_buffer.type=V4L2_BUF_TYPE_VIDEO_CAPTURE; /*视频捕获设备*/
//        video_buffer.memory=V4L2_MEMORY_MMAP;
//        video_buffer.index=i;/*缓冲区的编号*/
//        if(ioctl(video_fd,VIDIOC_QUERYBUF,&video_buffer))return -4;
//        /*映射地址*/
//        image_buffer[i]=(unsigned char *)mmap(NULL,video_buffer.length,PROT_READ|PROT_WRITE,MAP_SHARED,video_fd,video_buffer.m.offset);
//        printf("image_buffer[%d]=0x%X\n",i,image_buffer[i]);
//    }
//    /*5. 将缓冲区加入到采集队列*/
//    memset(&video_buffer,0,sizeof(struct v4l2_buffer));
//    for(i=0;i<video_requestbuffers.count;i++)
//    {
//        video_buffer.type=V4L2_BUF_TYPE_VIDEO_CAPTURE; /*视频捕获设备*/
//        video_buffer.memory=V4L2_MEMORY_MMAP;
//        video_buffer.index=i;/*缓冲区的编号*/
//        if(ioctl(video_fd,VIDIOC_QBUF,&video_buffer))return -5;
//    }
//    /*6. 启动采集队列*/
//    int opt=V4L2_BUF_TYPE_VIDEO_CAPTURE; /*视频捕获设备*/
//    if(ioctl(video_fd,VIDIOC_STREAMON,&opt))return -6;
//    return 0;
//}


////YUYV==YUV422
//int yuyv_to_yuv420p(const unsigned char *in, unsigned char *out, unsigned int width, unsigned int height)
//{
//    unsigned char *y = out;
//    unsigned char *u = out + width*height;
//    unsigned char *v = out + width*height + width*height/4;
//    unsigned int i,j;
//    unsigned int base_h;
//    unsigned int  is_u = 1;
//    unsigned int y_index = 0, u_index = 0, v_index = 0;
//    unsigned long yuv422_length = 2 * width * height;
//    //序列为YU YV YU YV，一个yuv422帧的长度 width * height * 2 个字节
//    //丢弃偶数行 u v
//    for(i=0; i<yuv422_length; i+=2)
//    {
//        *(y+y_index) = *(in+i);
//        y_index++;
//    }
//    for(i=0; i<height; i+=2)
//    {
//        base_h = i*width*2;
//        for(j=base_h+1; j<base_h+width*2; j+=2)
//        {
//            if(is_u)
//            {
//                *(u+u_index) = *(in+j);
//                u_index++;
//                is_u = 0;
//            }
//            else
//            {
//                *(v+v_index) = *(in+j);
//                v_index++;
//                is_u = 1;
//            }
//        }
//    }
//    return 1;
//}


///*
//子线程函数: 采集摄像头的数据
//*/
//void *pthread_read_video_data(void *arg)
//{
//    /*1. 循环读取摄像头采集的数据*/
//    struct pollfd fds;
//    fds.fd=video_fd;
//    fds.events=POLLIN;

//    /*2. 申请存放JPG的数据空间*/
//    struct v4l2_buffer video_buffer;
//    while(1)
//    {
//        /*(1)等待摄像头采集数据,如果没有数据就进行等待，直到有数据才继续执行*/
//        poll(&fds,1,-1);
//        /*(2)取出队列里采集完毕的缓冲区*/
//        video_buffer.type=V4L2_BUF_TYPE_VIDEO_CAPTURE; /*视频捕获设备*/
//        video_buffer.memory=V4L2_MEMORY_MMAP;
//        ioctl(video_fd,VIDIOC_DQBUF,&video_buffer);
//        /*(3)处理图像数据*/
//        /*YUYV数据转YUV420P*/
//        pthread_mutex_lock(&mutex);   /*互斥锁上锁*/
//        yuyv_to_yuv420p(image_buffer[video_buffer.index],YUV420P_Buffer,VIDEO_WIDTH,VIDEO_HEIGHT);
//        pthread_mutex_unlock(&mutex); /*互斥锁解锁*/
//        pthread_cond_broadcast(&cond);/*广播方式唤醒休眠的线程*/

//        /*(4)将缓冲区再放入队列*/
//        ioctl(video_fd,VIDIOC_QBUF,&video_buffer);
//    }
//}

///*
//子线程函数: 采集摄像头的数据
//*/
//void *pthread_read_audio_data(void *arg)
//{
//    capture_audio_data(capture_handle,buffer_frames);
//}

////运行示例:  ./a.out /dev/video0
//int main(int argc,char **argv)
//{
//    //    if(argc!=3)
//    //    {
//    //        printf("./app </dev/videoX> <hw:X> \n");
//    //        return 0;
//    //    }
//    int err;
//    pthread_t thread_id;

//    //创建链表头
//    list_head=List_CreateHead(list_head);

//    /*初始化互斥锁*/
//    pthread_mutex_init(&mutex,NULL);
//    /*初始化条件变量*/
//    pthread_cond_init(&cond,NULL);

//    /*初始化互斥锁*/
//    pthread_mutex_init(&mutex_audio,NULL);

//    /*初始化摄像头设备*/
//    err=VideoDeviceInit("/dev/video0");
//    printf("VideoDeviceInit=%d\n",err);
//    if(err!=0)return err;
//    /*创建子线程: 采集摄像头的数据*/
//    pthread_create(&thread_id,NULL,pthread_read_video_data,NULL);
//    /*设置线程的分离属性: 采集摄像头的数据*/
//    pthread_detach(thread_id);

//    capture_audio_data_init("hw:1");
//    /*创建子线程: 采集音频的数据*/
//    pthread_create(&thread_id,NULL,pthread_read_audio_data,NULL);
//    /*设置线程的分离属性: 采集麦克风的数据*/
//    pthread_detach(thread_id);

//    char filename[100];
//    time_t t;
//    struct tm *tme;
//    //开始音频、视频编码
//    while(1)
//    {
//        //开始视频编码
//        video_audio_encode(RTMP_SERVE_RADDR);
//    }
//    return 0;
//}

///*
//函数功能： 创建链表头
//*/
//struct AUDIO_DATA *List_CreateHead(struct AUDIO_DATA *head)
//{
//    if(head==NULL)
//    {
//        head = new AUDIO_DATA;
//        //        head=malloc(sizeof(struct AUDIO_DATA));
//        head->next=NULL;
//    }
//    return head;
//}

///*
//函数功能: 插入新的节点
//*/
//void List_AddNode(struct AUDIO_DATA *head,unsigned char* audio_buffer)
//{
//    struct AUDIO_DATA *tmp=head;
//    struct AUDIO_DATA *new_node;
//    /*找到链表尾部*/
//    while(tmp->next)
//    {
//        tmp=tmp->next;
//    }
//    /*插入新的节点*/
//    new_node = new AUDIO_DATA;
//    //    new_node=malloc(sizeof(struct AUDIO_DATA));
//    new_node->audio_buffer=audio_buffer;
//    new_node->next=NULL;
//    /*将新节点接入到链表*/
//    tmp->next=new_node;
//}

///*
//函数功能:删除节点
//*/
//void List_DelNode(struct AUDIO_DATA *head,unsigned char* audio_buffer)
//{
//    struct AUDIO_DATA *tmp=head;
//    struct AUDIO_DATA *p;
//    /*找到链表中要删除的节点*/
//    while(tmp->next)
//    {
//        p=tmp;
//        tmp=tmp->next;
//        if(tmp->audio_buffer==audio_buffer)
//        {
//            p->next=tmp->next;
//            free(tmp);
//        }
//    }
//}

///*
//*/


///*
//函数功能:遍历链表，得到节点总数量
//*/
//int List_GetNodeCnt(struct AUDIO_DATA *head)
//{
//    int cnt=0;
//    struct AUDIO_DATA *tmp=head;
//    while(tmp->next)
//    {
//        tmp=tmp->next;
//        cnt++;
//    }
//    return cnt;
//}


//int capture_audio_data_init( char *audio_dev)
//{
//    int i;
//    int err;

//    buffer_frames = 1024;
//    unsigned int rate = AUDIO_RATE_SET;// 常用的采样频率: 44100Hz 、16000HZ、8000HZ、48000HZ、22050HZ
////    capture_handle;// 一个指向PCM设备的句柄
//    snd_pcm_hw_params_t *hw_params; //此结构包含有关硬件的信息，可用于指定PCM流的配置

//    /*注册信号捕获退出接口*/
//    printf("进入main\n");
//    /*PCM的采样格式在pcm.h文件里有定义*/
//    format=SND_PCM_FORMAT_S16_LE; // 采样位数：16bit、LE格式

//    /*打开音频采集卡硬件，并判断硬件是否打开成功，若打开失败则打印出错误提示*/
//    if ((err = snd_pcm_open(&capture_handle, audio_dev,SND_PCM_STREAM_CAPTURE,0))<0)
//    {
//        printf("无法打开音频设备: %s (%s)\n",  audio_dev,snd_strerror (err));
//        exit(1);
//    }
//    printf("音频接口打开成功.\n");


//    /*分配硬件参数结构对象，并判断是否分配成功*/
//    if((err = snd_pcm_hw_params_malloc(&hw_params)) < 0)
//    {
//        printf("无法分配硬件参数结构 (%s)\n",snd_strerror(err));
//        exit(1);
//    }
//    printf("硬件参数结构已分配成功.\n");

//    /*按照默认设置对硬件对象进行设置，并判断是否设置成功*/
//    if((err=snd_pcm_hw_params_any(capture_handle,hw_params)) < 0)
//    {
//        printf("无法初始化硬件参数结构 (%s)\n", snd_strerror(err));
//        exit(1);
//    }
//    printf("硬件参数结构初始化成功.\n");

//    /*
//        设置数据为交叉模式，并判断是否设置成功
//        interleaved/non interleaved:交叉/非交叉模式。
//        表示在多声道数据传输的过程中是采样交叉的模式还是非交叉的模式。
//        对多声道数据，如果采样交叉模式，使用一块buffer即可，其中各声道的数据交叉传输；
//        如果使用非交叉模式，需要为各声道分别分配一个buffer，各声道数据分别传输。
//    */
//    if((err = snd_pcm_hw_params_set_access (capture_handle,hw_params,SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
//    {
//        printf("无法设置访问类型(%s)\n",snd_strerror(err));
//        exit(1);
//    }
//    printf("访问类型设置成功.\n");

//    /*设置数据编码格式，并判断是否设置成功*/
//    if ((err=snd_pcm_hw_params_set_format(capture_handle, hw_params,format)) < 0)
//    {
//        printf("无法设置格式 (%s)\n",snd_strerror(err));
//        exit(1);
//    }
//    fprintf(stdout, "PCM数据格式设置成功.\n");

//    /*设置采样频率，并判断是否设置成功*/
//    if((err=snd_pcm_hw_params_set_rate_near (capture_handle,hw_params,&rate,0))<0)
//    {
//        printf("无法设置采样率(%s)\n",snd_strerror(err));
//        exit(1);
//    }
//    printf("采样率设置成功\n");

//    /*设置声道，并判断是否设置成功*/
//    if((err = snd_pcm_hw_params_set_channels(capture_handle, hw_params,AUDIO_CHANNEL_SET)) < 0)
//    {
//        printf("无法设置声道数(%s)\n",snd_strerror(err));
//        exit(1);
//    }
//    printf("声道数设置成功.\n");

//    /*将配置写入驱动程序中，并判断是否配置成功*/
//    if ((err=snd_pcm_hw_params (capture_handle,hw_params))<0)
//    {
//        printf("无法向驱动程序设置参数(%s)\n",snd_strerror(err));
//        exit(1);
//    }
//    printf("参数设置成功.\n");
//    /*使采集卡处于空闲状态*/
//    snd_pcm_hw_params_free(hw_params);

//    /*准备音频接口,并判断是否准备好*/
//    if((err=snd_pcm_prepare(capture_handle))<0)
//    {
//        printf("无法使用音频接口 (%s)\n",snd_strerror(err));
//        exit(1);
//    }
//    printf("音频接口准备好.\n");

//    return 0;
//}

//unsigned char *audio_read_buff;
////音频采集线程
//int capture_audio_data(snd_pcm_t *capture_handle,int buffer_frames)
//{
//    int err;
//    //因为frame样本数固定为1024,而双通道，每个采样点2byte，所以一次要发送1024*2*2byte数据给frame->data[0];
//    /*配置一个数据缓冲区用来缓冲数据*/
//    //snd_pcm_format_width(format) 获取样本格式对应的大小(单位是:bit)
//    int frame_byte=snd_pcm_format_width(format)/8;

//    /*开始采集音频pcm数据*/
//    printf("开始采集数据...\n");
//    int i;
//    char *audio_buffer;
//    audio_read_buff = (unsigned char*)malloc(buffer_frames*frame_byte*AUDIO_CHANNEL_SET);
//    while(1)
//    {
//        audio_buffer=(char*)malloc(buffer_frames*frame_byte*AUDIO_CHANNEL_SET); //2048

//        if(audio_buffer==NULL)
//        {
//            printf("缓冲区分配错误.\n");
//            break;
//        }
//        /*从声卡设备读取一帧音频数据:2048字节*/
//        if((err=snd_pcm_readi(capture_handle,audio_read_buff,buffer_frames))!=buffer_frames)
//        {
//            printf("从音频接口读取失败(%s)\n",snd_strerror(err));
//            exit(1);
//        }

//        pthread_mutex_lock(&mutex_audio); /*互斥锁上锁*/
//        memcpy(audio_buffer,audio_read_buff,buffer_frames*frame_byte*AUDIO_CHANNEL_SET);
//        //添加节点
//        List_AddNode(list_head,(unsigned char *)audio_buffer);
//        pthread_mutex_unlock(&mutex_audio); /*互斥锁解锁*/
//    }

//    /*释放数据缓冲区*/
//    free(audio_buffer);

//    /*关闭音频采集卡硬件*/
//    snd_pcm_close(capture_handle);

//    /*关闭文件流*/
//    fclose(pcm_data_file);

//    return 0;
//}


#include <alsa/asoundlib.h>
#include <stdio.h>
extern "C"{
#include <sys/time.h>
#include <libavutil/time.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavdevice/avdevice.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
}
#include <pthread.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#define CHANNELS 2
#define FSIZE 2*CHANNELS

//设置初值结构体
union semun{
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO(Linux-specific) */
};

//获取资源
int sem_p(int semid)
{
    struct sembuf buf;
    int ret=-1;
    buf.sem_num=0;
    buf.sem_op=-1;
    buf.sem_flg=SEM_UNDO;
    ret=semop(semid,&buf,1);
    if(ret==-1)
    {
        perror("sem get fail!");
        return -1;
    }
    return 0;
}


//释放资源
int sem_v(int semid)
{
    struct sembuf buf;
    int ret=-1;
    buf.sem_num=0;
    buf.sem_op=+1;
    buf.sem_flg=SEM_UNDO;
    ret=semop(semid,&buf,1);
    if(ret==-1)
    {
        perror("sem get fail!");
        return -1;
    }
    return 0;
}


void *thread_func(void *arg);

//关键输出封装器
AVFormatContext* outfmt_ctx = NULL;
//推流前准备标志
int video_ready=0,audio_ready=0;
//互斥锁
int semid=-1;
union semun sem_val;

int main()
{

    //初始化网络
    avformat_network_init();
    //初始化设备
    avdevice_register_all();
    //输入封装器
    AVFormatContext* infmt_ctx = NULL;


    //视频输入格式
    AVInputFormat* ifmt =NULL;

    //通过v4l2框架来获取视频输入格式
    ifmt = av_find_input_format("linux4video2");

    //视频输入设备
    char *in_filename  = "/dev/video0";

    //视频输出设备
    char *out_filename = "rtmp://localhost/videotest/";

    //打开视频设备
    if (0 > avformat_open_input(&infmt_ctx, in_filename, ifmt, NULL)) {
        printf("failed open input file\n");
        return -1;
    }

    //读取设备信息
    if (0 > avformat_find_stream_info(infmt_ctx, NULL)) {
        printf("failed find stream info\n");
        avformat_close_input(&infmt_ctx);
        return -1;
    }


    //对流（Stream）的封装和抽象
    AVStream *in_stream = NULL;
    AVStream *out_stream = NULL;

    //视频流和音频流的标志
    int videoindex=-1;

    int i=0;
    int ret;
    //查找视频||音频流
    for (i = 0; i < infmt_ctx->nb_streams; i++)
    {
        //Create output AVStream according to input AVStream

        if (infmt_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoindex = i;
        }
        else
        {
            break;
        }
    }

    if (videoindex == -1)
    {
        printf("input video stream not exist\n");
        return -1;
    }


    AVCodec* encodec = NULL;
    AVCodec* decodec = NULL;


    //找到编码器
    encodec = avcodec_find_encoder(AV_CODEC_ID_H264);
    if (!encodec)
    {
        printf("not find encoder\n");
        avformat_close_input(&infmt_ctx);
        return -1;
    }


    //创建解码器上下文
    AVCodecContext* decodec_ctx = NULL;
    decodec_ctx=infmt_ctx->streams[videoindex]->codec;
    //找到解码器
    decodec = avcodec_find_decoder(decodec_ctx->codec_id);
    if (!decodec)
    {
        printf("not find decoder\n");
        avformat_close_input(&infmt_ctx);
        return -1;
    }

    //创建编码器上下文
    AVCodecContext* encodec_ctx = NULL;
    encodec_ctx = avcodec_alloc_context3(encodec);
    if (!encodec_ctx)
    {
        printf("not alloc context3\n\n");
        avformat_close_input(&infmt_ctx);
        return -1;
    }

    //打开解码器
    ret = avcodec_open2(decodec_ctx, decodec, NULL);
    if (ret < 0) {
        fprintf(stderr, "Could not open codec: %s\n", ret);
        return -1;
    }


    //配置编码器参数
    encodec_ctx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
    encodec_ctx->codec_id = encodec->id;
    encodec_ctx->bit_rate = 400000;
    encodec_ctx->width = 1280;
    encodec_ctx->height = 720;
    encodec_ctx->time_base = (AVRational){1, 30};    //5是编多少帧就发送，可根据编码速度改变
    encodec_ctx->framerate = (AVRational){30, 1};
    encodec_ctx->gop_size = 15;
    encodec_ctx->max_b_frames = 0;
    encodec_ctx->pix_fmt = AV_PIX_FMT_YUV420P;


    //编码质量和速度
    av_opt_set(encodec_ctx->priv_data, "preset", "ultrafast", 0);
    av_opt_set(encodec_ctx->priv_data, "tune", "zerolatency", 0);
    AVDictionary *opts = NULL;
    av_dict_set(&opts, "profile", "baseline", 0);
    //av_opt_set(encodec_ctx->priv_data, "crf", "18", 0);

    //打开编码器
    ret = avcodec_open2(encodec_ctx, encodec, &opts);
    if (ret < 0) {
        fprintf(stderr, "Could not open codec: %s\n", ret);
        return -1;
    }

    //初始化输出封装器
    ret=avformat_alloc_output_context2(&outfmt_ctx, NULL, "flv",out_filename);
    if (ret != 0) {
        printf("failed alloc output context\n");
        avformat_close_input(&infmt_ctx);
        return -1;;
    }

    //添加视频流
    out_stream = avformat_new_stream(outfmt_ctx,NULL);
    if (!out_stream) {
        printf("failed new stream\n");
        avformat_close_input(&infmt_ctx);
        avformat_close_input(&outfmt_ctx);
        return -1;
    }
    out_stream->codecpar->codec_tag = 0;
    //复制参数
    avcodec_parameters_from_context(out_stream->codecpar, encodec_ctx);

    //查看输出封装内容
    av_dump_format(outfmt_ctx, 0, out_filename, 1);
    //创建音频推流线程
    pthread_t tid;            //线程ID
    int t_arg=100;            //传入参数
    if(pthread_create(&tid,NULL,thread_func,&t_arg))    //创建线程
    {
        perror("Fail to create thread");
    }
    //等待音频推流初始化
    while(!audio_ready)
    {

    }
    //打开rtmp的网络输出IO
    ret=avio_open(&outfmt_ctx->pb, out_filename, AVIO_FLAG_WRITE);
    if (ret!=0)
    {
    printf("failed to open outfile\n");
    avformat_close_input(&infmt_ctx);
    avformat_close_input(&outfmt_ctx);
    return -1;
    }

    //写入封装头
    ret=avformat_write_header(outfmt_ctx, NULL);
    if (ret!=0)
    {
    printf("failed to write header\n");
    avio_close(outfmt_ctx->pb);
    avformat_close_input(&infmt_ctx);
    avformat_close_input(&outfmt_ctx);
    return -1;
    }


    AVPacket *dec_pkt,enc_pkt;
    //包裹申请内存
    dec_pkt = (AVPacket *)av_malloc(sizeof(AVPacket));
    memset(&enc_pkt, 0, sizeof(enc_pkt));
    //像素格式转换YU420
    struct SwsContext *img_convert_ctx  = NULL;
    img_convert_ctx  = sws_getCachedContext(img_convert_ctx, decodec_ctx->width, decodec_ctx->height,decodec_ctx->pix_fmt, encodec_ctx->width, encodec_ctx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, 0, 0, 0);
    if (!img_convert_ctx)
    {
        printf("fail to sws_getCachedContext\n");
    }

    AVFrame *pFrameYUV,*pFrame ;
    //原始帧
    pFrame = av_frame_alloc();
    //输出帧
    pFrameYUV = av_frame_alloc();
    pFrameYUV->format = AV_PIX_FMT_YUV420P;
    pFrameYUV->width = 1280;
    pFrameYUV->height = 720;
    pFrameYUV->pts = 0;

    ret = av_frame_get_buffer(pFrameYUV, 1);
    if (ret != 0)
    {
        printf("fail to frame get buffer\n");
        return -1;
    }
    //开始计时
    int64_t start_time = av_gettime();
    //标记
    int got_picture=0,enc_got_frame=0;
    //每一帧编号
    int vpts = 0;

    //创建信号量
    semid=semget(1234,1,0666|IPC_CREAT);
    if(semid==-1)
    {
        perror("create sem fail!");
        return -1;
    }

    //设置信号量初值
    sem_val.val=1;
    ret=semctl(semid,0,SETVAL,sem_val);
    if(ret==-1)
    {
        perror("semctl set sem val fail!");
        return -1;
    }

    video_ready=1;

    while(1)
    {
        //每一帧加1
        pFrameYUV->pts = vpts;
        vpts+=1;
        //获取摄像头帧
        ret=av_read_frame(infmt_ctx,dec_pkt);
        if (ret != 0)
        {
            printf("fail to read_frame\n");
            break;
        }

        //解码获取初始图片
        ret = avcodec_decode_video2(infmt_ctx->streams[dec_pkt->stream_index]->codec, pFrame, &got_picture, dec_pkt);
        if(!got_picture)
        {
            printf("123\n");
            continue;
        }
        //h264格式转换
        ret=sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, encodec_ctx->height, pFrameYUV->data, pFrameYUV->linesize);
        if (ret <= 0)
        {
            printf("123\n");
            continue;
        }

        //输出帧编码
        ret = avcodec_send_frame(encodec_ctx, pFrameYUV);
        if (ret != 0)
        {
            printf("123\n");
            continue;
        }
        //打包到输出包裹
        ret = avcodec_receive_packet(encodec_ctx, &enc_pkt);
        if (ret != 0 || enc_pkt.size > 0)
        {
                //cout << "*" << pack.size << flush;
        }
        else
        {
                continue;
        }

        //推流
        enc_pkt.pts = av_rescale_q(enc_pkt.pts, encodec_ctx->time_base, out_stream->time_base);
        enc_pkt.dts = av_rescale_q(enc_pkt.dts, encodec_ctx->time_base, out_stream->time_base);
        enc_pkt.duration = av_rescale_q(enc_pkt.duration, encodec_ctx->time_base, out_stream->time_base);


        ret=sem_p(semid);
        if(ret==-1)
        {
            perror("sem_p fail!");
            break;
        }


        //发送到服务器
        ret = av_interleaved_write_frame(outfmt_ctx, &enc_pkt);
        if (ret < 0) {
            fprintf(stderr, "Error muxing packet\n");
            break;
        }


        av_packet_unref(&enc_pkt);
        //释放信号量资源
        ret=sem_v(semid);
        if(ret==-1)
        {
            perror("sem_p fail!");
            break;
        }

    }
    avio_close(outfmt_ctx->pb);
    avformat_close_input(&infmt_ctx);
    avformat_close_input(&outfmt_ctx);
    return 0;
}


void *thread_func(void *arg)    //线程函数
{
    int fd;

    int ret=0;
    snd_pcm_t *handle;
    //以录音模式打开设备
    ret = snd_pcm_open(&handle, "hw:1",SND_PCM_STREAM_CAPTURE, 0);
    if (ret < 0)
    {
        printf("unable to open pcm device!\n");
        exit(1);
    }

    //配置硬件参数结构体
    snd_pcm_hw_params_t *params;
    //params申请内存
    snd_pcm_hw_params_malloc(&params);
    //使用pcm设备初始化hwparams
    ret=snd_pcm_hw_params_any(handle, params);
    if (ret < 0)
    {
        printf("Can not configure this PCM device!\n");
        exit(1);
    }

    //设置多路数据在buffer中的存储方式
    //SND_PCM_ACCESS_RW_INTERLEAVED每个周期(period)左右声道的数据交叉存放
    ret=snd_pcm_hw_params_set_access(handle, params,SND_PCM_ACCESS_RW_INTERLEAVED);
    if (ret < 0)
    {
        printf("Failed to set PCM device to interleaved!\n");
        exit(1);
    }

    //设置16位采样格式
    ret=snd_pcm_hw_params_set_format(handle, params,SND_PCM_FORMAT_S16_LE);
    if (ret < 0)
    {
        printf("Failed to set PCM device to 16-bit signed PCM\n");
        exit(1);
    }

    //设置声道数
    ret=snd_pcm_hw_params_set_channels(handle, params, CHANNELS);
    if (ret < 0)
    {
        printf("Failed to set PCM device CHANNELS\n");
        exit(1);
    }

    unsigned int val=44100;
    int dir;
    //设置采样率,如果采样率不支持，会用硬件支持最接近的采样率
    ret=snd_pcm_hw_params_set_rate_near(handle, params,&val, &dir);
    if (ret < 0)
    {
        printf("Failed to set PCM device to sample rate\n");
        exit(1);
    }

    unsigned int buffer_time,period_time;
    //获取最大的缓冲时间,buffer_time单位为us,500000us=0.5s
    snd_pcm_hw_params_get_buffer_time_max(params, &buffer_time, 0);
    //printf("buffer_time:%d\n",buffer_time);
    if ( buffer_time >500000)
        buffer_time = 500000;

    //设置缓冲时间
    ret = snd_pcm_hw_params_set_buffer_time_near(handle, params, &buffer_time, 0);
    if (ret < 0)
    {
        printf("Failed to set PCM device to sample rate\n");
        exit(1);
    }

    //设置周期时间，设置为37帧/s，1/37=0.023219
    period_time = 23219;
    ret = snd_pcm_hw_params_set_period_time_near(handle, params, &period_time, 0);
    if (ret < 0)
    {
        printf("Failed to set PCM device to period time\n");
        exit(1);
    }

    //让这些参数作用于PCM设备
    ret = snd_pcm_hw_params(handle, params);
    if (ret < 0)
    {
        printf("unable to set hw parameters\n");
        exit(1);
    }

    snd_pcm_uframes_t frames;
    snd_pcm_hw_params_get_period_size(params,&frames, &dir);
    printf("period_size:%ld\n",frames);
    int size;
    // 1 frame = channels * sample_size.
    size = frames * FSIZE; /* 2 bytes/sample, 1 channels */
    printf("size:%d\n",size);
    char *buffer;
    buffer = (char *) malloc(size);

    AVFrame *pframePCM;
    pframePCM = av_frame_alloc();

    pframePCM->format = AV_SAMPLE_FMT_S16;
    pframePCM->channel_layout = AV_CH_LAYOUT_STEREO;
    pframePCM->sample_rate = 44100;
    pframePCM->nb_samples = frames;
    pframePCM->channels = CHANNELS;
    av_frame_get_buffer(pframePCM, 0);

    AVFrame *pframeAAC;
    pframeAAC = av_frame_alloc();

    pframeAAC->format = AV_SAMPLE_FMT_FLTP;
    pframeAAC->channel_layout = AV_CH_LAYOUT_STEREO;
    pframeAAC->sample_rate = 44100;
    pframeAAC->nb_samples = 1024;
    pframeAAC->channels = CHANNELS;
    av_frame_get_buffer(pframeAAC, 0);

    int re = -1;
    struct SwrContext *aac_convert_ctx  = swr_alloc();
    if (!aac_convert_ctx)
    {
        fprintf(stderr, "Could not allocate resampler context\n");
        return &re;
    }

    swr_alloc_set_opts(aac_convert_ctx,
                       AV_CH_LAYOUT_STEREO,
                       AV_SAMPLE_FMT_FLTP,
                       44100,
                       AV_CH_LAYOUT_STEREO,
                       AV_SAMPLE_FMT_S16,
                       44100,
                       0,
                       NULL);


    if ((ret = swr_init(aac_convert_ctx)) < 0)
    {
        fprintf(stderr, "Failed to initialize the resampling context\n");
        return &re;
    }


    AVCodec* encodec = NULL;
    //找到编码器
    encodec = avcodec_find_encoder(AV_CODEC_ID_AAC);
    if (!encodec)
    {
        printf("not find encoder\n");
        return &re;
    }

    AVCodecContext* encodec_ctx = NULL;
    //创建编码器
    encodec_ctx = avcodec_alloc_context3(encodec);
    if (!encodec_ctx)
    {
        printf("not alloc context3\n\n");
        return &re;
    }

    encodec_ctx->codec_id = encodec->id;
    encodec_ctx->codec_type = AVMEDIA_TYPE_AUDIO;
    encodec_ctx->sample_fmt  = AV_SAMPLE_FMT_FLTP;
    encodec_ctx->bit_rate    = 64000;
    encodec_ctx->sample_rate = 44100;
    encodec_ctx->channel_layout = AV_CH_LAYOUT_STEREO ;
    encodec_ctx->channels = av_get_channel_layout_nb_channels(AV_CH_LAYOUT_STEREO);

    //打开解码器
    ret = avcodec_open2(encodec_ctx, encodec, NULL);
    if (ret < 0) {
        fprintf(stderr, "Could not open codec: %s\n", ret);
        return &re;
    }

    //服务器地址
    char *out_name="rtmp://47.101.62.167/live/stream";


    AVStream *out_stream = NULL;
    //添加音频流
    out_stream = avformat_new_stream(outfmt_ctx,NULL);
    if (!out_stream) {
        printf("failed new stream\n");
        return &re;
    }

    //复制参数
    avcodec_parameters_from_context(out_stream->codecpar, encodec_ctx);

    //查看输出封装内容
    av_dump_format(outfmt_ctx, 0, out_name, 1);


    AVPacket enc_pkt;
    memset(&enc_pkt, 0, sizeof(enc_pkt));

    int got_picture;
    int i,vpts=0;
    char *p;
    struct timeval start, end;
    gettimeofday( &start, NULL );

    audio_ready=1;
    while(!video_ready)
    {

    }

    while (1)
    {
        ret = snd_pcm_readi(handle, buffer, frames);
        if (ret == -EPIPE) {
        // EPIPE means overrun
            fprintf(stderr, "overrun occurred\n");
            ret=snd_pcm_prepare(handle);
            if(ret <0){
                printf("Failed to recover form overrun");
                exit(1);
            }
        }
        else if (ret < 0) {
            fprintf(stderr,"error from read: %s\n",snd_strerror(ret));
            exit(1);
        }
        else if (ret != (int)frames) {
            fprintf(stderr, "short read, read %d frames\n", ret);

        }


        memcpy(pframePCM->data[0],buffer,size);

        ret=swr_convert(aac_convert_ctx,pframeAAC->data, pframeAAC->nb_samples,(const uint8_t **)pframePCM->data, pframePCM->nb_samples);

        avcodec_encode_audio2(encodec_ctx, &enc_pkt, pframeAAC, &got_picture);
    if(!got_picture)
        {
            printf("123\n");
            continue;
        }


        //推流
        enc_pkt.pts = av_rescale_q(enc_pkt.pts, encodec_ctx->time_base, out_stream->time_base);
        enc_pkt.dts = av_rescale_q(enc_pkt.dts, encodec_ctx->time_base, out_stream->time_base);
        enc_pkt.duration = av_rescale_q(enc_pkt.duration, encodec_ctx->time_base, out_stream->time_base);
        enc_pkt.stream_index=1;

        //获取信号量资源
        ret=sem_p(semid);
        if(ret==-1)
        {
            perror("sem_p fail!");
            break;
        }


        ret = av_interleaved_write_frame(outfmt_ctx, &enc_pkt);
        if (ret < 0) {
            fprintf(stderr, "Error muxing packet\n");
            break;
        }
        av_free_packet(&enc_pkt);

        //释放信号量资源
        ret=sem_v(semid);
        if(ret==-1)
        {
            perror("sem_p fail!");
            break;
        }

        pframeAAC->pts = vpts;
        vpts+=pframeAAC->nb_samples;



        gettimeofday( &end, NULL );
        printf("%ld",end.tv_sec-start.tv_sec);
        printf("\r\033[k");
        fflush(stdout);
    }

    printf("audio off\n");
    snd_pcm_drain(handle);
    snd_pcm_close(handle);
    free(buffer);

}

