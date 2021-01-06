package main

import (
	"log"
)

// The padder char set
var chars = "abcdefghijklmnopqrstuvwxyz0123456789-"

// The string to int map
var s2i = make(map[string]int, 0)

// The int to string map
var i2s = make(map[int]string, 0)

// Ensure string only has valid padder chars
func goodString(str string) bool {
	for _, c := range str {
		_, ok := s2i[string(c)]
		if !ok {
			return false
		}
	}
	return true
}

// Ensure pad is equal to or greater than msg
func goodSize(msg, pad string) bool {
	if len(msg) > len(pad) {
		return false
	}
	return true
}

// Truncate pad
// goodSize() has already made sure that msg <= pad
func truncatePad(msg, pad string) string {
	// msg < pad
	if len(msg) < len(pad) {
		//log.Printf("TruncatePad: %s\n", pad[:len(msg)])
		return pad[:len(msg)]
	}
	// msg = pad
	return pad
}

// Get ints from a string
func getInts(str string) []int {
	ints := make([]int, 0)

	for _, c := range str {
		i := s2i[string(c)]
		ints = append(ints, i)
	}

	return ints
}

// Add msg and pad ints
func addInts(msg, pad []int) []int {
	added := make([]int, 0)

	if len(msg) != len(pad) {
		log.Fatal("msg and pad must be the same size!")
	}

	for i := 0; i != len(msg); i++ {
		//log.Printf("%d\n", msg[i]+pad[i])
		added = append(added, msg[i]+pad[i])
	}
	return added
}

// Subtract msg from pad ints
func subInts(msg, pad []int) []int {
	subed := make([]int, 0)

	if len(msg) != len(pad) {
		log.Fatal("msg and pad must be the same size!")
	}

	for i := 0; i != len(msg); i++ {
		//log.Printf("%d\n", msg[i]-pad[i])
		subed = append(subed, msg[i]-pad[i])
	}
	return subed
}

// Given an int, return encrypted string
func encrypt(i int) string {
	var tmp int = 0

	if i > len(chars)-1 {
		tmp = (i - len(chars)) % len(chars)
	} else {
		tmp = i % len(chars)
	}

	return i2s[tmp]
}

// Given an int, return decrypted string
func decrypt(i int) string {
	var tmp int = 0

	tmp = (i + len(chars)) % len(chars)

	return i2s[tmp]
}
