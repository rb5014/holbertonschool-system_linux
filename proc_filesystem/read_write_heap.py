#!/usr/bin/python3
"""read_write_heap - script that finds a string in the heap of
a running process, and replaces it.
"""

import sys

if len(sys.argv) < 4:
    print("Usage: read_write_heap.py pid search_string replace_string")
    exit(1)

pid = sys.argv[1]
search_string = sys.argv[2].encode("utf-8")
replace_string = sys.argv[3].encode("utf-8")

maps_filename = "/proc/{}/maps".format(pid)
mem_filename = "/proc/{}/mem".format(pid)

add_in_memory = None  # Define add_in_memory here

try:
    with open(maps_filename, mode="r") as maps_file:
        while True:
            line = maps_file.readline()
            if not line:
                break
            sline = line.split(' ')
            try:
                # check if we found the heap
                if sline[-1][:-1] == "[heap]":

                    # parse line
                    addr = sline[0]
                    perm = sline[1]
                    offset = sline[2]
                    device = sline[3]
                    inode = sline[4]
                    pathname = sline[-1][:-1]

                    # get start and end of mem
                    addr = addr.split("-")
                    addr_start = int(addr[0], 16)
                    addr_end = int(addr[1], 16)

                    # open and read mem
                    try:
                        mem_file = open(mem_filename, 'r+b')
                        # read heap
                        mem_file.seek(addr_start)
                        heap = mem_file.read(addr_end - addr_start)
                        # find string
                        try:
                            add_in_memory = heap.index(search_string)
                            add_in_memory += addr_start
                            mem_file.seek(add_in_memory)

                            # Adjust the length of the replace string
                            replace_string_padded = replace_string\
                                					+ b'\x00' *\
                                         			(len(search_string)
                                    				- len(replace_string))
                            mem_file.write(replace_string_padded)

                        except Exception as e:
                            print(e)
                        mem_file.close()
                    except Exception as e:
                        print(e)

                    break
            except Exception as e:
                print(e)
except Exception as e:
    print(e)
