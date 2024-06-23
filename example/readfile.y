#!/bin/why

fun readfile(filename)
{
    var handler = openfile(filename)
    handler.write("something!")
    handler.close()

    return true
}