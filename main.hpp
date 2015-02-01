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
 */


#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <utility> 
#include <vector>

#pragma once


bool DEBUG                   = false; 
bool DECRYPT                 = false;
bool FAKEPAD                 = false;
bool ENCRYPT                 = false;

const std::string characters = "abcdefghijklmnopqrstuvwxyz0123456789-";
const std::string version    = "padder 1.0";
const std::string usage      = version + " flags: \n \
--c  the ciphertext to generate a fake pad (requires --f)\n \
--d  decrypt the message\n \
--D  enable verbose debugging\n \
--e  encrypt the message\n \
--f  generate a fake pad (requires --c)\n \
--h  show this help\n \
--m  the message\n \
--p  the pad\n \
--t  run tests and exit\n \
--v  show version and exit\n";

std::string cph                            = "";
std::string msg                            = "";
std::string pad                            = "";
std::string out                            = "";

std::vector<std::uint8_t>                  ctxt_ints;
std::vector<std::uint8_t>                  ptxt_ints;
std::vector<std::uint8_t>                  pad_ints;

std::vector<std::int16_t>                  add_ints;
std::vector<std::int16_t>                  sub_ints;

std::vector<std::int16_t>::const_iterator  addit;
std::vector<std::int16_t>::const_iterator  subit;


bool good_string( const std::string& str )
{
    // Ensure that the str only contain valid chars
    if( DEBUG )
    {
        std::cout << "good_string - str: " << str << "\n";
    }

    std::string::const_iterator strit;

    for( strit = str.begin(); strit != str.end(); ++strit )
    {
        if ( characters.find(*strit) == std::string::npos )
        {
            return false;
        }
    }
    return true;
}


bool good_size( const std::string& min, const std::string& str )
{
    // Ensure that str is as long or longer than min.size()
    if( DEBUG )
    {
        std::cout << "good_size - min: " << min.size() << "\n";
        std::cout << "good_size - str: " << str.size()     << "\n";
    }

    if( min.size() > str.size() )
    {
        return false;
    }

    return true;
}


std::map<char, std::uint8_t> chars( const std::string& str )
{
    // map chars to ints
    // a -> 0
    // b -> 1
    // c -> 2
    // ...

    std::map<char, std::uint8_t> the_map;

    std::uint8_t count = 0;

    while( count != str.size() )
    {
        the_map.insert( std::pair<char, std::uint8_t>( str[count], count ) );
        ++count;
    }

    return the_map;
}


std::map<std::uint8_t, char> numbers( const std::string& str )
{
    // map ints to chars
    // 0 -> a
    // 1 -> b
    // 2 -> c
    // ...

    std::map<std::uint8_t, char> the_map;

    std::uint8_t count = 0;

    while( count != str.size() )
    {
        the_map.insert( std::pair<std::uint8_t, char>( count, str[count] ) );
        ++count;
    }

    return the_map;
}


char encrypt( const std::int16_t the_int, 
              const std::map<std::uint8_t, char>& numbers )
{
    std::uint8_t tmp;
    const std::int8_t limit = characters.size() - 1;

    if( the_int > limit )
    {
        tmp = ( the_int - characters.size() ) % characters.size();
    }
    else
    {
        tmp = the_int % characters.size();
    }

    return numbers.find( tmp )->second;
}


char decrypt( const std::int16_t the_int, 
              const std::map<std::uint8_t, char>& numbers )
{
    const std::uint8_t tmp = (the_int + characters.size()) % characters.size();

    return numbers.find( tmp )->second;
}


std::vector<std::int16_t> add_vectors( const std::vector<std::uint8_t>& the_msg,
                                             std::vector<std::uint8_t>& the_pad )
{
    // Encryption - Add the pad ints to the message ints.

    if( the_msg.size() > the_pad.size() )
    {
        std::cerr << "The pad is too short. It must be equal to or larger than the message!\n";
        std::cerr << the_msg.size() << " " << the_pad.size() << "\n";
        std::abort();
    }

    the_pad.resize( the_msg.size() );

    std::vector<std::int16_t> result;
    result.reserve( the_msg.size() );

    std::transform( the_msg.begin(), the_msg.end(),
                    the_pad.begin(), std::back_inserter(result), std::plus<std::int16_t>() );

    return result;
}


std::vector<std::int16_t> subtract_vectors( const std::vector<std::uint8_t>& the_msg,
                                                  std::vector<std::uint8_t>& the_pad )
{
    // Decryption - Subtract the pads ints from the message ints.
    // Operation may sometimes produce signed/negative ints

    if( the_msg.size() > the_pad.size() )
    {
        std::cerr << "The pad is too short. It must be equal to or larger than the message!\n";
        std::cerr << the_msg.size() << " " << the_pad.size() << "\n";
        std::abort();
    }

    the_pad.resize( the_msg.size() );

    std::vector<std::int16_t> result;
    result.reserve( the_msg.size() );

    std::transform( the_msg.begin(), the_msg.end(),
                    the_pad.begin(), std::back_inserter(result), std::minus<std::int16_t>() );

    return result;
}


const std::map<char, std::uint8_t> the_chars = chars( characters );
const std::map<std::uint8_t, char> the_numbs = numbers( characters );


void get_ints( const std::string& str, std::vector<std::uint8_t>& v )
{
    v.clear();

    std::map<char, std::uint8_t>::const_iterator cit;
    std::string::const_iterator                  strit;

    for( strit = str.begin(); strit != str.end(); ++strit )
    {
        cit = the_chars.find( *strit );

        if( cit != the_chars.end() )
        {
            v.push_back( cit->second );
        }
    }
}

