/*****************************************************************
|
|      Memory Buffer Input Module
|
|      (c) 1996-2000 Xaudio Corporation
|      Author: Gilles Boccon-Gibod (gilles@xaudio.com)
|
 ****************************************************************/

#ifndef __MEMORY_INPUT_H__
#define __MEMORY_INPUT_H__

/*----------------------------------------------------------------------
|       includes
+---------------------------------------------------------------------*/
#include "decoder.h"

/*----------------------------------------------------------------------
|       prototypes
+---------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

int XA_EXPORT memory_input_feed(XA_InputInstance *input, 
                                const unsigned char *data, 
                                unsigned int nb_bytes);
int XA_EXPORT memory_input_flush(XA_InputInstance *input);
int XA_EXPORT memory_input_module_register(XA_InputModule *module);

#ifdef __cplusplus
}
#endif
 
#endif /* __MEMORY_INPUT_H__ */
