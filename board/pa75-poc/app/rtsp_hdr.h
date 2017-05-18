/*
 * WARNING: do not edit, this file was automatically generated.
 */

#ifndef __RTPS_HDR_H__
#define __RTPS_HDR_H__

#include <stdint.h>

enum {
	HDR_RTSP_1_0 = 1,
	HDR_ACCEPT = 2,
	HDR_ACCEPT_CHARSET = 3,
	HDR_ACCEPT_ENCODING = 4,
	HDR_ACCEPT_LANGUAGE = 5,
	HDR_ALLOW = 6,
	HDR_AUTHORIZATION = 7,
	HDR_BANDWIDTH = 8,
	HDR_BLOCKSIZE = 9,
	HDR_CACHE_CONTROL = 10,
	HDR_CONFERENCE = 11,
	HDR_CONNECTION = 12,
	HDR_CONTENT_BASE = 13,
	HDR_CONTENT_ENCODING = 14,
	HDR_CONTENT_LANGUAGE = 15,
	HDR_CONTENT_LENGTH = 16,
	HDR_CONTENT_LOCATION = 17,
	HDR_CONTENT_TYPE = 18,
	HDR_CSEQ = 19,
	HDR_DATE = 20,
	HDR_EXPIRES = 21,
	HDR_FROM = 22,
	HDR_IF_MODIFIED_SINCE = 23,
	HDR_LAST_MODIFIED = 24,
	HDR_PROXY_AUTHENTICATE = 25,
	HDR_PROXY_REQUIRE = 26,
	HDR_PUBLIC = 27,
	HDR_RANGE = 28,
	HDR_REFERER = 29,
	HDR_REQUIRE = 30,
	HDR_RETRY_AFTER = 31,
	HDR_RTP_INFO = 32,
	HDR_SCALE = 33,
	HDR_SESSION = 34,
	HDR_SERVER = 35,
	HDR_SPEED = 36,
	HDR_SUPPORTED = 37,
	HDR_TIMESTAMP = 38,
	HDR_TRANSPORT = 39,
	HDR_UNSUPPORTED = 40,
	HDR_USER_AGENT = 41,
	HDR_VIA = 42,
	HDR_WWW_AUTHENTICATE = 43,
	HDR_X_ACCEPT_AUTHENTICATION = 44,
	HDR_CLIENT_CHALLENGE = 45,
	HDR_CLIENT_ID = 46,
	HDR_PLAYER_STARTTIME = 47,
	HDR_COMPANY_ID = 48,
	HDR_GUID = 49,
	HDR_REGION_DATA = 50,
	HDR_RTSP_DESCRIBE = 51,
	HDR_RTSP_ANNOUNCE = 52,
	HDR_RTSP_GET_PARAMETER = 53,
	HDR_RTSP_OPTIONS = 54,
	HDR_RTSP_PAUSE = 55,
	HDR_RTSP_PLAY = 56,
	HDR_RTSP_RECORD = 57,
	HDR_RTSP_REDIRECT = 58,
	HDR_RTSP_SETUP = 59,
	HDR_RTSP_SET_PARAMETER = 60,
	HDR_RTSP_TEARDOWN = 61
};

enum {
	RTSP_DESCRIBE = 1,
	RTSP_ANNOUNCE = 2,
	RTSP_GET_PARAMETER = 3,
	RTSP_OPTIONS = 4,
	RTSP_PAUSE = 5,
	RTSP_PLAY = 6,
	RTSP_RECORD = 7,
	RTSP_REDIRECT = 8,
	RTSP_SETUP = 9,
	RTSP_SET_PARAMETER = 10,
	RTSP_TEARDOWN = 11
};

enum {
	RTSP_CONTINUE = 100,
	RTSP_OK = 200,
	RTSP_CREATED = 201,
	RTSP_ACCEPTED = 202,
	RTSP_BADREQUEST = 400,
	RTSP_AUTHORIZATION_REQUIRED = 401,
	RTSP_FORBIDDEN = 403,
	RTSP_NOTFOUND = 404,
	RTSP_NOTACCEPTABLE = 406,
	RTSP_UNSUPPORTEDMEDIA = 415,
	RTSP_PARAMETERNOTUNDERSTOOD = 451,
	RTSP_NOTENOUGHBANDWIDTH = 453,
	RTSP_SESSIONNOTFOUND = 454,
	RTSP_INVALIDMETHODINSTATE = 455,
	RTSP_HEADERFIELDNOTVALIDFORRESOURCE = 456,
	RTSP_INVALIDRANGE = 457,
	RTSP_AGGREGATENOTALLOWED = 459,
	RTSP_AGGREGATEONLY = 460,
	RTSP_UNSUPPORTEDTRANSPORT = 461,
	RTSP_INTERNALSERVERERROR = 500,
	RTSP_NOTIMPLEMENTED = 501,
	RTSP_SERVICEUNAVAILABLE = 503,
	RTSP_VERSIONNOTSUPPORTED = 505,
	RTSP_OPTIONNOTSUPPORTED = 551
};

extern const char * rtsp_hdr_name[];

#ifdef __cplusplus
extern "C" {
#endif

unsigned int rtsp_hdr_id(const char * s);

unsigned int rtsp_parse_hdr(const char * buf, char ** val);

const char * rtsp_reason_phrase(unsigned int code);

#ifdef __cplusplus
}
#endif

#endif /* __RTSP_HDR_H__ */