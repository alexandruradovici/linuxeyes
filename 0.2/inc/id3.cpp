void id3 (char *name)
{
    XA_DecoderInfo *decoder;            
    XA_InputModule module;
    XA_PropertyList list;
    XA_CodecModule codec;
    decoder_new (&decoder);
    file_input_module_register(&module);
    decoder_input_module_register(decoder, &module);
    mpeg_codec_module_register(&codec);
    decoder_codec_module_register(decoder, &codec);
    decoder_input_new(decoder, name,XA_DECODER_INPUT_AUTOSELECT);
    decoder_input_open(decoder);
    if (properties_get_list(decoder->status->info.properties, &list) == 
        XA_SUCCESS &&
        list.nb_properties > 0) 
        {
	  title=list.properties[6].value.string;
	  artist=list.properties[7].value.string;
	} 
    decoder_input_close(decoder);	
    decoder_delete (decoder);	
}