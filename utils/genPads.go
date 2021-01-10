package main

import (
	"crypto/rand"
	"flag"
	"fmt"
	"math/big"
)

// purpose: generate pads for use by padder.

// usage: go run genPads.go > pads.txt

// Map of the padder char set: "abcdefghijklmnopqrstuvwxyz0123456789-"
// There are 37 chars in the padder char set.
var m = map[int64]string{0: "a", 1: "b", 2: "c", 3: "d", 4: "e", 5: "f",
	6: "g", 7: "h", 8: "i", 9: "j", 10: "k", 11: "l",
	12: "m", 13: "n", 14: "o", 15: "p", 16: "q", 17: "r",
	18: "s", 19: "t", 20: "u", 21: "v", 22: "w", 23: "x",
	24: "y", 25: "z",
	26: "0", 27: "1", 28: "2", 29: "3", 30: "4",
	31: "5", 32: "6", 33: "7", 34: "8", 35: "9",
	36: "-",
}

func main() {
	var help = flag.Bool("help", false, "show help and exit")
	var numb = flag.Int("n", 12, "the number of pads to generate")
	var plen = flag.Int("l", 98, "the length of the pads")

	flag.Parse()

	if *help {
		flag.PrintDefaults()
		return
	}

	// Index starts at 0 and ends at 36.
	max := big.NewInt(37)

	// Print *numb pads
	fmt.Println("# Pad")
	for pn := 1; pn <= *numb; pn++ {
		pad := ""
		for i := 0; i < *plen; i++ {
			// Int returns a uniform random value in [0, max).
			p, _ := rand.Int(rand.Reader, max)

			// Get random char from map
			rc, _ := m[p.Int64()]
			//fmt.Println(rc)

			pad += rc
		}
		fmt.Printf("%d %s\n", pn, pad)
	}
}
