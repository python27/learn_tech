package main
import "fmt"

func max(a int, b int) int {
    if a > b{
        return a;
    }
    return b;
}

func multi_ret(key string) (int,bool){
    m := map[string]int{"one":1,"two":2,"three":3}
    var err bool
    var val int
    
    val,err = m[key]
    return val,err
}

func main(){
    fmt.Println(max(4,5))
    fmt.Println("------")

    v,e := multi_ret("one")
    fmt.Println(v,e)

    v,e = multi_ret("four")
    fmt.Println(v,e)

    if v,e = multi_ret("four");e{
        fmt.Println("normal")
    }else{
        fmt.Println("error")
    }

    
}
