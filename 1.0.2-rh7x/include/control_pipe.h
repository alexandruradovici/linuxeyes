/*****************************************************************
|
|      XAudio Player GUI. Control Driver, fork() implementation
|
|      (c) 1997 Gilles Boccon-Gibod. bok@bok.net
|
 ****************************************************************/

#ifndef __CONTROL_PIPE_H__
#define __CONTROL_PIPE_H__

/*----------------------------------------------------------------------
|       includes
+---------------------------------------------------------------------*/
#include <sys/types.h>

/*----------------------------------------------------------------------
|       types
+---------------------------------------------------------------------*/
struct XA_MessageQueue;

struct XA_Control {
    pid_t                   decoder_pid;
    pid_t                   feedback_pid;
    int                     command_read_pipe;
    int                     command_write_pipe;
    int                     feedback_read_pipe;
    int                     feedback_write_pipe;
    struct XA_MessageQueue *command_queue;
    struct XA_MessageQueue *feedback_queue;
    struct {
        XA_ControlMessageHandler  procedure;
        void                     *client;
    }                       handler;
};

#endif /* __CONTROL_PIPE_H__    */
