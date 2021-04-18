# List of All Process
task_struct_traversal.c - lists all process's pid running currently

# List of Sibling Process  
Digram Ref: https://stackoverflow.com/questions/67119348/siblings-of-struct-task-struct-current-always-include-a-process-with-pid-0/67128018#67128018

     PARENT              CHILD 1             CHILD 2
     ======              =======             =======

                         task_struct         task_struct
                        +-------------+     +-------------+
                        |             |     |             |
     task_struct        ~             ~     ~             ~
    +-------------+     |             |     |             |
    |             |     |-------------|     |-------------|
    ~             ~     | children    |     | children    |
    |             |     |             |     |             |
    |-------------|     |-------------|     |-------------| 
    | children    |     | sibling     |     | sibling     |
    | prev | next |<===>| prev | next |<===>| prev | next | <== X ==> PARENT->children
    |-------------|     |-------------|     |-------------| 
    | sibling     |     |             |     |             |
    |             |     ~             ~     ~             ~
    |-------------|     |             |     |             |
    |             |     +-------------+     +-------------+
    ~             ~
    |             |     'X's are joined together, making
    +-------------+     a doubly linked, circular list.

task_struct_list_siblings.c - lists sibling process's of 'insmod' command/program which 
			      is inserting this module

To better view siblings, follow below steps
make  

sudo su root

top &

tail -f &

ps -o ppid,pid,cmd

insmod ./task_struct_list_siblings.ko  && dmesg | tail -n5
