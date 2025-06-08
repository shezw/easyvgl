//
// Created by 志伟佘 on 2023/7/26.
//
#include <string.h>
#include "http.h"

int http_hex2dec(char c)
{
    if ('0' <= c && c <= '9')
    {
        return c - '0';
    }
    else if ('a' <= c && c <= 'f')
    {
        return c - 'a' + 10;
    }
    else if ('A' <= c && c <= 'F')
    {
        return c - 'A' + 10;
    }
    else
    {
        return -1;
    }
}

char http_dec2hex(short int c)
{
    if (0 <= c && c <= 9)
    {
        return c + '0';
    }
    else if (10 <= c && c <= 15)
    {
        return c + 'A' - 10;
    }
    else
    {
        return -1;
    }
}

//编码一个参数（out_url的大小需要 >= url大小 + 特殊字符 * 3 ）
void http_bbt_urlencode(char *url, char *out_url)
{
    int i = 0;
    int len = strlen(url);
    int res_len = 0;
    for (i = 0; i < len; ++i)
    {
        char c = url[i];
        if (    ('0' <= c && c <= '9') ||
                ('a' <= c && c <= 'z') ||
                ('A' <= c && c <= 'Z') )
        {
            out_url[res_len++] = c;
        }
        else
        {
            int j = (short int)c;
            if (j < 0)
                j += 256;
            int i1, i0;
            i1 = j / 16;
            i0 = j - i1 * 16;
            out_url[res_len++] = '%';
            out_url[res_len++] = http_dec2hex(i1);
            out_url[res_len++] = http_dec2hex(i0);
        }
    }
    out_url[res_len] = '\0';
}

void http_test_post(void)
{
    struct http_opts opts = {
            .data = "key1=value1&key2=value2",
    };
    struct http_response *resp = http_request("POST", "https://easyvgl.com/", &opts);
    debug_response_print(resp);
    http_response_free(resp);
}

void http_test_json(void)
{
    struct http_opts opts = {
            .json = "{\"key1\": \"value1\", \"key2\": \"value2\"}",
    };
    struct http_response *resp = http_request("PUT", "https://easyvgl.com/", &opts);
    debug_response_print(resp);
    http_response_free(resp);
}

void http_test_timeout(void)
{
    struct http_opts opts = {
            .timeout_secs = 1
    };
    struct http_response *resp = http_request("GET", "https://easyvgl.com/", &opts);
    debug_response_print(resp);
    http_response_free(resp);
}

int main(void)
{
    // Test URL encoding
    char url[] = "https://easyvgl.com/";
    char encoded_url[256];
    http_bbt_urlencode(url, encoded_url);
    printf("Encoded URL: %s\n", encoded_url);

    // Test HTTP POST request
    http_test_post();

    // Test HTTP JSON request
    http_test_json();

    // Test HTTP timeout
    http_test_timeout();

    return 0;
}