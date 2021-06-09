# Assignment-1: CS2323
# Ananya Mantravadi (CS19B1004)
# Problem 5: Copy the elements of one array into another array

        .data
msg1:   .asciiz "Enter array size:\n"
msg2:   .asciiz "Enter array elements:\n"
msg3:   .asciiz "The elements in the first array are:\n"
msg4:   .asciiz "The elements in the second array after copying are:\n"
blank:  .asciiz " "
endl:   .asciiz "\n"

        .text
        .globl main

main:
        la $a0 msg1     # load the argument string
        li $v0 4        # system call code for print_string
        syscall         # print the string msg1 - "Enter array size:\n"

        li $v0 5        # system call code for read_int
        syscall         # read the value of n

        move $t0 $v0    # store value of n in $t0

        sll $a0 $v0 2   # sll performs $a0 = $v0 x 2^2 
        li $v0 9        # system call code for sbrk
        syscall         # allocate space for first array of size n

        move $t1 $zero  # store value of 0 in $t1
        move $t2 $v0    # store first array's starting address in $t2
        move $t3 $v0    # store first array's starting address in $t3
        move $t4 $v0    # store first array's starting address in $t4

        la $a0 msg2     # load the argument string
        li $v0 4        # system call code for print_string
        syscall         # print the string msg2 - "Enter array elements:\n"

loop:   # to take input of array elements from user

        bge $t1 $t0 end

        li $v0 5        # system call code for read_int
        syscall         # read the value of array element
        sw $v0 0($t2)   # store the value of array element $v0 into index at address [0+$t2] 

        addi $t1 $t1 1  # increment iterator value by 1
        addi $t2 $t2 4  # increment address by 4 to increment index of array
        j loop          # jump to starting of loop 

end:

        la $a0 msg3    # load the argument string
        li $v0 4       # system call code for print_string
        syscall        # print the string msg3 - "The elements in the first array are:\n"

        move $t1 $zero # store value of 0 in $t1

print_loop1:           # to print the array elements of first array

        bge $t1 $t0 end_loop1

        lw $a0 0($t3)   # load the value of array element at address [0+$t3]
        li $v0 1        # system call code for print_int
        syscall         # print the value of array element

        la $a0 blank    # load the argument string
        li $v0 4        # system call code for print_string
        syscall         # print a blank space

        addi $t1 $t1 1  # increment iterator value by 1
        addi $t3 $t3 4  # increment address by 4 to increment index of array
        j print_loop1   # jump to starting of loop 

end_loop1:

        la $a0 endl     # load the argument string
        li $v0 4        # system call code for print_string
        syscall         # print a line break

        # allocate space for second array of size n 

        sll $a0 $t0 2   # sll performs $a0 = $t0 x 2^2 ($t0 contains value of n, array size)
        li $v0 9        # system call code for sbrk
        syscall                

        move $t1 $zero  # store value of 0 into $t1
        move $t2 $v0    # store second array's starting address in $t2
        move $t3 $v0    # store second array's starting address in $t3

copy_loop:              # copying elements from first array into second array

        bge $t1 $t0 end_copy_loop

        lw $a0 0($t4)   # load the value of first array's element at address [0+$t4]
        sw $a0 0($t2)   # store the value into second array's element at address [0+$t2]       

        addi $t1 $t1 1  # increment iterator value by 1
        addi $t4 $t4 4  # increment address by 4 to increment index of first array
        addi $t2 $t2 4  # increment address by 4 to increment index of second array
        j copy_loop     # jump to starting of loop

end_copy_loop:
        
        la $a0 msg4     # load the argument string
        li $v0 4        # system call code for print_string
        syscall         # print the string msg4 - "The elements in the second array after copying are:\n"

        move $t1 $zero  # store value of 0 in $t1

print_loop2:            # to print the array elements of second array

        bge $t1 $t0 end_loop2

        lw $a0 0($t3)   # load the value of array element at address [0+$t3]
        li $v0 1        # system call code for print_int
        syscall         # print the value of array element

        la $a0 blank    # load the argument string
        li $v0 4        # system call code for print_string
        syscall         # print a blank space

        addi $t1 $t1 1  # increment iterator value by 1
        addi $t3 $t3 4  # increment address by 4 to increment index of array
        j print_loop2   # jump to starting of loop 

end_loop2:

        jr $ra          # return to caller
