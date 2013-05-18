package main

import (
        "net"
        "fmt"
        "io"
)

const RECV_BUF_LEN = 1024

func main(){
    listener,err := net.Listen("tcp","0.0.0.0:6666")
    if err != nil{
        panic("error listening:"+err.Error())
    }
    fmt.Println("Starting the sever")

    for{
        conn,err := listener.Accept()
        if err != nil{
            panic("Error Accept:"+err.Error())
        }
        fmt.Println("Accept the connection:",conn.RemoteAddr())
        go EchoServer(conn)
    }
}

func EchoServer(conn net.Conn){
    buf := make([]byte, RECV_BUF_LEN)
    defer conn.Close()

    for {
        n,err := conn.Read(buf);
        switch err{
            case nil:
                conn.Write(buf[0:n])
            case io.EOF:
                fmt.Printf("Warning:End of data:%s \n",err)
                return
            default:
                fmt.Printf("Error:Reading data: %s \n",err)
                return
        }
    }
}
