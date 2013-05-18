package main
import "fmt"
import "os"

func main(){
    args := os.Args
    fmt.Println(args)  //带执行文件的
    fmt.Println(args[1:]) //不带执行文件的
}
