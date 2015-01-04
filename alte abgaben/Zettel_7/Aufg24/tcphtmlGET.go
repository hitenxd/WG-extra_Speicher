package main //Zu Copy-Paste Zwecken: http://www.net.cs.uni-bonn.de/wg/cs/teaching/wt-201415/sysprog


import (
 "fmt"
 "net/http"
 "net/url"
 "os"
 )

 func main() {

  if len(os.Args) != 2 {
   fmt.Println("Verwendung: ", os.Args[0], "http://host:port/link")
   os.Exit(1)
  }
  url, error := url.Parse(os.Args[1])
  checkError(error)

   client := &http.Client{}

   request, error := http.NewRequest("GET", url.String(), nil)

   response, error := client.Do(request)
   if response.Status != "200 OK" {
    fmt.Println(response.Status)
    os.Exit(2)
   }

   var buf [512]byte

   reader := response.Body
   filename := "zettel.html"
   file, err := os.OpenFile(filename, os.O_CREATE|os.O_APPEND|os.O_WRONLY, 0666)
   if err != nil {
    os.Exit(3)
   }

   for {
    n, error := reader.Read(buf[0:])
    if error != nil {
     fmt.Println("Lesen abgeschlossen")
     os.Exit(0)
    }
    _, error = file.Write(buf[0:n])
   }
   os.Exit(0)
  }

  func checkError(error error) {
   if error != nil {
    fmt.Println("Request fehlgeschlagen ", error.Error())
    os.Exit(1)
   }
  }
