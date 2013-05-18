package main
import "fmt"
import "time"

func main() {
    channel := make(chan string)  //buffer=1

    go func(){
        channel <- "hello"
        fmt.Println("write \"hello\" done !")

        channel <- "world"
        fmt.Println("write \"world\" done !")

        fmt.Println("Write go sleep...")
        time.Sleep(3*time.Second)
        channel <- "channel"
        fmt.Println("Write \"channel\" done !")
    }()

    time.Sleep(2*time.Second)
    fmt.Println("Reader Wake up...")

    msg := <-channel
    fmt.Println("Reader:",msg)

    msg = <-channel
    fmt.Println("Reader:",msg)

    msg = <-channel
    fmt.Println("Reader:",msg)
}
