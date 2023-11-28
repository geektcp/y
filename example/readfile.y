#!/bin/why

bool fun readfile(var filename)
{
    var handler = openfile(filename)
    handler.write("something!")
    handler.close()

    return true
}