/*
 * WARNING: do not edit, this file was automatically generated.
 */

#ifndef __HTTP_HDR_H__
#define __HTTP_HDR_H__

#include <stdint.h>

enum {
	HTTP_HDR_ACCEPT = 1,
	HTTP_HDR_ACCEPT_CHARSET = 2,
	HTTP_HDR_ACCEPT_ENCODING = 3,
	HTTP_HDR_ACCEPT_LANGUAGE = 4,
	HTTP_HDR_ACCEPT_RANGES = 5,
	HTTP_HDR_AGE = 6,
	HTTP_HDR_ALLOW = 7,
	HTTP_HDR_AUTHORIZATION = 8,
	HTTP_HDR_CACHE_CONTROL = 9,
	HTTP_HDR_CONNECTION = 10,
	HTTP_HDR_CONTENT_DISPOSITION = 11,
	HTTP_HDR_CONTENT_ENCODING = 12,
	HTTP_HDR_CONTENT_LANGUAGE = 13,
	HTTP_HDR_CONTENT_LENGTH = 14,
	HTTP_HDR_CONTENT_LOCATION = 15,
	HTTP_HDR_CONTENT_MD5 = 16,
	HTTP_HDR_CONTENT_RANGE = 17,
	HTTP_HDR_CONTENT_TYPE = 18,
	HTTP_HDR_COOKIE = 19,
	HTTP_HDR_DATE = 20,
	HTTP_HDR_ETAG = 21,
	HTTP_HDR_EXPECT = 22,
	HTTP_HDR_EXPIRES = 23,
	HTTP_HDR_FROM = 24,
	HTTP_HDR_HOST = 25,
	HTTP_HDR_IF_MATCH = 26,
	HTTP_HDR_IF_MODIFIED_SINCE = 27,
	HTTP_HDR_IF_NONE_MATCH = 28,
	HTTP_HDR_IF_RANGE = 29,
	HTTP_HDR_IF_UNMODIFIED_SINCE = 30,
	HTTP_HDR_LAST_MODIFIED = 31,
	HTTP_HDR_LOCATION = 32,
	HTTP_HDR_MAX_FORWARDS = 33,
	HTTP_HDR_ORIGIN = 34,
	HTTP_HDR_PRAGMA = 35,
	HTTP_HDR_PROXY_AUTHENTICATE = 36,
	HTTP_HDR_PROXY_AUTHORIZATION = 37,
	HTTP_HDR_RANGE = 38,
	HTTP_HDR_REFERER = 39,
	HTTP_HDR_RETRY_AFTER = 40,
	HTTP_HDR_SERVER = 41,
	HTTP_HDR_SET_COOKIE = 42,
	HTTP_HDR_SET_COOKIE2 = 43,
	HTTP_HDR_TE = 44,
	HTTP_HDR_TRAILER = 45,
	HTTP_HDR_TRANSFER_ENCODING = 46,
	HTTP_HDR_UPGRADE = 47,
	HTTP_HDR_UPGRADE_INSECURE_REQUESTS = 48,
	HTTP_HDR_USER_AGENT = 49,
	HTTP_HDR_VARY = 50,
	HTTP_HDR_VIA = 51,
	HTTP_HDR_WARNING = 52,
	HTTP_HDR_WWW_AUTHENTICATE = 53,
	HTTP_HDR_X_REQUESTED_WITH = 54,
	HTTP_HDR_UA_CPU = 55
};

enum {
	HTTP_CONTINUE = 100,
	HTTP_SWITCHING_PROTOCOLS = 101,
	HTTP_OK = 200,
	HTTP_CREATED = 201,
	HTTP_ACCEPTED = 202,
	HTTP_NON_AUTHORITATIVE_INFORMATION = 203,
	HTTP_NO_CONTENT = 204,
	HTTP_RESET_CONTENT = 205,
	HTTP_PARTIAL_CONTENT = 206,
	HTTP_MULTIPLE_CHOICES = 300,
	HTTP_MOVED_PERMANENTLY = 301,
	HTTP_FOUND = 302,
	HTTP_SEE_OTHER = 303,
	HTTP_NOT_MODIFIED = 304,
	HTTP_USE_PROXY = 305,
	HTTP_TEMPORARY_REDIRECT = 307,
	HTTP_BAD_REQUEST = 400,
	HTTP_UNAUTHORIZED = 401,
	HTTP_PAYMENT_REQUIRED = 402,
	HTTP_FORBIDDEN = 403,
	HTTP_NOT_FOUND = 404,
	HTTP_METHOD_NOT_ALLOWED = 405,
	HTTP_NOT_ACCEPTABLE = 406,
	HTTP_PROXY_AUTHENTICATION_REQUIRED = 407,
	HTTP_REQUEST_TIME_OUT = 408,
	HTTP_CONFLICT = 409,
	HTTP_GONE = 410,
	HTTP_LENGTH_REQUIRED = 411,
	HTTP_PRECONDITION_FAILED = 412,
	HTTP_REQUEST_ENTITY_TOO_LARGE = 413,
	HTTP_REQUEST_URI_TOO_LARGE = 414,
	HTTP_UNSUPPORTED_MEDIA_TYPE = 415,
	HTTP_REQUESTED_RANGE_NOT_SATISFIABLE = 416,
	HTTP_EXPECTATION_FAILED = 417,
	HTTP_INTERNAL_SERVER_ERROR = 500,
	HTTP_NOT_IMPLEMENTED = 501,
	HTTP_BAD_GATEWAY = 502,
	HTTP_SERVICE_UNAVAILABLE = 503,
	HTTP_GATEWAY_TIME_OUT = 504,
	HTTP_VERSION_NOT_SUPPORTED = 505
};

extern const char * http_hdr_name[];

#ifdef __cplusplus
extern "C" {
#endif

unsigned int http_hdr_id(const char * s);

unsigned int http_parse_field(const char * buf, char ** val);

unsigned int http_parse_content_type(const char * str, char ** endptr);

const char * http_reason_phrase(unsigned int code);

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_HDR_H__ */
