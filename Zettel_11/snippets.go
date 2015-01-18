// read line from terminal
bio := bufio.NewReader(os.Stdin)
command, err := bio.ReadString('\n')

// separates command from argments
parts := strings.Fields(command)
cmd = parts[0]
args = parts[1:]

// Checks whether command is in $PATH
command, err = exec.LookPath(command)
if err != nil {
	...
}

// if args is an array of arguments, build cmd struct
cmd := exec.Command(command, args...)

// redirect file handles
cmd.Stdin = os.Stdin
cmd.Stdout = os.Stdout
cmd.Stderr = os.Stderr
