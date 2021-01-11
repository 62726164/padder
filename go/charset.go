package main

import (
	"log"
)

// version
var version = "gopadder 1.0a"

// The padder char set
var chars = "abcdefghijklmnopqrstuvwxyz0123456789-"
var lenChars int64 = int64(len(chars))

// The string to int map
var s2i = make(map[string]int64, 0)

// The int to string map
var i2s = make(map[int64]string, 0)

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

// Truncate str
// goodSize() has already made sure that msg <= str
// str is either pad (for encryption and decryption) or ciphertext (for fakepad)
func truncateStr(msg, str string) string {
	// msg < str
	if len(msg) < len(str) {
		//log.Printf("Truncate: %s\n", str[:len(msg)])
		return str[:len(msg)]
	}
	// msg = str
	return str
}

// Get ints from a string
func getInts(str string) []int64 {
	ints := make([]int64, 0)

	for _, c := range str {
		i := s2i[string(c)]
		ints = append(ints, i)
	}

	return ints
}

// Add msg and pad ints
func addInts(msg, pad []int64) []int64 {
	added := make([]int64, 0)

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
func subInts(msg, pad []int64) []int64 {
	subed := make([]int64, 0)

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
func encrypt(i int64) string {
	var tmp int64 = 0

	if i > lenChars-1 {
		tmp = (i - lenChars) % lenChars
	} else {
		tmp = i % lenChars
	}

	return i2s[tmp]
}

// Given an int, return decrypted string
func decrypt(i int64) string {
	var tmp int64 = 0

	tmp = (i + lenChars) % lenChars

	return i2s[tmp]
}
