package main

import ()

// The padder char set
var chars = "abcdefghijklmnopqrstuvwxyz0123456789-"

// The char to int map
var c2i = make(map[string]string, 0)

// The int to char map
var i2c = make(map[string]string, 0)

// Ensure string only has valid padder chars
func goodString(str string) bool {
	for _, c := range str {
		valid := c2i[string(c)]
		if valid == "" {
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
