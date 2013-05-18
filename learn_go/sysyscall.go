package main

import "os"
import "strings"

func main(){
    for _, env := range os.Environ(){
        e := strings.Split(env, "=")
        println(e[0], "=", e[1])
    }
}
