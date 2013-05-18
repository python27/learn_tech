package main
import "math"
import "fmt"

type shape interface{
    area() float64
    perimeter() float64
}

//rectangle
type rect struct{
    width float64
    height float64
}

func (r *rect) area() float64{
    return r.width * r.height
}
func (r *rect) perimeter() float64{
    return 2 * (r.width + r.height)
}

//cicle
type circle struct{
    radius float64
}

func (c *circle) area() float64{
    return math.Pi * c.radius * c.radius
}
func (c *circle) perimeter() float64{
    return 2 * math.Pi * c.radius
}


func main(){
    r := rect{width:2.9,height:4.8}
    c := circle{radius:4.3}

    s := []shape{&r,&c}

    for _, sh := range s{
        fmt.Println(sh)
        fmt.Println(sh.area())
        fmt.Println(sh.perimeter())
    }
}
