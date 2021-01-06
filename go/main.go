package main

import (
	//"crypto/rand"
	"fmt"
	"strconv"
	//"math/big"
)

func main() {
	// build the i2c map
	for i, c := range chars {
		si := strconv.Itoa(i)
		i2c[si] = string(c)
		//fmt.Printf("%s %s\n", si, string(c))
	}

	// build the c2i map
	for i, c := range i2c {
		c2i[c] = i
	}

	fmt.Printf("i2c %q\n", i2c)
	fmt.Printf("c2i %q\n", c2i)
}
