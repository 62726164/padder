package main

import (
	"crypto/rand"
	"flag"
	"fmt"
	"math/big"
)

// purpose: generate pads for use by padder.

// usage: go run genPads.go > pads.txt

// The padder char set
var chars = "abcdefghijklmnopqrstuvwxyz0123456789-"
var lenChars int64 = int64(len(chars))

// The int to string map
var i2s = make(map[int64]string, 0)

func main() {
	var help = flag.Bool("help", false, "show help and exit")
	var numb = flag.Int("n", 12, "the number of pads to generate")
	var plen = flag.Int("l", 98, "the length of the pads")

	flag.Parse()

	if *help {
		flag.PrintDefaults()
		return
	}

	// build the i2s map
	for i, c := range chars {
		i2s[int64(i)] = string(c)
	}

	// Index starts at 0 and ends at 36.
	max := big.NewInt(lenChars)

	// Print *numb pads
	fmt.Println("# Pad")
	for pn := 1; pn <= *numb; pn++ {
		pad := ""
		for i := 0; i < *plen; i++ {
			// Int returns a uniform random value in [0, max).
			p, _ := rand.Int(rand.Reader, max)

			// Get random char from map
			rc, _ := i2s[p.Int64()]
			//fmt.Println(rc)

			pad += rc
		}
		fmt.Printf("%d %s\n", pn, pad)
	}
}
