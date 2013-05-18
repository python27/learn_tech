package main

import "fmt"
import "math"

func main(){
    fmt.Println("Hello,world");

    fmt.Printf("%t\n",1==2)
    fmt.Printf("2jinzhi:%b\n",255)
    fmt.Printf("8jinzhi:%o\n",255)
    fmt.Printf("16jinzhi:%x\n",255)
    fmt.Printf("10jinzhi:%d\n",255)
    fmt.Printf("float:%f\n",math.Pi)
    fmt.Printf("string:%s\n","Hello,world")
}

