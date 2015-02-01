/*
 * Copyright (c) 2015 Richard B Tilley <brad@w8rbt.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * fake.hpp - Contains functions to generate fake pads.
 *            Nothing here is used in the encryption or
 *            decryption process.
 *
 */


#include <cstdint>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include "main.hpp"


std::random_device                           rd;
std::mt19937                                 rng;
std::uniform_int_distribution<std::uint8_t>  dist( 0, characters.size() -1 );


std::uint32_t combine( const std::uint32_t rd, const std::uint32_t ur, const std::uint32_t tm )
{
    // Combine integers. Return seed for the Mersenne Twister
    // Seed must be unsigned.
    std::uint32_t seed = (rd ^ ur) ^ tm;

    if( DEBUG )
    {
        std::cout << "combine - rd: "   << rd   << "\n";
        std::cout << "combine - ur: "   << ur   << "\n";
        std::cout << "combine - tm: "   << tm   << "\n";
        std::cout << "combine - seed: " << seed << "\n";
    }

    return seed;
}


std::uint32_t urandom()
{
    // Return 4 bytes of random data as an int or 0
    std::uint32_t rand = 0;
    char buffer[ sizeof(rand) ];

    std::ifstream rb( "/dev/urandom", std::ifstream::binary );
    if( rb.is_open() )
    {
        rb.read( buffer, sizeof(rand) );
        rb.close();

        rand = *reinterpret_cast<std::uint32_t*>(buffer);
    }

    if( DEBUG )
    {
        std::cout << "urandom - rand: " << rand << "\n";
    }

    return rand;
}


std::uint8_t random_char()
{
    // Return pseudo random int
    return dist(rng);
}


std::string extend( const std::string& short_str, const std::string& str )
{
    // Extend short_str with random characters to the size of str
    std::string tmp = short_str;
    
    while( tmp.size() != str.size() )
    {
        tmp.push_back( characters[random_char()] );
    }

    return tmp;
}


void gen_fake_pad( const std::string& fake_msg, const std::string& cipher_text )
{
    // Generate a fake pad
    std::string fake_pad( extend( "", cipher_text ) );

    get_ints( fake_msg,   ptxt_ints );
    get_ints( cipher_text, ctxt_ints );

    std::string::const_iterator chit, fmit, tmit;

    for( chit = characters.begin(); chit != characters.end(); ++chit )
    {
        std::string tmp_pad( cipher_text.size(), *chit );
        std::string tmp_msg;

        get_ints( tmp_pad, pad_ints  );
        sub_ints = subtract_vectors( ctxt_ints, pad_ints );

        for( subit = sub_ints.begin(); subit != sub_ints.end(); ++subit )
        {
            tmp_msg.push_back( decrypt( *subit, the_numbs ) );
        }

        for( std::uint32_t i = 0; i != fake_msg.size(); ++i )
        {
            if( fake_msg[i] == tmp_msg[i] )
            {
                fake_pad[i] = *chit;
            }
        }
    }

    if( DEBUG )
    {
        std::cout << "gen_fake_pad - fake_msg: "    << fake_msg    << "\n";
        std::cout << "gen_fake_pad - fake_pad: "    << fake_pad    << "\n";
        std::cout << "gen_fake_pad - cipher_text: " << cipher_text << "\n";
    }

    std::cout << "FakePad: " << fake_pad << "\n";
}

