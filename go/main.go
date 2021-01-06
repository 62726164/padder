package main

import (
	"fmt"
)

func main() {
	// build the i2s map
	for i, c := range chars {
		i2s[i] = string(c)
	}

	// build the s2i map
	for i, s := range i2s {
		s2i[s] = i
	}

	fmt.Printf("i2s %v\n", i2s)
	fmt.Printf("s2i %v\n", s2i)

	fmt.Printf("goodString 'msg' %t\n", goodString("msg"))
	fmt.Printf("goodString 'Msg' %t\n", goodString("Msg"))

	fmt.Printf("goodSize 'black white' %t\n", goodSize("black", "white"))
	fmt.Printf("goodSize 'blue red' %t\n", goodSize("blue", "red"))

	mints := getInts("msg")
	fmt.Printf("getInts 'msg' %v\n", mints)

	pints := getInts("pad")
	fmt.Printf("getInts 'pad' %v\n", pints)

	aints := addInts(mints, pints)
	fmt.Printf("addInts aints %v\n", aints)
}
