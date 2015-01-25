package main
import "fmt"
import "time"
import "syscall"

var cnt int = 0

func printer(){
 time.Sleep(100 * time.Millisecond)
 fmt.Println(cnt," ",syscall.Getpid()," ",syscall.Getppid())
 cnt = cnt + 1
}
func main() {
 printer()
 go printer()
 //time.Sleep(100 * time.Millisecond)
 go printer()
 time.Sleep(1000 * time.Millisecond)
}
