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

#include <iostream>
#include <string>
#include "main.hpp"

bool  pass                  = true;

const std::string test_ctxt = "nxec-3usexfnb7ayf8r6heqbi9jblny7zbyu3q42jrt0dphnd";
const std::string test_ptxt = "the-only-correct-view-is-the-absence-of-all-views";
const std::string test_pad  = "5qadwqj5fv27v39fgnj2wfiujqc8mnxpvzwq4cz3jgi1thd2w";

void test()
{
    if( DEBUG )
    {
        std::cout << "test_pad:  " << test_pad << "\n";
    }

    // Get ints from plaintext and pad
    get_ints( test_ptxt, ptxt_ints );
    get_ints( test_pad,  pad_ints );

    // Encrypt
    add_ints = add_vectors( ptxt_ints, pad_ints );

    for( addit = add_ints.begin(); addit != add_ints.end(); ++addit )
    {
        out.push_back( encrypt( *addit, the_numbs ) );
    }

    if( DEBUG )
    {
        std::cout << "test_ctxt: " << test_ctxt << "\n";
        std::cout << "gene_ctxt: " << out       << "\n";
    }

    if( test_ctxt != out )
    {
        pass = false;
    }

    // ------------------------------------------
    out.clear();

    // Get ciphertext ints
    // No need to reload pad_ints
    // They were loaded above and are unchanged
    get_ints( test_ctxt, ctxt_ints );

    // Decrypt
    sub_ints = subtract_vectors( ctxt_ints, pad_ints );

    for( subit = sub_ints.begin(); subit != sub_ints.end(); ++subit )
    {
        out.push_back( decrypt( *subit, the_numbs ) );
    }

    if( DEBUG )
    {
        std::cout << "test_ptxt: " << test_ptxt << "\n";
        std::cout << "gene_ptxt: " << out       << "\n";
    }

    if( test_ptxt != out )
    {
        pass = false;
    }

    // Show test results
    if( pass )
    {
        std::cout << version << " All tests passed.\n";
    }
    else
    {
        std::cout << version << " Some tests failed!\n";
    }
}

