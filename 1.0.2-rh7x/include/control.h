/*****************************************************************
|
|      Xaudio SDK. ASYNC API
|
|
|      (c) 1996-2000 Xaudio Corporation
|      Author: Gilles Boccon-Gibod (gilles@xaudio.com)
|
 ****************************************************************/

#ifndef __CONTROL_H__
#define __CONTROL_H__

/*----------------------------------------------------------------------
|       includes
+---------------------------------------------------------------------*/
#include "xaudio.h"
#include "decoder.h"
#include "properties.h"

/*----------------------------------------------------------------------
|       version constants
+---------------------------------------------------------------------*/
#define XA_ASYNC_API_MAJOR    3
#define XA_ASYNC_API_MINOR    7
#define XA_ASYNC_API_REVISION 0
#define XA_ASYNC_API_VERSION          \
 XA_VERSION_ID(XA_ASYNC_API_MAJOR,    \
               XA_ASYNC_API_MINOR,    \
               XA_ASYNC_API_REVISION)

/*----------------------------------------------------------------------
|       dthread messages
+---------------------------------------------------------------------*/
typedef enum {
    XA_MSG_UNKNOWN,                                          /*   0 */

    /* commands to decoder */
    XA_MSG_COMMAND_EXIT,                                     /*   1 */
    XA_MSG_COMMAND_SYNC,
    XA_MSG_COMMAND_PING,                                     /*   2 */
    XA_MSG_COMMAND_PLAY,                                     /*   3 */
    XA_MSG_COMMAND_PAUSE,                                    /*   4 */
    XA_MSG_COMMAND_STOP,                                     /*   5 */
    XA_MSG_COMMAND_SEEK,                                     /*   6 */
    XA_MSG_COMMAND_INPUT_OPEN,                               /*   7 */
    XA_MSG_COMMAND_INPUT_CLOSE,                              /*   8 */
    XA_MSG_COMMAND_INPUT_SEND_MESSAGE,                       /*   9 */
    XA_MSG_COMMAND_INPUT_ADD_FILTER,                         /*  10 */
    XA_MSG_COMMAND_INPUT_REMOVE_FILTER,                      /*  11 */
    XA_MSG_COMMAND_INPUT_FILTERS_LIST,                       /*  12 */
    XA_MSG_COMMAND_INPUT_MODULE_REGISTER,                    /*  13 */
    XA_MSG_COMMAND_INPUT_MODULE_QUERY,                       /*  14 */
    XA_MSG_COMMAND_INPUT_MODULES_LIST,                       /*  15 */
    XA_MSG_COMMAND_OUTPUT_OPEN,                              /*  16 */
    XA_MSG_COMMAND_OUTPUT_CLOSE,                             /*  17 */
    XA_MSG_COMMAND_OUTPUT_SEND_MESSAGE,                      /*  18 */
    XA_MSG_COMMAND_OUTPUT_MUTE,                              /*  19 */
    XA_MSG_COMMAND_OUTPUT_UNMUTE,                            /*  20 */
    XA_MSG_COMMAND_OUTPUT_RESET,                             /*  21 */
    XA_MSG_COMMAND_OUTPUT_DRAIN,                             /*  22 */
    XA_MSG_COMMAND_OUTPUT_ADD_FILTER,                        /*  23 */
    XA_MSG_COMMAND_OUTPUT_REMOVE_FILTER,                     /*  24 */
    XA_MSG_COMMAND_OUTPUT_FILTERS_LIST,                      /*  25 */
    XA_MSG_COMMAND_OUTPUT_MODULE_REGISTER,                   /*  26 */
    XA_MSG_COMMAND_OUTPUT_MODULE_QUERY,                      /*  27 */
    XA_MSG_COMMAND_OUTPUT_MODULES_LIST,                      /*  28 */
    XA_MSG_COMMAND_CODEC_MODULE_REGISTER,                    /*  29 */
    XA_MSG_SET_PLAYER_MODE,                                  /*  30 */
    XA_MSG_GET_PLAYER_MODE,                                  /*  31 */
    XA_MSG_SET_PLAYER_ENVIRONMENT_INTEGER,                   /*  32 */
    XA_MSG_GET_PLAYER_ENVIRONMENT_INTEGER,                   /*  33 */
    XA_MSG_SET_PLAYER_ENVIRONMENT_STRING,                    /*  34 */
    XA_MSG_GET_PLAYER_ENVIRONMENT_STRING,                    /*  35 */
    XA_MSG_UNSET_PLAYER_ENVIRONMENT,                         /*  36 */
    XA_MSG_SET_INPUT_NAME,                                   /*  37 */
    XA_MSG_GET_INPUT_NAME,                                   /*  38 */
    XA_MSG_SET_INPUT_MODULE,                                 /*  39 */
    XA_MSG_GET_INPUT_MODULE,                                 /*  40 */
    XA_MSG_SET_INPUT_POSITION_RANGE,                         /*  41 */
    XA_MSG_GET_INPUT_POSITION_RANGE,                         /*  42 */
    XA_MSG_SET_INPUT_TIMECODE_GRANULARITY,                   /*  43 */
    XA_MSG_GET_INPUT_TIMECODE_GRANULARITY,                   /*  44 */
    XA_MSG_SET_OUTPUT_NAME,                                  /*  45 */
    XA_MSG_GET_OUTPUT_NAME,                                  /*  46 */
    XA_MSG_SET_OUTPUT_MODULE,                                /*  47 */
    XA_MSG_GET_OUTPUT_MODULE,                                /*  48 */
    XA_MSG_SET_OUTPUT_POSITION_RANGE,                        /*  49 */
    XA_MSG_GET_OUTPUT_POSITION_RANGE,                        /*  50 */
    XA_MSG_SET_OUTPUT_TIMECODE_GRANULARITY,                  /*  51 */
    XA_MSG_GET_OUTPUT_TIMECODE_GRANULARITY,                  /*  52 */
    XA_MSG_SET_OUTPUT_VOLUME,                                /*  53 */
    XA_MSG_GET_OUTPUT_VOLUME,                                /*  54 */
    XA_MSG_SET_OUTPUT_CHANNELS,                              /*  55 */
    XA_MSG_GET_OUTPUT_CHANNELS,                              /*  56 */
    XA_MSG_SET_OUTPUT_PORTS,                                 /*  57 */
    XA_MSG_GET_OUTPUT_PORTS,                                 /*  58 */
    XA_MSG_SET_CODEC_QUALITY,                                /*  59 */
    XA_MSG_GET_CODEC_QUALITY,                                /*  60 */
    XA_MSG_SET_CODEC_EQUALIZER,                              /*  61 */
    XA_MSG_GET_CODEC_EQUALIZER,                              /*  62 */
    XA_MSG_SET_NOTIFICATION_MASK,                            /*  63 */
    XA_MSG_GET_NOTIFICATION_MASK,                            /*  64 */
    XA_MSG_SET_DEBUG_LEVEL,                                  /*  65 */
    XA_MSG_GET_DEBUG_LEVEL,                                  /*  66 */

    /* notifications from decoder */
    XA_MSG_NOTIFY_READY,                                     /*  67 */
    XA_MSG_NOTIFY_ACK,                                       /*  68 */
    XA_MSG_NOTIFY_NACK,                                      /*  69 */
    XA_MSG_NOTIFY_PONG,                                      /*  70 */
    XA_MSG_NOTIFY_EXITED,                                    /*  71 */
    XA_MSG_NOTIFY_PLAYER_STATE,                              /*  72 */
    XA_MSG_NOTIFY_PLAYER_MODE,                               /*  73 */
    XA_MSG_NOTIFY_PLAYER_ENVIRONMENT_INTEGER,                /*  74 */
    XA_MSG_NOTIFY_PLAYER_ENVIRONMENT_STRING,                 /*  75 */
    XA_MSG_NOTIFY_INPUT_STATE,                               /*  76 */
    XA_MSG_NOTIFY_INPUT_NAME,                                /*  77 */
    XA_MSG_NOTIFY_INPUT_CAPS,                                /*  78 */
    XA_MSG_NOTIFY_INPUT_POSITION,                            /*  79 */
    XA_MSG_NOTIFY_INPUT_POSITION_RANGE,                      /*  80 */
    XA_MSG_NOTIFY_INPUT_TIMECODE,                            /*  81 */
    XA_MSG_NOTIFY_INPUT_TIMECODE_GRANULARITY,                /*  82 */
    XA_MSG_NOTIFY_INPUT_MODULE,                              /*  83 */
    XA_MSG_NOTIFY_INPUT_MODULE_INFO,                         /*  84 */
    XA_MSG_NOTIFY_INPUT_DEVICE_INFO,                         /*  85 */
    XA_MSG_NOTIFY_INPUT_FILTER_INFO,                         /*  86 */
    XA_MSG_NOTIFY_OUTPUT_STATE,                              /*  87 */
    XA_MSG_NOTIFY_OUTPUT_NAME,                               /*  88 */
    XA_MSG_NOTIFY_OUTPUT_CAPS,                               /*  89 */
    XA_MSG_NOTIFY_OUTPUT_POSITION,                           /*  90 */
    XA_MSG_NOTIFY_OUTPUT_POSITION_RANGE,                     /*  91 */
    XA_MSG_NOTIFY_OUTPUT_TIMECODE,                           /*  92 */
    XA_MSG_NOTIFY_OUTPUT_TIMECODE_GRANULARITY,               /*  93 */
    XA_MSG_NOTIFY_OUTPUT_VOLUME,                             /*  94 */
    XA_MSG_NOTIFY_OUTPUT_BALANCE,                            /*  95 */
    XA_MSG_NOTIFY_OUTPUT_PCM_LEVEL,                          /*  96 */
    XA_MSG_NOTIFY_OUTPUT_MASTER_LEVEL,                       /*  97 */
    XA_MSG_NOTIFY_OUTPUT_CHANNELS,                           /*  98 */
    XA_MSG_NOTIFY_OUTPUT_PORTS,                              /*  99 */
    XA_MSG_NOTIFY_OUTPUT_MODULE,                             /* 100 */
    XA_MSG_NOTIFY_OUTPUT_MODULE_INFO,                        /* 101 */
    XA_MSG_NOTIFY_OUTPUT_DEVICE_INFO,                        /* 102 */
    XA_MSG_NOTIFY_OUTPUT_FILTER_INFO,                        /* 103 */
    XA_MSG_NOTIFY_STREAM_MIME_TYPE,                          /* 104 */
    XA_MSG_NOTIFY_STREAM_DURATION,                           /* 105 */
    XA_MSG_NOTIFY_STREAM_PARAMETERS,                         /* 106 */
    XA_MSG_NOTIFY_STREAM_PROPERTIES,                         /* 107 */
    XA_MSG_NOTIFY_CODEC_QUALITY,                             /* 108 */
    XA_MSG_NOTIFY_CODEC_EQUALIZER,                           /* 109 */
    XA_MSG_NOTIFY_NOTIFICATION_MASK,                         /* 110 */
    XA_MSG_NOTIFY_DEBUG_LEVEL,                               /* 111 */
    XA_MSG_NOTIFY_PROGRESS,                                  /* 112 */
    XA_MSG_NOTIFY_DEBUG,                                     /* 113 */
    XA_MSG_NOTIFY_ERROR,                                     /* 114 */
    XA_MSG_NOTIFY_PRIVATE_DATA,                              /* 115 */

    /* commands to timesync */
    XA_MSG_COMMAND_FEEDBACK_HANDLER_MODULE_REGISTER,         /* 116 */
    XA_MSG_COMMAND_FEEDBACK_HANDLER_MODULE_QUERY,            /* 117 */
    XA_MSG_COMMAND_FEEDBACK_HANDLER_MODULES_LIST,            /* 118 */
    XA_MSG_COMMAND_FEEDBACK_HANDLER_EXIT,                    /* 119 */
    XA_MSG_COMMAND_FEEDBACK_HANDLER_START,                   /* 120 */
    XA_MSG_COMMAND_FEEDBACK_HANDLER_STOP,                    /* 121 */
    XA_MSG_COMMAND_FEEDBACK_HANDLER_PAUSE,                   /* 122 */
    XA_MSG_COMMAND_FEEDBACK_HANDLER_RESTART,                 /* 123 */
    XA_MSG_COMMAND_FEEDBACK_HANDLER_FLUSH,                   /* 124 */
    XA_MSG_COMMAND_FEEDBACK_HANDLER_SEND_MESSAGE,            /* 125 */
    XA_MSG_COMMAND_FEEDBACK_HANDLER_QUEUE_AUDIO_EVENT,       /* 126 */
    XA_MSG_COMMAND_FEEDBACK_HANDLER_QUEUE_TAG_EVENT,         /* 127 */
    XA_MSG_COMMAND_FEEDBACK_HANDLER_QUEUE_TIMECODE_EVENT,    /* 128 */
    XA_MSG_COMMAND_FEEDBACK_HANDLER_QUEUE_POSITION_EVENT,    /* 129 */
    XA_MSG_SET_FEEDBACK_AUDIO_EVENT_RATE,                    /* 130 */
    XA_MSG_GET_FEEDBACK_AUDIO_EVENT_RATE,                    /* 131 */
    XA_MSG_SET_FEEDBACK_HANDLER_NAME,                        /* 132 */
    XA_MSG_GET_FEEDBACK_HANDLER_NAME,                        /* 133 */
    XA_MSG_SET_FEEDBACK_HANDLER_MODULE,                      /* 134 */
    XA_MSG_GET_FEEDBACK_HANDLER_MODULE,                      /* 135 */
    XA_MSG_SET_FEEDBACK_HANDLER_ENVIRONMENT_INTEGER,         /* 136 */
    XA_MSG_GET_FEEDBACK_HANDLER_ENVIRONMENT_INTEGER,         /* 137 */
    XA_MSG_SET_FEEDBACK_HANDLER_ENVIRONMENT_STRING,          /* 138 */
    XA_MSG_GET_FEEDBACK_HANDLER_ENVIRONMENT_STRING,          /* 139 */
    XA_MSG_UNSET_FEEDBACK_HANDLER_ENVIRONMENT,               /* 140 */

    /* notifications from timesync */
    XA_MSG_NOTIFY_FEEDBACK_AUDIO_EVENT_RATE,                 /* 141 */
    XA_MSG_NOTIFY_FEEDBACK_HANDLER_STATE,                    /* 142 */
    XA_MSG_NOTIFY_FEEDBACK_HANDLER_MODULE,                   /* 143 */
    XA_MSG_NOTIFY_FEEDBACK_HANDLER_MODULE_INFO,              /* 144 */
    XA_MSG_NOTIFY_FEEDBACK_HANDLER_NAME,                     /* 145 */
    XA_MSG_NOTIFY_FEEDBACK_HANDLER_INFO,                     /* 146 */
    XA_MSG_NOTIFY_FEEDBACK_HANDLER_ENVIRONMENT_INTEGER,      /* 147 */
    XA_MSG_NOTIFY_FEEDBACK_HANDLER_ENVIRONMENT_STRING,       /* 148 */
    XA_MSG_NOTIFY_FEEDBACK_AUDIO_EVENT,                      /* 149 */
    XA_MSG_NOTIFY_FEEDBACK_TAG_EVENT,                        /* 150 */

    /* sentinel */
    XA_MSG_LAST                                              /* 151 */
} XA_MessageCode;

typedef enum { 
    XA_PLAYER_STATE_STOPPED, 
    XA_PLAYER_STATE_PLAYING,
    XA_PLAYER_STATE_PAUSED,
    XA_PLAYER_STATE_EOS
} XA_PlayerState;

typedef enum {
    XA_INPUT_STATE_OPEN,
    XA_INPUT_STATE_CLOSED
} XA_InputState;

typedef enum {
    XA_OUTPUT_STATE_OPEN,
    XA_OUTPUT_STATE_CLOSED
} XA_OutputState;

typedef enum {
    XA_FEEDBACK_HANDLER_STATE_STARTED,
    XA_FEEDBACK_HANDLER_STATE_STOPPED
} XA_FeedbackHandlerState;

typedef enum { 
    XA_OUTPUT_CHANNELS_STEREO, 
    XA_OUTPUT_CHANNELS_MONO_LEFT,         
    XA_OUTPUT_CHANNELS_MONO_RIGHT,
    XA_OUTPUT_CHANNELS_MONO_MIX 
} XA_OutputChannels;

typedef struct {
    const char *name;
    union {
        long        integer;
        const char *string;
    } value;
} XA_EnvironmentInfo;

typedef struct {
    unsigned char h;
    unsigned char m;
    unsigned char s;
    unsigned char f;
} XA_TimecodeInfo;

typedef struct {
    unsigned char command;
    short         code;
} XA_NackInfo;
        
typedef struct {
    unsigned char master_level;
    unsigned char pcm_level;
    unsigned char balance;
} XA_VolumeInfo;

typedef struct {
    unsigned long offset;
    unsigned long range;
} XA_PositionInfo;

typedef struct {
    unsigned char id;
    unsigned char nb_devices;
    const char   *name;
    const char   *description;
} XA_ModuleInfo;

typedef struct {
    short          id;
    const char    *name;
} XA_FilterInfo;

typedef struct {
    unsigned char module_id;
    unsigned char index;
    unsigned char flags;
    const char   *name;
    const char   *description;
} XA_DeviceInfo;

typedef struct {
    unsigned long  frequency;
    unsigned short bitrate;
    unsigned char  nb_channels;
} XA_StreamParameters;

typedef struct {
    unsigned short type;
    unsigned long  size;
    const void    *data;
} XA_ModuleMessage;

typedef struct {
    XA_AbsoluteTime when;
    unsigned long   tag;
} XA_TagEvent;

typedef struct {
    XA_AbsoluteTime    when;
    unsigned long      sampling_frequency;
    unsigned short     nb_channels;
    unsigned short     nb_samples;
    const signed char *samples;
} XA_AudioEvent;

typedef struct {
    XA_AbsoluteTime when;
    XA_TimecodeInfo timecode;
} XA_TimecodeEvent;

typedef struct {
    XA_AbsoluteTime when;
    XA_PositionInfo position;
} XA_PositionEvent;

typedef struct {
    unsigned char source;
    unsigned char code;
    short         value;
    const char   *message;
} XA_ProgressInfo;

typedef struct {
    unsigned char source;
    unsigned char level;
    const char   *message;
} XA_DebugInfo;

typedef struct {
    unsigned char source;
    short         code;
    const char   *message;
} XA_ErrorInfo;

typedef struct {
	unsigned char  source;
	short          type;
	const void    *data;
	unsigned long  size;
} XA_PrivateData;

typedef struct {
    XA_MessageCode code;
    union {
        char               *buffer;
        char               *name;
        char               *string;
        char               *mime_type;
        short               module_id;
        unsigned char       state;
        unsigned long       mode;
        unsigned char       channels;
        unsigned char       quality;
        unsigned long       duration;
        unsigned long       range;
        unsigned long       granularity;
        unsigned long       caps;
        unsigned char       ports;
        unsigned char       ack;
        unsigned long       tag;
        unsigned char       debug_level;
        unsigned long       notification_mask;
        unsigned char       rate;
        XA_NackInfo         nack;
        XA_VolumeInfo       volume;
        XA_PositionInfo     position;
        XA_EqualizerInfo   *equalizer;
        XA_ModuleInfo       module_info;
        XA_FilterInfo       filter_info;
        XA_DeviceInfo       device_info;
        XA_StreamParameters stream_parameters;
        XA_EnvironmentInfo  environment_info;
        XA_TimecodeInfo     timecode;
        XA_ModuleMessage    module_message;
        XA_TagEvent         tag_event;
        XA_AudioEvent       audio_event;
        XA_TimecodeEvent    timecode_event;
        XA_PositionEvent    position_event;
        XA_PropertyList     properties;
        XA_AbsoluteTime     when;
        XA_ProgressInfo     progress;
        XA_DebugInfo        debug;
        XA_ErrorInfo        error;
        XA_PrivateData      private_data;
    } data;
} XA_Message;

typedef struct XA_Control XA_Control;

typedef void (*XA_ControlProcedure)(XA_Control *control, void *args);
typedef void (*XA_ControlMessageHandler)(void *client, const XA_Message *message);

/*----------------------------------------------------------------------
|       constants
+---------------------------------------------------------------------*/
#define XA_TIMEOUT_INFINITE                -1

#define XA_CONTROL_PRIORITY_LOWEST          0
#define XA_CONTROL_PRIORITY_LOW             1
#define XA_CONTROL_PRIORITY_NORMAL          2
#define XA_CONTROL_PRIORITY_HIGH            3
#define XA_CONTROL_PRIORITY_HIGHEST         4

/*----------------------------------------------------------------------
|       prototypes
+---------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

int  XA_EXPORT control_procedure_new(XA_Control **control, 
                                     void *control_driver_args,
                                     XA_ControlProcedure decoder_handler,
                                     void *decoder_args,
                                     XA_ControlProcedure feedback_handler,
                                     void *feedback_handler_args);
int  XA_EXPORT control_procedure_delete(XA_Control *control);
int  XA_EXPORT control_procedure_set_priority(XA_Control *control, 
                                              int priority);
int  XA_EXPORT control_procedure_get_priority(XA_Control *control);
int  XA_EXPORT control_set_message_handler(XA_Control *control,
                                           XA_ControlMessageHandler handler,
                                           void *client);
int  XA_EXPORT control_message_to_bytes(const XA_Message *message, 
                                        unsigned char *buffer,
                                        unsigned long max_size);
int  XA_EXPORT control_message_from_bytes(XA_Message *message, 
                                          const unsigned char *buffer);
int            control_message_send(XA_Control *control, int code, ...);
int            control_feedback_send(XA_Control *control, int code, ...);
int  XA_EXPORT control_message_send_N(XA_Control *control, int code);
int  XA_EXPORT control_message_send_P(XA_Control *control, int code, 
                                      const void *ptr1);
int  XA_EXPORT control_message_send_S(XA_Control *control, int code, 
                                      const char *str1);
int  XA_EXPORT control_message_send_SS(XA_Control *control, int code, 
                                       const char *str1, const char *str2);
int  XA_EXPORT control_message_send_SI(XA_Control *control, int code, 
                                       const char *str1, int int1);
int  XA_EXPORT control_message_send_I(XA_Control *control, int code, int int1);
int  XA_EXPORT control_message_send_II(XA_Control *control, int code,
                                       int int1, int int2);
int  XA_EXPORT control_message_send_III(XA_Control *control, int code, 
                                        int int1, int int2, int int3);
int  XA_EXPORT control_message_send_IIII(XA_Control *control, int code, 
                                         int int1, int int2, 
                                         int int3, int int4);
int  XA_EXPORT control_message_send_IPI(XA_Control *control, int code,
                                        int int1, const void *ptr1, int int2);
int  XA_EXPORT control_message_post_to_command_queue(XA_Control *control, 
                                                     const XA_Message *message);
int  XA_EXPORT control_message_sync_to_command_queue(XA_Control *control, int timeout);
int  XA_EXPORT control_message_post_to_feedback_queue(XA_Control *control, 
                                                      const XA_Message *message);
int  XA_EXPORT control_message_sync_to_feedback_queue(XA_Control *control, int timeout);
int  XA_EXPORT control_message_get(XA_Control *control, XA_Message *message);
int  XA_EXPORT control_message_wait(XA_Control *control, XA_Message *message,
                                    int timeout);
void XA_EXPORT control_message_print(const XA_Message *message);
void XA_EXPORT control_message_sprint(char *string, const XA_Message *message);

#ifdef __cplusplus
}
#endif

#endif /* __CONTROL_H__ */
