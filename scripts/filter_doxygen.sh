cat $1 | sed 's/```c/@code{.c}/' | sed 's/```/@endcode/'