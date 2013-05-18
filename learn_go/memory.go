package main

import "fmt"

func main(){
    var p *[]int = new([]int)
    fmt.Println(p)
    
    *p = make([]int,10,10)
    fmt.Println(p)
    fmt.Println(*p)
    fmt.Println((*p)[2])

    fmt.Println("--------")

    q := make([]int,10,15)
    fmt.Println(q)
    fmt.Println((q)[2])
    fmt.Println(q)
}
