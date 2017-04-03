# padder

Padder is a one-time pad software implementation intended for educational 
purposes and experimentation. It can be used to encrypt and decrypt small 
messages. Padder can also be used to generate fake pads and fake messages.

## Warning

Padder should not be used in real-world situations that require encryption. If 
you need strong message encryption, do not use padder. Use a well-regarded,
open-source OpenPGP implementation such as GnuPG (https://gnupg.org/).

## The Padder Character Set
```bash
abcdefghijklmnopqrstuvwxyz0123456789-
```

## Encryption

$ padder -e -m black -p e7vwd
CipherText: fhvyn

## Decryption

$ padder -d -m fhvyn -p e7vwd
PlainText: black

## Fake Message and Pad Generation
 
$ padder -f -m white -c fhvyn
FakePad: uanfj

## Message Transmission

The Padder Character Set was selected specifically for message transmission 
over radio (HF, VHF, UHF). However, messages can be transmitted in other ways. 
Twitter, text messages, phone calls and website forums could all be used to 
send and receive messages. Encrypted messages could also be embedded in image 
tags, HTML, or some other inconspicuous place.

## Decrypt the Same Ciphertext to Multiple Plaintexts

One-time pad encrypted messages can be decrypted to virtually any plaintext 
message by using different pads. This feature is useful for creating 
diversions. It may also provide for plausible deniability. This requires two 
(or more) sets of pads.  

    Real Message

        ptxt: we-are-moving-north-and-will-attack-at-the-pass
        ctxt: c2wrbumxvj8gob34mxn46pxg29a6kxnwfhcaam3en-hr-2v 
        pad:  ryxrvqnlhz04icqq6eg56cuhg10vlx5dff3ba44wg6ic-kd

    Fake Message

        ptxt: our-group-fled-south-to-the-city-we-sailed-east 
        ctxt: c2wrbumxvj8gob34mxn46pxg29a6kxnwfhcaam3en-hr-2v 
        pad:  zifs6d9dgk36k94m9d5x77jhj277ip59gw9btmv4j7in-kc

## Security Considerations & Precautions

Pads must be random, kept secret, only used once and destroyed immediately 
after use. Should the same pad be used to encrypt more than one message, those 
messages will be cracked. Should the pads become lost or stolen, then all the 
messages should be suspect.

You must assume that the attacker intercepts and stores all of your ciphertext 
messages indefinitely. He hopes to somehow obtain the pads so that he can 
decrypt the messages someday. 

When used with appropriate procedures and precautions, one-time pad encrypted 
messages cannot be cracked. However, how the ciphertext message is sent and 
received may identify the communicating parties. This may or may not be an 
acceptable risk in your environment. For example, if a person posted a padder 
encrypted message to a Twitter account, the IP address, user name and date/time 
would be logged and stored. And, any IP address that read the message would be 
logged and stored too. Basically, any transmission method that uses a network 
(cellular, IP, etc.) may quickly reveal the location of the communicating 
parties. 

Radio signals are directional and can be tracked. However, radio signals don't 
rely on network infrastructure and require more expensive equipment and greater 
technical knowledge to track. With radio you only know the general time and 
direction from which the signal emanated. Also, it's relatively easy to hide 
the source of radio signals when the transmitter is moving around in densely 
populated areas. The reception of radio signals cannot be tracked. Stations in 
range of the signal may relay the messages to stations out of range.

One-time pad encrypted messages are not authenticated. 

## General Notes

Plaintext messages, pads and ciphertext messages must only contain characters 
from the Padder Character Set. Capitalization, punctuation and spaces are not 
allowed. When creating plaintext messages, use the dash symbol '-' rather than 
spaces to separate words. this-is-an-example-plaintext-message

The pad must be as long or longer than the message. The sender and receiver 
should have the same numbered list of pads and know in which order to use them. 
As a simplified example, there could be 31 pads for the month of January. The 
January 1st message would use pad number 1 for that day's message.  

Padder is only intended for educational purposes and experimentation.

