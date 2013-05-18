package main
import "fmt"
import "time"
import "math/rand"

func main(){
    channel := make(chan string)
    rand.Seed(time.Now().Unix())

    go func(){
        cnt := rand.Intn(10)
        fmt.Println("Message count:",cnt)
        for i:=0; i < cnt;i++{
            channel<-fmt.Sprintf("message-%2d",i)
        }
        close(channel)
    }()
    
    var more bool = true
    var msg string
    for more{
        select{
        //channel return two values:one is context,one if next
        case msg,more = <-channel:
            if more{
                fmt.Println(msg)
            }else{
                fmt.Println("channel closed!")
            }
        }
    }
}
