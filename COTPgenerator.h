//
// Created by jurandi on 21-06-2023.
//
/*
MIT License
Copyright (c) 2023 OUI

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef COTP_GENERATOR
#define COTP_GENERATOR

#ifndef SHA_256_H
#define SHA_256_H


#include <stdint.h>
#include <string.h>



/*
 * @brief Size of the SHA-256 sum. This times eight is 256 bits.
 */
#define SIZE_OF_SHA_256_HASH 32

/*
 * @brief Size of the chunks used for the calculations.
 *
 * @note This should mostly be ignored by the user, although when using the streaming API, it has an impact for
 * performance. Add chunks whose size is a multiple of this, and you will avoid a lot of superfluous copying in RAM!
 */
#define SIZE_OF_SHA_256_CHUNK 64

/*
 * @brief The opaque SHA-256 type, that should be instantiated when using the streaming API.
 *
 * @note Although the details are exposed here, in order to make instantiation easy, you should refrain from directly
 * accessing the fields, as they may change in the future.
 */
struct Sha_256 {
    uint8_t *hash;
    uint8_t chunk[SIZE_OF_SHA_256_CHUNK];
    uint8_t *chunk_pos;
    size_t space_left;
    size_t total_len;
    uint32_t h[8];
};

/*
 * @brief The simple SHA-256 calculation function.
 * @param hash Hash array, where the result is delivered.
 * @param input Pointer to the data the hash shall be calculated on.
 * @param len Length of the input data, in byte.
 *
 * @note If all of the data you are calculating the hash value on is available in a contiguous buffer in memory, this is
 * the function you should use.
 *
 * @note If either of the passed pointers is NULL, the results are unpredictable.
 */
void calc_sha_256(uint8_t hash[SIZE_OF_SHA_256_HASH], const void *input, size_t len);

/*
 * @brief Initialize a SHA-256 streaming calculation.
 * @param sha_256 A pointer to a SHA-256 structure.
 * @param hash Hash array, where the result will be delivered.
 *
 * @note If all of the data you are calculating the hash value on is not available in a contiguous buffer in memory, this is
 * where you should start. Instantiate a SHA-256 structure, for instance by simply declaring it locally, make your hash
 * buffer available, and invoke this function. Once a SHA-256 hash has been calculated (see further below) a SHA-256
 * structure can be initialized again for the next calculation.
 *
 * @note If either of the passed pointers is NULL, the results are unpredictable.
 */
void sha_256_init(struct Sha_256 *sha_256, uint8_t hash[SIZE_OF_SHA_256_HASH]);

/*
 * @brief Stream more input data for an on-going SHA-256 calculation.
 * @param sha_256 A pointer to a previously initialized SHA-256 structure.
 * @param data Pointer to the data to be added to the calculation.
 * @param len Length of the data to add, in byte.
 *
 * @note This function may be invoked an arbitrary number of times between initialization and closing, but the maximum
 * data length is limited by the SHA-256 algorithm: the total number of bits (i.e. the total number of bytes times
 * eight) must be representable by a 64-bit unsigned integer. While that is not a practical limitation, the results are
 * unpredictable if that limit is exceeded.
 *
 * @note This function may be invoked on empty data (zero length), although that obviously will not add any data.
 *
 * @note If either of the passed pointers is NULL, the results are unpredictable.
 */
void sha_256_write(struct Sha_256 *sha_256, const void *data, size_t len);

/*
 * @brief Conclude a SHA-256 streaming calculation, making the hash value available.
 * @param sha_256 A pointer to a previously initialized SHA-256 structure.
 * @return Pointer to the hash array, where the result is delivered.
 *
 * @note After this function has been invoked, the result is available in the hash buffer that initially was provided. A
 * pointer to the hash value is returned for convenience, but you should feel free to ignore it: it is simply a pointer
 * to the first byte of your initially provided hash array.
 *
 * @note If the passed pointer is NULL, the results are unpredictable.
 *
 * @note Invoking this function for a calculation with no data (the writing function has never been invoked, or it only
 * has been invoked with empty data) is legal. It will calculate the SHA-256 value of the empty string.
 */
uint8_t *sha_256_close(struct Sha_256 *sha_256);




#define TOTAL_LEN_LEN 8

/*
 * Comments from pseudo-code at https://en.wikipedia.org/wiki/SHA-2 are reproduced here.
 * When useful for clarification, portions of the pseudo-code are reproduced here too.
 */

/*
 * @brief Rotate a 32-bit value by a number of bits to the right.
 * @param value The value to be rotated.
 * @param count The number of bits to rotate by.
 * @return The rotated value.
 */
static inline uint32_t right_rot(uint32_t value, unsigned int count)
{
    /*
     * Defined behaviour in standard C for all count where 0 < count < 32, which is what we need here.
     */
    return value >> count | value << (32 - count);
}

/*
 * @brief Update a hash value under calculation with a new chunk of data.
 * @param h Pointer to the first hash item, of a total of eight.
 * @param p Pointer to the chunk data, which has a standard length.
 *
 * @note This is the SHA-256 work horse.
 */
static inline void consume_chunk(uint32_t *h, const uint8_t *p)
{
    unsigned i, j;
    uint32_t ah[8];

    /* Initialize working variables to current hash value: */
    for (i = 0; i < 8; i++)
        ah[i] = h[i];

    /*
     * The w-array is really w[64], but since we only need 16 of them at a time, we save stack by
     * calculating 16 at a time.
     *
     * This optimization was not there initially and the rest of the comments about w[64] are kept in their
     * initial state.
     */

    /*
     * create a 64-entry message schedule array w[0..63] of 32-bit words (The initial values in w[0..63]
     * don't matter, so many implementations zero them here) copy chunk into first 16 words w[0..15] of the
     * message schedule array
     */
    uint32_t w[16];

    /* Compression function main loop: */
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 16; j++) {
            if (i == 0) {
                w[j] =
                        (uint32_t)p[0] << 24 | (uint32_t)p[1] << 16 | (uint32_t)p[2] << 8 | (uint32_t)p[3];
                p += 4;
            } else {
                /* Extend the first 16 words into the remaining 48 words w[16..63] of the
                 * message schedule array: */
                const uint32_t s0 = right_rot(w[(j + 1) & 0xf], 7) ^ right_rot(w[(j + 1) & 0xf], 18) ^
                                    (w[(j + 1) & 0xf] >> 3);
                const uint32_t s1 = right_rot(w[(j + 14) & 0xf], 17) ^
                                    right_rot(w[(j + 14) & 0xf], 19) ^ (w[(j + 14) & 0xf] >> 10);
                w[j] = w[j] + s0 + w[(j + 9) & 0xf] + s1;
            }
            const uint32_t s1 = right_rot(ah[4], 6) ^ right_rot(ah[4], 11) ^ right_rot(ah[4], 25);
            const uint32_t ch = (ah[4] & ah[5]) ^ (~ah[4] & ah[6]);

            /*
             * Initialize array of round constants:
             * (first 32 bits of the fractional parts of the cube roots of the first 64 primes 2..311):
             */
            static const uint32_t k[] = {
                    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4,
                    0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe,
                    0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f,
                    0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
                    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
                    0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
                    0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116,
                    0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
                    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7,
                    0xc67178f2};

            const uint32_t temp1 = ah[7] + s1 + ch + k[i << 4 | j] + w[j];
            const uint32_t s0 = right_rot(ah[0], 2) ^ right_rot(ah[0], 13) ^ right_rot(ah[0], 22);
            const uint32_t maj = (ah[0] & ah[1]) ^ (ah[0] & ah[2]) ^ (ah[1] & ah[2]);
            const uint32_t temp2 = s0 + maj;

            ah[7] = ah[6];
            ah[6] = ah[5];
            ah[5] = ah[4];
            ah[4] = ah[3] + temp1;
            ah[3] = ah[2];
            ah[2] = ah[1];
            ah[1] = ah[0];
            ah[0] = temp1 + temp2;
        }
    }

    /* Add the compressed chunk to the current hash value: */
    for (i = 0; i < 8; i++)
        h[i] += ah[i];
}

/*
 * Public functions. See header file for documentation.
 */

void sha_256_init(struct Sha_256 *sha_256, uint8_t hash[SIZE_OF_SHA_256_HASH])
{
    sha_256->hash = hash;
    sha_256->chunk_pos = sha_256->chunk;
    sha_256->space_left = SIZE_OF_SHA_256_CHUNK;
    sha_256->total_len = 0;
    /*
     * Initialize hash values (first 32 bits of the fractional parts of the square roots of the first 8 primes
     * 2..19):
     */
    sha_256->h[0] = 0x6a09e667;
    sha_256->h[1] = 0xbb67ae85;
    sha_256->h[2] = 0x3c6ef372;
    sha_256->h[3] = 0xa54ff53a;
    sha_256->h[4] = 0x510e527f;
    sha_256->h[5] = 0x9b05688c;
    sha_256->h[6] = 0x1f83d9ab;
    sha_256->h[7] = 0x5be0cd19;
}

void sha_256_write(struct Sha_256 *sha_256, const void *data, size_t len)
{
    sha_256->total_len += len;

    const uint8_t *p = (uint8_t*)data;

    while (len > 0) {
        /*
         * If the input chunks have sizes that are multiples of the calculation chunk size, no copies are
         * necessary. We operate directly on the input data instead.
         */
        if (sha_256->space_left == SIZE_OF_SHA_256_CHUNK && len >= SIZE_OF_SHA_256_CHUNK) {
            consume_chunk(sha_256->h, p);
            len -= SIZE_OF_SHA_256_CHUNK;
            p += SIZE_OF_SHA_256_CHUNK;
            continue;
        }
        /* General case, no particular optimization. */
        const size_t consumed_len = len < sha_256->space_left ? len : sha_256->space_left;
        memcpy(sha_256->chunk_pos, p, consumed_len);
        sha_256->space_left -= consumed_len;
        len -= consumed_len;
        p += consumed_len;
        if (sha_256->space_left == 0) {
            consume_chunk(sha_256->h, sha_256->chunk);
            sha_256->chunk_pos = sha_256->chunk;
            sha_256->space_left = SIZE_OF_SHA_256_CHUNK;
        } else {
            sha_256->chunk_pos += consumed_len;
        }
    }
}

uint8_t *sha_256_close(struct Sha_256 *sha_256)
{
    uint8_t *pos = sha_256->chunk_pos;
    size_t space_left = sha_256->space_left;
    uint32_t *const h = sha_256->h;

    /*
     * The current chunk cannot be full. Otherwise, it would already have been consumed. I.e. there is space left for
     * at least one byte. The next step in the calculation is to add a single one-bit to the data.
     */
    *pos++ = 0x80;
    --space_left;

    /*
     * Now, the last step is to add the total data length at the end of the last chunk, and zero padding before
     * that. But we do not necessarily have enough space left. If not, we pad the current chunk with zeroes, and add
     * an extra chunk at the end.
     */
    if (space_left < TOTAL_LEN_LEN) {
        memset(pos, 0x00, space_left);
        consume_chunk(h, sha_256->chunk);
        pos = sha_256->chunk;
        space_left = SIZE_OF_SHA_256_CHUNK;
    }
    const size_t left = space_left - TOTAL_LEN_LEN;
    memset(pos, 0x00, left);
    pos += left;
    size_t len = sha_256->total_len;
    pos[7] = (uint8_t)(len << 3);
    len >>= 5;
    int i;
    for (i = 6; i >= 0; --i) {
        pos[i] = (uint8_t)len;
        len >>= 8;
    }
    consume_chunk(h, sha_256->chunk);
    /* Produce the final hash value (big-endian): */
    int j;
    uint8_t *const hash = sha_256->hash;
    for (i = 0, j = 0; i < 8; i++) {
        hash[j++] = (uint8_t)(h[i] >> 24);
        hash[j++] = (uint8_t)(h[i] >> 16);
        hash[j++] = (uint8_t)(h[i] >> 8);
        hash[j++] = (uint8_t)h[i];
    }
    return sha_256->hash;
}

void calc_sha_256(uint8_t hash[SIZE_OF_SHA_256_HASH], const void *input, size_t len)
{
    struct Sha_256 sha_256;
    sha_256_init(&sha_256, hash);
    sha_256_write(&sha_256, input, len);
    (void)sha_256_close(&sha_256);
}

#endif


#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdbool.h>



int private_cotp_sanitize_range(int value, int min, int max);


void private_cotp_format_num(char *result, int num, int num_size);


void  private_cotp_calc_sha_256_generating_string(char *hash_string, const char *input);

void  private_cotp_calc_sha_256_generating_number(char *hash_string, const char *input);


void  private_cotp_sub_str(char *result, const char *element, int start_point, int end_point);

int private_cotp_int_sub_str(const char *element, int start_point, int end_point);






int cotp_minutes(int minutes);
int copt_hours(int hours);
int cotp_days(int days);





#define COTP_MAX 100

#define COTP_DESCRIPTION_SIZE 11


typedef struct COTPKeyAttributes{
    char seed[200];
    int interval;
    int password_size;
    int key_size;
    bool allow_letters_on_passowrd;

    bool allow_letters_on_key;
}COTPKeyAttributes;

void private_cotp_initialize_key_attribtes(COTPKeyAttributes *attributes, int interval);


COTPKeyAttributes newCOTPKeyAttribute(int interval, const char *secret, unsigned  long current_time);


void private_cotp_sanitize_attributes(COTPKeyAttributes *attributes);


void COTPKeyAttributes_represent_key_attributes(COTPKeyAttributes *attributes);

void cotp_create_key(
        char *key,
        COTPKeyAttributes *attributes
);





typedef struct COTParsedKey{
    char generated_sha[81];
    int interval;
    int password_size;
    bool allow_letters_on_passowrd;
}COTParsedKey;

COTParsedKey cotp_parse_key(const char *key);

void COTPParsedKey_reprsent(COTParsedKey *parsed_key);

void COTPParsedKey_get_password(COTParsedKey *parsed_key, char *password, int *time_ramaing, long actual_time);

void cotp_get_password(char *password, int *time_ramaing, const char *key, long actual_time);




int private_cotp_sanitize_range(int value, int min, int max){
    if(value < min){
        return min;
    }
    if(value > max){
        return max;
    }
    return value;
}
void  private_cotp_format_num(char *result, int num, int num_size){
    char element[11] = {0};
    sprintf(element,"%d",num);
    int element_size = (int)strlen(element);
    int zeros_to_add = num_size -element_size;
    char zeros[10] = {0};
    for(int i = 0; i < zeros_to_add; i++){
        zeros[i]  = '0';
    }
    int result_size = zeros_to_add + element_size;
    sprintf(result,"%s%s",zeros,element);
    result[result_size] = '\0';
}

void  private_cotp_calc_sha_256_generating_string(char *hash_string, const char *input){
    uint8_t hash[SIZE_OF_SHA_256_HASH];

    calc_sha_256(hash, input, strlen(input));
    for (unsigned int i = 0; i < SIZE_OF_SHA_256_HASH; i++) {
        sprintf(hash_string + i * 2, "%02x", hash[i]);
    }
}

void  private_cotp_calc_sha_256_generating_number(char *hash_string, const char *input){
    uint8_t hash[SIZE_OF_SHA_256_HASH] = {0};

    calc_sha_256(hash, input, strlen(input));

    int hash_string_size = 0;
    for (unsigned int i = 0; i < SIZE_OF_SHA_256_HASH; i++) {

        char result[5] = {0};
        sprintf(result,"%d",hash[i]);
        sprintf((hash_string + hash_string_size), "%s", result);
        hash_string_size+= (int)strlen(result);

    }
}

void private_cotp_sub_str(char *result, const char *element, int start_point, int end_point){

    int result_size = 0;
    for(int i = start_point; i < end_point; i++){

        result[result_size] = element[i];
        result_size+=1;
    }
    result[result_size] ='\0';
}

int private_cotp_int_sub_str(const char *element, int start_point, int end_point){
    char result[10]= {0};
    private_cotp_sub_str(result, element, start_point, end_point);
    int result_formated;
    sscanf(result,"%d",&result_formated);
    return result_formated;
}






int cotp_minutes(int minutes){
    return minutes * 60;
}
int copt_hours(int hours){
    return cotp_minutes(60) * hours;
}
int cotp_days(int days){
    return copt_hours(24) * days;
}





void private_cotp_initialize_key_attribtes(COTPKeyAttributes *attributes, int interval){

    attributes->allow_letters_on_key = true;
    attributes->allow_letters_on_passowrd = true;
    attributes->key_size = COTP_MAX;
    attributes->interval = interval;
    attributes->password_size = 20;

}


COTPKeyAttributes newCOTPKeyAttribute(int interval, const char *secret, unsigned  long current_time){
    COTPKeyAttributes keey_attributes = {0};
    private_cotp_initialize_key_attribtes(&keey_attributes, interval);
    sprintf(keey_attributes.seed,"%s%ld",secret,current_time);
    return keey_attributes;
}



void private_cotp_sanitize_attributes(COTPKeyAttributes *attributes){

    int min_key_size = 20 + COTP_DESCRIPTION_SIZE;
    int max_key_size = 64 + COTP_DESCRIPTION_SIZE;

    if(!attributes->allow_letters_on_key){
        max_key_size = 81 + COTP_DESCRIPTION_SIZE;
    }
    attributes->key_size = private_cotp_sanitize_range(
            attributes->key_size,
            min_key_size,
            max_key_size
    );

    int min_password_size = 5;
    int max_password_size = 64;

    if(!attributes->allow_letters_on_passowrd){
        max_password_size = 81;
    }

    attributes->password_size = private_cotp_sanitize_range(
            attributes->password_size,
            min_password_size,
            max_password_size
    );

}


void COTPKeyAttributes_represent_key_attributes(COTPKeyAttributes *attributes){
    private_cotp_sanitize_attributes(attributes);
    printf("seed: %s\n",attributes->seed);
    printf("interval: %d\n",attributes->interval);
    printf("keey size: %d\n",attributes->key_size);
    printf("password_size: %d\n",attributes->password_size);
    printf("allow letters on  key: %s\n",attributes->allow_letters_on_key? "true":"false");
    printf("allow letters on password: %s\n",attributes->allow_letters_on_passowrd? "true":"false");
}

void cotp_create_key(
        char *key,
        COTPKeyAttributes *attributes
){


    private_cotp_sanitize_attributes(attributes);
    //creating the elements

    char interval[9] = {0};
    private_cotp_format_num(interval, attributes->interval, 8);

    char password_size[3] = {0};
    private_cotp_format_num(password_size, attributes->password_size, 2);



    char sha_of_seed[82] = {0};
    char seed[82] = {0};


    if(attributes->allow_letters_on_key){

        private_cotp_calc_sha_256_generating_string(
                sha_of_seed,
                attributes->seed
        );

    }
    else{

        private_cotp_calc_sha_256_generating_number(
                sha_of_seed,
                attributes->seed
        );

    }

    private_cotp_sub_str(seed, sha_of_seed, 0, attributes->key_size - COTP_DESCRIPTION_SIZE);

    sprintf(key,
            "%s%s%s%d",
            seed,
            interval,
            password_size,
            attributes->allow_letters_on_passowrd
    );

}



COTParsedKey cotp_parse_key(const char *key){

    COTParsedKey parsed_key = {0};
    int key_size = (int)strlen(key);
    int sha_point = key_size - COTP_DESCRIPTION_SIZE;

    private_cotp_sub_str(
            parsed_key.generated_sha,
            key,
            0,
            sha_point
    );
    int interval_point = sha_point+8;
    parsed_key.interval = private_cotp_int_sub_str(key, sha_point, interval_point);
    int password_point = interval_point+2;
    parsed_key.password_size = private_cotp_int_sub_str(key, interval_point, password_point);

    parsed_key.allow_letters_on_passowrd = false;

    if(key[key_size-1] == '1'){
        parsed_key.allow_letters_on_passowrd = true;
    }



    return parsed_key;

}

void COTPParsedKey_reprsent(COTParsedKey *parsed_key){
    printf("generated sha: %s\n",parsed_key->generated_sha);
    printf("interval: %d\n",parsed_key->interval);
    printf("password size: %d\n",parsed_key->password_size);
    printf("allow letters on password: %s\n",parsed_key->allow_letters_on_passowrd? "true":"false");
}


void COTPParsedKey_get_password(COTParsedKey *parsed_key, char *password, int *time_ramaing, long actual_time){

    long last_point = (long)(actual_time / parsed_key->interval) * parsed_key->interval;
    long next_point = last_point + parsed_key->interval;
    *time_ramaing = (int)(next_point - actual_time);

    char generated_sha[82] = {0};
    char generated_seed[100] = {0};
    sprintf(generated_seed,"%s%li",parsed_key->generated_sha,last_point);


    if(parsed_key->allow_letters_on_passowrd){

        private_cotp_calc_sha_256_generating_string(generated_sha, generated_seed);

    }
    else{
        private_cotp_calc_sha_256_generating_number(generated_sha, generated_seed);
    }
    private_cotp_sub_str(password, generated_sha, 0, parsed_key->password_size);
}


void cotp_get_password(char *password, int *time_ramaing, const char *key, long actual_time){
    COTParsedKey parsed_key = cotp_parse_key(key);
    COTPParsedKey_get_password(&parsed_key, password, time_ramaing, actual_time);
}


#endif