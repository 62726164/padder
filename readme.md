# padder

Padder is a one-time pad implementation intended for educational purposes and experimentation. It can be used to encrypt and decrypt small messages. Padder can also be used to generate fake pads and fake messages. Read more about padder on the [blog](https://www.go350.com/posts/padder-a-one-time-pad-implementation/)

## To Build

```bash
$ make
```

## The Padder Character Set
```bash
abcdefghijklmnopqrstuvwxyz0123456789-
```

## Generate pads
```bash
$ go run utils/genPads.go
```

## Encrypt a message

```bash
$ padder -e -m black -p e7vwd
CipherText: fhvyn
```

## Decrypt a message

```bash
$ padder -d -m fhvyn -p e7vwd
PlainText: black
```

## Fake message and pad generation
 
```bash
$ padder -f -m white -c fhvyn
FakePad: uanfj
```

