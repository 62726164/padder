package main

import (
	"crypto/rand"
	"fmt"
	"math/big"
	"strings"
)

func genFakePad(fakeMsg, cipherText string) {
	max := big.NewInt(lenChars)

	fakePad := make([]string, 0)

	for i := 0; i < len(cipherText); i++ {
		p, _ := rand.Int(rand.Reader, max)
		rc, _ := i2s[p.Int64()]
		fakePad = append(fakePad, rc)
	}

	cints := getInts(cipherText)

	for _, c := range chars {
		tmpMsg := ""
		tmpPad := strings.Builder{} // aaaa..., bbbb..., cccc..., ...

		for i := 0; i < len(cipherText); i++ {
			tmpPad.WriteRune(c)
		}

		tints := getInts(tmpPad.String())
		sints := subInts(cints, tints)

		for _, i := range sints {
			tmpMsg += decrypt(i)
		}

		for i := 0; i < len(fakeMsg); i++ {
			if fakeMsg[i] == tmpMsg[i] {
				fakePad[i] = string(c)
			}
		}
	}
	fmt.Printf("%v\n", fakePad)
}
