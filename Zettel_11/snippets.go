package main

import (
	"bufio"
	"os"
	"os/exec"
	"fmt"
	"strings"
)
func main(){
	for{
		aInput()
	}
}

func aInput(){
// read line from terminal
bio := bufio.NewReader(os.Stdin)
command, err := bio.ReadString('\n')

// separates command from argments
parts := strings.Fields(command)
args := parts[1:]

//Check for cls&exit
if parts[0]=="cls"{
	fmt.Printf("\033[H\033[2J");
	return
}else if parts[0]=="exit"{
		os.Exit(0)
}

// Checks whether command is in $PATH
command, err = exec.LookPath(command)
if err != nil {
	fmt.Println	(err.Error())
	return
}
	// if args is an array of arguments, build cmd struct
	cmd := exec.Command(parts[0], args...)
	// redirect file handles
	cmd.Stdin = os.Stdin
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr

	cmd.Run()
}
