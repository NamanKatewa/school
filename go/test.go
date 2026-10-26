package main

import "fmt"

func main() {
	names := []string{"Alice"}
	names = append(names, "Bob", "Charlie")
	for _, name := range names {
		fmt.Println(name)
	}
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func divide(a, b int) (int, int) {
	return a / b, a % b
}

func sum(nums ...int) int {
	total := 0

	for _, n := range nums {
		total += n
	}
	return total
}

type Counter struct{ Count int }

func (c *Counter) Increment() {
	c.Count++
}
