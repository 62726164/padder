package main

import (
	"flag"
	"fmt"
	"os"
)

func main() {
	var cflag = flag.String("c", "", "the ciphertext to create a fake pad. requires -m and -f.")
	var dflag = flag.Bool("d", false, "decrypt a message. requires -m and -p.")
	var eflag = flag.Bool("e", false, "encrypt a message. requires -m and -p.")
	var fflag = flag.Bool("f", false, "create a fake pad. requires -m and -c.")
	var help = flag.Bool("help", false, "show help and exit")
	var msg = flag.String("m", "", "the message to encrypt or decrypt.")
	var pad = flag.String("p", "", "the pad to use to encrypt or decrypt.")
	var vflag = flag.Bool("v", false, "show version and exit")

	flag.Parse()

	if *help || len(os.Args) == 1 {
		flag.PrintDefaults()
		return
	}

	if *vflag {
		fmt.Println(version)
		return
	}

	// build the i2s map
	for i, c := range chars {
		i2s[int64(i)] = string(c)
	}

	// build the s2i map
	for i, s := range i2s {
		s2i[s] = i
	}

	//genFakePad("white", "2c36e")

	if *eflag {
		if goodString(*msg) {
			if goodString(*pad) {
				if goodSize(*msg, *pad) {
					tpad := truncateStr(*msg, *pad)
					mints := getInts(*msg)
					pints := getInts(tpad)
					aints := addInts(mints, pints)

					var ctxt string = ""
					for _, i := range aints {
						ctxt += encrypt(i)
					}
					fmt.Printf("CipherText: %s\n", ctxt)
				} else {
					fmt.Printf("The pad is smaller than the msg.\n")
				}
			} else {
				fmt.Printf("The pad has invalid chars.\n")
			}
		} else {
			fmt.Printf("The msg has invalid chars.\n")
		}
	}

	if *dflag {
		if goodString(*msg) {
			if goodString(*pad) {
				if goodSize(*msg, *pad) {
					tpad := truncateStr(*msg, *pad)
					mints := getInts(*msg)
					pints := getInts(tpad)
					sints := subInts(mints, pints)

					var ptxt string = ""
					for _, i := range sints {
						ptxt += decrypt(i)
					}
					fmt.Printf("PlainText: %s\n", ptxt)
				} else {
					fmt.Printf("The pad is smaller than the msg.\n")
				}
			} else {
				fmt.Printf("The pad has invalid chars.\n")
			}
		} else {
			fmt.Printf("The msg has invalid chars.\n")
		}
	}

	if *fflag {
		if goodString(*msg) {
			if goodString(*cflag) {
				if goodSize(*msg, *cflag) {
					tcflag := truncateStr(*msg, *cflag)
					genFakePad(*msg, tcflag)
				} else {
					fmt.Printf("The ciphertext is smaller than the msg.\n")
				}
			} else {
				fmt.Printf("The ciphertext has invalid chars.\n")
			}
		} else {
			fmt.Printf("The msg has invalid chars.\n")
		}
	}
}
