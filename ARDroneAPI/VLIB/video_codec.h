#ifndef _VLIB_H_
#define _VLIB_H_

#include <VLIB/video_controller.h>

#define VLIB_DEFAULT_BITRATE          (100) /* In kb/s */

struct _video_codec_t {
  encode_blockline_fc encode_blockline;
  decode_blockline_fc decode_blockline;
  update_fc           update;
  cache_stream_fc     cache_stream;
};

/******** Available codecs ********/
typedef enum _codec_type_t {
  NULL_CODEC    = 0,
  UVLC_CODEC,
  MJPEG_CODEC,
  P263_CODEC
} codec_type_t;

/******** API ********/
C_RESULT video_codec_open( video_controller_t* controller, codec_type_t codec_type );
C_RESULT video_codec_close( video_controller_t* controller );

// Encode/Decode a complete picture given 
C_RESULT video_encode_picture( video_controller_t* controller, const vp_api_picture_t* picture, bool_t* got_image );
C_RESULT video_decode_picture( video_controller_t* controller, vp_api_picture_t* picture, video_stream_t* ex_stream, bool_t* got_image );

// Encode/Decode a blockline
static INLINE C_RESULT video_encode_blockline( video_controller_t* controller, const vp_api_picture_t* blockline, bool_t picture_complete )
{
  return controller->video_codec->encode_blockline( controller, blockline, picture_complete );
}

static INLINE C_RESULT video_decode_blockline( video_controller_t* controller, vp_api_picture_t* blockline, bool_t* got_image )
{
  return controller->video_codec->decode_blockline( controller, blockline, got_image );
}

#endif // _VLIB_H_
