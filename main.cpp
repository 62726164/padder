/*
 * Copyright (c) 2015 Richard B Tilley <btilley@gatech.edu>
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
#include <ctime>
#include <iostream>

#include "bop.hpp"
#include "fake.hpp"
#include "main.hpp"
#include "test.hpp"


int main( int argc, char* argv[] )
{
    vec flags;
    load_flags( argc, argv, flags );

    if( std::find( flags.begin(), flags.end(), "-D" ) != flags.end() )
    {
        DEBUG = true;
    }

    if( std::find( flags.begin(), flags.end(), "-d" ) != flags.end() )
    {
        DECRYPT = true;
    }

    if( std::find( flags.begin(), flags.end(), "-e" ) != flags.end() )
    {
        ENCRYPT = true;
    }

    if( std::find( flags.begin(), flags.end(), "-f" ) != flags.end() )
    {
        FAKEPAD = true;
        rng.seed( combine( rd(), urandom(), (std::uint32_t)std::time(nullptr) ) );

        if( DEBUG )
        {
            std::cout << "main - rd size: " << sizeof(rd())               << "\n";
            std::cout << "main - ur size: " << sizeof(urandom())          << "\n";
            std::cout << "main - tm size: " << sizeof(std::time(nullptr)) << "\n";
        }
    }

    if( argc == 1 || std::find( flags.begin(), flags.end(), "-h" ) != flags.end() )
    {
        std::cout << usage;
        return 0;
    }

    if( std::find( flags.begin(), flags.end(), "-t" ) != flags.end() )
    {
        test();
        return 0;
    }

    if( std::find( flags.begin(), flags.end(), "-v" ) != flags.end() )
    {
        std::cout << version << "\n";
        return 0;
    }

    // Get msg and make sure it only contains valid chars
    if( get_value( flags, "-m", msg ) )
    {
        if( !good_string( msg ) )
        {
            std::cerr << "The msg contains invalid characters.\n";
            return 1;
        }
    }
    else
    {
        std::cerr << "Unable to read msg.\n";
        return 1;
    }

    // Get pad and make sure it only contains valid chars
    if( !FAKEPAD )
    {
        if( get_value( flags, "-p", pad ) )
        {
            if( !good_string( pad ) )
            {
                std::cerr << "The pad contains invalid characters.\n";
                return 1;
            }
        }
        else
        {
            std::cerr << "Unable to read pad.\n";
            return 1;
        }
    }

    if( FAKEPAD )
    {
        pad = "none";
        if( get_value( flags, "-c", cph ) )
        {
            if( !good_string( cph ) )
            {
                std::cerr << "The ciphertext contains invalid characters.\n";
                return 1;
            }
        }
        else
        {
            std::cerr << "Unable to read ciphertext.\n";
            return 1;
        }
    }

    // Sanity Checks
    if( ENCRYPT && DECRYPT )
    {
        std::cerr << "Specify either -e (encrypt) or -d (decrypt), not both.\n";
        return 1;
    }

    if( !FAKEPAD )
    {
        if( !good_size( msg, pad ) )
        {
            std::cerr << "The pad is too short. It must be equal to or larger than the message!\n";
            return 1;
        }
    }

    if( FAKEPAD )
    {
        if( !good_size( msg, cph ) )
        {
            std::cerr << "The ciphertext is too short. It must be equal to or larger than the message!\n";
            return 1;
        }
    }

    if( DEBUG )
    {
        std::cout << "main - msg: "     << msg            << "\n";
        std::cout << "main - Pad: "     << pad            << "\n";
        std::cout << "main - ENCRYPT: " << std::boolalpha << ENCRYPT <<"\n";
        std::cout << "main - DECRYPT: " << std::boolalpha << DECRYPT <<"\n";
        std::cout << "main - FAKEPAD: " << std::boolalpha << FAKEPAD <<"\n";
    }

    // Encrypt
    if( ENCRYPT )
    {
        // Get ints from msg and pad
        get_ints( msg, ptxt_ints );
        get_ints( pad, pad_ints );

        add_ints = add_vectors( ptxt_ints, pad_ints );

        for( addit = add_ints.begin(); addit != add_ints.end(); ++addit )
        {
            out.push_back( encrypt( *addit, the_numbs ) );
        }

        std::cout << "CipherText: " << out << "\n";
    }

    // Decrypt
    if( DECRYPT )
    {
        // Get ints from msg and pad
        get_ints( msg, ctxt_ints );
        get_ints( pad, pad_ints );

        sub_ints = subtract_vectors( ctxt_ints, pad_ints );

        for( subit = sub_ints.begin(); subit != sub_ints.end(); ++subit )
        {
            out.push_back( decrypt( *subit, the_numbs ) );
        }

        std::cout << "PlainText: " << out << "\n";
    }

    // Fake
    if( FAKEPAD )
    {
        gen_fake_pad( msg, cph );
    }

    return 0;
}

