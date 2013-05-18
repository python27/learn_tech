package main

import "fmt"

func main(){
    var i int = 1;
    var pInt *int = &i;
    fmt.Printf("i=%d\t pInt=%p\t *pInt=%d\n",i,pInt,*pInt);
    fmt.Printf("i=%d\t pInt=%d\t *pInt=%d\n",i,pInt,*pInt);

    *pInt = 2;
    fmt.Printf("i=%d\t pInt=%p\t *pInt=%d\n",i,pInt,*pInt);

    i = 3;
    fmt.Printf("i=%d\t pInt=%p\t *pInt=%d\n",i,pInt,*pInt);
    

}
