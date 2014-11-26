package main //Main default package

import (
	"fmt"
)

func sock() int {
	var fd int
	//fd = socket(AF_INET,SOCK_STREAM,0);
	
	if (fd<0) {
		fmt.Println("Fehler beim erstellen des Sockets.")
		return -1
	}

	return fd
}




func main(){
	var fd int
	fd = sock()
	
}