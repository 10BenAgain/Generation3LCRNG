#ifndef RNG_H
#define RNG_H

#include <stdint.h>
#include <stdio.h>

/* Found by calculating the modular multiplicative inverse of the LCRNG prime numbers
 * We know that Next Seed = (a * Last Seed + C) % m
 * Where m is the modulus (2^32)
 * a is the multiplier (0x41C64E6D)
 * c is the increment (0x6073)
 * Using the extended Euclidean algorithm we can say that ax + by = gcd(a,b)
 * 0x4702CBA * (2^32 + 1) + -289805467 * 0x41C64E6D = 1
 * Since gcd(a, b) in this case is 1, we can use ax = 1 (mod m) to calculate the inverse
 * It becomes the value we need to multiply the multiplier by so that the remainder of that number divided by mod m is 1
*/

#define MULTIPLIER  0x41C64E6D
#define INCREMENT   0x6073
#define MOD         4294967295 //2^32
#define AINVERSE    0xEEB9EB65
#define CINVERSE    0xA3561A1
#define IV_MASK     0x1F
#define IV_SHIFT    5

void increment_seed(uint32_t *seed, uint32_t advances);
void decrement_seed(uint32_t *seed, uint32_t advances);
void method1_generate(uint32_t seed, uint32_t *PID, uint8_t *nature, uint8_t *ability, uint8_t *IVs);
void check_seed(uint32_t *seed);

uint32_t next_seed(const uint32_t *seed);
uint16_t nextUShort(uint16_t max, uint32_t seed);

#endif