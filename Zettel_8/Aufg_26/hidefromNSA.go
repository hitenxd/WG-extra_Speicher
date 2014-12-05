package main

/*
#include <stdlib.h>
#include <rot13.h>
*/

import (
  "C"
  "bufio"
  "os"
  "fmt"
  //"unsafe"
 )

func main(){

 if len(os.Args) != 1 {
  fmt.Println("Verwendung: ", os.Args[0], " starten, dann tippen")
  os.Exit(1)
 }

 filename := "unlesbarenachricht.txt"

 reader := bufio.NewReader(os.Stdin)
 file, error := os.OpenFile(filename, os.O_CREATE|os.O_APPEND|os.O_WRONLY, 0666)
 checkError(error)

for {
 input, error := reader.ReadBytes('\n')
 checkError(error)

 _, error = file.Write(input[0:])
 checkError(error)

}

os.Exit(0)
}

 func checkError(error error) {
  if error != nil {
   fmt.Println("Verschlüsselung fehlgeschlagen ", error.Error())
   os.Exit(1)
  }
}
