package main

import "fmt"

/**
线性表的数据对象集合为 {a1, a2, ..., an}，每个元素的类型均为 DataType。
其中，除第一个元素 a1 外，每一个元素有且只有一个直接前驱元素，除了最后一个元素
an 外，每一个元素有且只有一个直接后继元素。数据元素之间的关系是一对一的关系。
*/

type List struct {
	data []int
}

// 初始化线性表。
func (l *List) InitList() {
}

// 若线性表为空，返回 true，否则返回 false
func (l *List) ListEmpty() bool {
	return len(l.data) == 0
}

// 将线性表清空
func (l *List) ClearList() {
	l.data = make([]int, 0)
}

// 将线性表 l 中第 i 个位置元素返回
func (l *List) GetElem(i int) int {
	return l.data[i]
}

// 在线性表 l 中查找与给定值 e 相等的元素，如果查找成功，
// 返回该元素在表中序号表示成功；否则返回 -1 表示失败。
func (l *List) LocateElem(e int) (int, bool) {
	for i, v := range l.data {
		if v == e {
			return i, true
		}
	}
	return -1, false
}

// 在线性表的第 i 个位置插入新元素 e
func (l *List) ListInsert(i, e int) bool {
	if i < 0 {
		panic(fmt.Sprintf("Index \"%d\" out of range", i))
	}
	if i > len(l.data)-1 {
		panic(fmt.Sprintf("Index \"%d\" out of range", i))
	}

	result := make([]int, 0)
	prefix := l.data[:i]
	postfix := l.data[i:]
	result = append(result, prefix...)
	result = append(result, e)
	result = append(result, postfix...)
	l.data = result

	return true
}

// 删除线性表中第 i 个元素
func (l *List) ListDelete(i int) (e int) {
	if i < 0 {
		panic(fmt.Sprintf("Index \"%d\" out of range", i))
	}
	if i > len(l.data)-1 {
		panic(fmt.Sprintf("Index \"%d\" out of range", i))
	}

	e = l.data[e]

	result := make([]int, 0)
	prefix := l.data[:i]
	postfix := l.data[i+1:] // i + 1，不要位置 i 的元素了
	result = append(result, prefix...)
	result = append(result, postfix...)
	l.data = result

	return
}

// 返回线性表的元素个数
func (l *List) ListLength() int {
	return len(l.data)
}

/*
false
[4 3 1 2]
item = 1
3's index is 1
[4 3 1]
length: 3
length: 0
*/
func main() {
	l := List{data: []int{3, 1, 2}}
	// 初始化
	l.InitList()

	// false
	fmt.Printf("%t\n", l.ListEmpty())

	// 插入元素
	l.ListInsert(0, 4)
	fmt.Printf("%v\n", l.data)

	// 获取元素
	item := l.GetElem(2)
	fmt.Printf("item = %d\n", item) // 1

	// 定位元素
	elem := 3
	index, ok := l.LocateElem(elem)
	if !ok {
		fmt.Errorf("%d not in l\n", elem)
	}
	fmt.Printf("%d's index is %d\n", elem, index)

	// 删除元素
	l.ListDelete(3)
	fmt.Printf("%v\n", l.data)
	fmt.Printf("length: %d\n", l.ListLength()) // 3

	// 清空线性表
	l.ClearList()
	fmt.Printf("length: %d\n", l.ListLength()) // 0
}
